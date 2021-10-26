#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr)
{
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
    uniforms.mv_matrix = m_shader->uniformLocation("mv_matrix");
    uniforms.proj_matrix = m_shader->uniformLocation("proj_matrix");
    m_shader->release();

    m_vao->release();
}

void GlWidget::initObjects() {
    QOpenGLFunctions_4_2_Core *f = this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>();
    if (f == nullptr) {
        return;
    }
    QString sProPath = CONFIG2QSTR(PRO_PATH);

    tex_object[1] = cKtxLoader.load(QString(sProPath + "/brick.ktx").toStdString().c_str(), 0, f);

    f->glViewport(0, 0, this->width(), this->height());
    m_vao->bind();
    objLoader.load(QString(sProPath + "/torus_nrms_tc.sbm").toStdString().c_str(), f);
    m_vao->release();
}

void GlWidget::initializeGL()
{
#define B 0x00, 0x00, 0x00, 0x00
#define W 0xFF, 0xFF, 0xFF, 0xFF
        static const GLubyte tex_data[] =
        {
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
            B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
            W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        };
#undef B
#undef W

    QString sProPath = CONFIG2QSTR(PRO_PATH);

    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();
    //init gl environment
    f = this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    f->glGenTextures(1, &tex_object[0]);
    f->glBindTexture(GL_TEXTURE_2D, tex_object[0]);
    f->glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 16, 16);
    f->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 16, 16, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //init shader
    initShader();
    //init data
    initObjects();

    f->glEnable(GL_DEPTH_TEST);
    //f->glEnable(GL_CULL_FACE);
    f->glDepthFunc(GL_LEQUAL);

    m_vao->release();
}

void GlWidget::paintGL()
{
    m_vao->bind();
    m_shader->bind();

    static const GLfloat gray[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    static const GLfloat ones[] = { 1.0f };

    f->glClearBufferfv(GL_COLOR, 0, gray);
    f->glClearBufferfv(GL_DEPTH, 0, ones);

    f->glViewport(0, 0, this->width(), this->height());
    f->glBindTexture(GL_TEXTURE_2D, tex_object[tex_index + 1]);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -3.0);
    matrix.rotate((float)currentTime * 19.3f, 0.0f, 1.0f, 0.0f);
    matrix.rotate((float)currentTime * 21.1f, 0.0f, 0.0f, 1.0f);

    m_shader->setUniformValue("mv_matrix", matrix);
    m_shader->setUniformValue("proj_matrix", projection);
    objLoader.render(1, 0, f);

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
