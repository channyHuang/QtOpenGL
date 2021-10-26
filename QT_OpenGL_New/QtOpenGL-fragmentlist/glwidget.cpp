#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_vao(nullptr), currentTime(0)
{
    m_sProPath = CONFIG2QSTR(PRO_PATH);
    model_matrix.setToIdentity();
    model_matrix.scale(7.f);
    view_matrix.setToIdentity();

    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, [&]{
        currentTime += 0.001f;
    });
    timer.start();
}

GlWidget::~GlWidget(){

}

void GlWidget::initShader() {
    m_vao->bind();
    m_append_shader = new QOpenGLShaderProgram();
    m_append_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/append_vshader.glsl");
    m_append_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/append_fshader.glsl");
    if (m_append_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    uniforms.mvp = m_append_shader->uniformLocation("mvp");

    m_clear_shader = new QOpenGLShaderProgram();
    m_clear_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/clear_vshader.glsl");
    m_clear_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/clear_fshader.glsl");
    if (m_clear_shader->link()) {
        qDebug("clear shader link success");
    } else {
        qDebug("clear shader link failed");
    }

    m_resolve_shader = new QOpenGLShaderProgram();
    m_resolve_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resolve_vshader.glsl");
    m_resolve_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resolve_fshader.glsl");
    if (m_resolve_shader->link()) {
        qDebug("resolve shader link success");
    }

    m_vao->release();
}

void GlWidget::initObjects() {
    if (f == nullptr) {
        qDebug() << "init f failed";
        return;
    }

    m_vao->bind();

    m_resolve_shader->bind();
    m_append_shader->bind();
    m_clear_shader->bind();

    f->glGenBuffers(1, &uniforms_buffer);
    f->glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
    f->glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

    objLoader.load((m_sProPath + "/dragon.sbm").toStdString().c_str(), f);

    f->glGenBuffers(1, &fragment_buffer);
    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, fragment_buffer);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, 1024 * 1024 * 16, NULL, GL_DYNAMIC_COPY);

    f->glGenBuffers(1, &atomic_counter_buffer);
    f->glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomic_counter_buffer);
    f->glBufferData(GL_ATOMIC_COUNTER_BUFFER, 4, NULL, GL_DYNAMIC_COPY);

    f->glGenBuffers(1, &head_pointer_image);
    f->glBindBuffer(GL_TEXTURE_2D, head_pointer_image);
    f->glTexStorage2D(GL_TEXTURE, 1, GL_R32UI, 1024, 1024);

    m_clear_shader->release();
    m_append_shader->release();
    m_resolve_shader->release();
    m_vao->release();
}

void GlWidget::initializeGL()
{
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();

    if (f == nullptr) {
        f = this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>();
        f->initializeOpenGLFunctions();
    }
    if (f == nullptr) {
        qDebug() << "init f failed";
        return;
    }

    //init shader
    initShader();

    //init data
    initObjects();

    m_vao->release();
}

void GlWidget::paintGL()
{
    const float ftime = (float)currentTime;
    m_vao->bind();
    f->glViewport(0, 0, this->width(), this->height());

    f->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_ATOMIC_COUNTER_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);

    m_clear_shader->bind();
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_append_shader->bind();
    QVector3D view_position = QVector3D(std::cos(ftime * 0.35f) * 120.0f, std::cos(ftime * 0.4f) * 30.0f, std::sin(ftime * 0.35f) * 120.f);
    view_matrix.lookAt(view_position, QVector3D(0.f, 30.f, 0.f), QVector3D(0.f, 1.f, 0.f));

    m_append_shader->setUniformValue("mvp", projection * (view_matrix * model_matrix));

    static const unsigned int zero = 0;
    f->glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomic_counter_buffer);
    f->glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(zero), &zero);

    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fragment_buffer);

    f->glBindImageTexture(0, head_pointer_image, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

    f->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_ATOMIC_COUNTER_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
    objLoader.render(1, 0, f);
    f->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_ATOMIC_COUNTER_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);

    m_resolve_shader->bind();
    f->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_ATOMIC_COUNTER_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_resolve_shader->release();
    m_append_shader->release();
    m_clear_shader->release();
    m_vao->release();

    update();
}

void GlWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1f, zFar = 1000.0f, fov = 50.0f;
    projection.setToIdentity();
    projection.perspective(fov, this->width() * 1.f / this->height(), zNear, zFar);
}
