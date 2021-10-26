#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr)
{
    m_sProPath = CONFIG2QSTR(PRO_PATH);
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, [&]{
        currentTime += 1.f;
    });
    timer.start();
}

GlWidget::~GlWidget(){

}

void GlWidget::initShader() {
    m_vao->bind();
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    m_shader->bind();
    m_shader->release();

    m_vao->release();
}

void GlWidget::initObjects() {
    if (f == nullptr) {
        qDebug() << "init f failed";
        return;
    }

    m_vao->bind();
    m_shader->bind();

    QString sTexturePath = m_sProPath + "/../resources";
    tex_alien_array = cKtxLoader.load(QString(sTexturePath + "/aliens.ktx").toStdString().c_str(), 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());
    f->glBindTexture(GL_TEXTURE_2D, tex_alien_array);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    f->glGenBuffers(1, &rain_buffer);
    f->glBindBuffer(GL_UNIFORM_BUFFER, rain_buffer);
    f->glBufferData(GL_UNIFORM_BUFFER, 256 * sizeof(QVector4D), NULL, GL_DYNAMIC_DRAW);

    for (int i = 0; i < 256; ++i) {
        droplet_x_offset[i] = rand() * 1.0f / RAND_MAX * 2.0f - 1.0f;
        droplet_rot_speed[i] = (rand() * 1.0f / RAND_MAX + 0.5f) * ((i & 1) ? -3.f : 3.f);
        droplet_fall_speed[i] = rand() * 1.0f / RAND_MAX + 0.2f;
    }

    f->glEnable(GL_BLEND);
    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shader->release();
    m_vao->release();
}

void GlWidget::initializeGL()
{
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();

    if (f == nullptr) {
        f = this->context()->versionFunctions<QOpenGLFunctions_4_2_Compatibility>();
        f->initializeOpenGLFunctions();
    }
    if (f == nullptr) {
        qDebug() << "init f failed";
        return;
    }

    //init shader
    initShader();

    m_shader->bind();
    //init data
    initObjects();

    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);

    m_shader->release();
    m_vao->release();
}

void GlWidget::paintGL()
{
    m_vao->bind();
    m_shader->bind();

    static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    f->glClearBufferfv(GL_COLOR, 0, black);
    f->glViewport(0, 0, this->width(), this->height());

    currentTime += 0.001f;

    f->glBindBufferBase(GL_UNIFORM_BUFFER, 0, rain_buffer);
    QVector4D *droplet = (QVector4D *)f->glMapBufferRange(GL_UNIFORM_BUFFER, 0, 256 * sizeof(QVector4D), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
    for (int i = 0; i < 256; i++) {
        droplet[i][0] = droplet_x_offset[i];
        droplet[i][1] = 2.f - std::fmod((currentTime + (float)i) * droplet_fall_speed[i], 4.31f);
        droplet[i][2] = currentTime * droplet_rot_speed[i];
        droplet[i][3] = 0.0f;
    }
    f->glUnmapBuffer(GL_UNIFORM_BUFFER);

    int alient_index;
    for (alient_index = 0; alient_index < 256; alient_index++) {
        f->glVertexAttribI1i(0, alient_index);
        f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    m_shader->release();
    m_vao->release();

    update();
}

void GlWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1f, zFar = 1000.0f, fov = 60.0f;
}
