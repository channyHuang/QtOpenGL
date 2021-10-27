#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr)
{
    m_sProPath = CONFIG2QSTR(PRO_PATH);
    m_sProPath += QString("/../resources/");

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

    uniforms.mv_matrix = m_shader->uniformLocation("mv_matrix");
    uniforms.proj_matrix = m_shader->uniformLocation("proj_matrix");

    f->glEnable(GL_CULL_FACE);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);

    m_vao->release();
}

void GlWidget::initObjects() {
    if (f == nullptr) {
        qDebug() << "init f failed";
        return;
    }

    m_vao->bind();
    m_shader->bind();

    envmaps[0] = texLoader.load((m_sProPath + "spheremap1.ktx").toStdString().c_str(), 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());
    //envmaps[1] = texLoader.load((m_sProPath + "spheremap2.ktx").toStdString().c_str(), 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());
    //envmaps[2] = texLoader.load((m_sProPath + "spheremap3.ktx").toStdString().c_str(), 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());

    objLoader.load((m_sProPath + "dragon.sbm").toStdString().c_str(), this->context()->versionFunctions<QOpenGLFunctions_4_2_Compatibility>());

    m_shader->release();
    m_vao->release();
}

void GlWidget::initializeGL()
{
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();

    if (f == nullptr) {
        f = this->context()->versionFunctions<QOpenGLFunctions_4_4_Compatibility>();
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

    static const GLfloat black[] = {0.f, 0.f, 0.f, 0.f};
    f->glViewport(0, 0, this->width(), this->height());
    f->glClearBufferfv(GL_COLOR, 0, black);

    float curTime = (float)currentTime;

    f->glBindTexture(GL_TEXTURE_2D, envmaps[index]);
    //index = (index + 1) % 3;

    mv_matrix.setToIdentity();
    mv_matrix.translate(0.f, 0.f, -15.f);
    mv_matrix.rotate(curTime, 1.f, 0.f, 0.f);
    mv_matrix.rotate(curTime * 1.1f, 0.f, 1.f, 0.f);
    mv_matrix.translate(0.f, -4.f, 0.f);

    m_shader->setUniformValue(uniforms.mv_matrix, mv_matrix);
    m_shader->setUniformValue(uniforms.proj_matrix, projection);

    objLoader.render(1, 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Compatibility>());

    m_shader->release();
    m_vao->release();

    update();
}

void GlWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1f, zFar = 1000.0f, fov = 60.0f;
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}
