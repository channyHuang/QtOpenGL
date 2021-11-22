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
    // normal shader
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    if (!m_shader->link()) {
        qDebug("Shaders link failed!");
    }

    // light shader
    m_shader_light = new QOpenGLShaderProgram();
    m_shader_light->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader_light.glsl");
    m_shader_light->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader_light.glsl");
    if (!m_shader_light->link()) {
        qDebug("Light Shaders link failed!");
    }

    // nm shader
    m_shader_nm = new QOpenGLShaderProgram();
    m_shader_nm->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader_nm.glsl");
    m_shader_nm->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader_nm.glsl");
    if (!m_shader_nm->link()) {
        qDebug("NM Shaders link failed!");
    }

    // vis shader
    m_shader_vis = new QOpenGLShaderProgram();
    m_shader_vis->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader_vis.glsl");
    if (!m_shader_vis->link()) {
        qDebug("Vis Shaders link failed!");
    }

    m_shader_vis->bind();
    uniforms.loc_vis_mode = m_shader_vis->uniformLocation("vis_mode");
    m_shader_vis->release();

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
    tex_nm = cKtxLoader.load(QString(sTexturePath + "/brick.ktx").toStdString().c_str(), 0, f);
    tex_diffuse = cKtxLoader.load(QString(sTexturePath + "/ceiling.ktx").toStdString().c_str(), 0, f);

    f->glGenTextures(3, gbuffer_tex);

    f->glBindTexture(GL_TEXTURE_2D, gbuffer_tex[0]);
    f->glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    f->glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gbuffer_tex[0], 0);

    f->glBindTexture(GL_TEXTURE_2D, gbuffer_tex[1]);
    f->glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    f->glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, gbuffer_tex[1], 0);

    f->glBindTexture(GL_TEXTURE_2D, gbuffer_tex[2]);
    f->glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, MAX_DISPLAY_WIDTH, MAX_DISPLAY_HEIGHT);
    f->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gbuffer_tex[2], 0);

    f->glBindFramebuffer(GL_FRAMEBUFFER, 0);

    objLoader.load((m_sProPath + " /ladybug.sbm").toStdString().c_str(), f);
    tex_nm = cKtxLoader.load("ladybug_nm.ktx");
    tex_diffuse = cKtxLoader.load("ladybug_co.ktx");

    m_shader->release();
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

    static const GLuint uint_zeros[] = { 0, 0, 0, 0 };
    static const GLfloat float_zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat float_ones[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    int i, j;
    static double last_time = 0.0;
    static double total_time = 0.0;



    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    f->glBindTexture(GL_TEXTURE_2D, 0);
    f->glActiveTexture(GL_TEXTURE0);
    f->glBindTexture(GL_TEXTURE_2D, 0);

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
