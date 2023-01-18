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
    uniforms.mv_matrix = m_shader->uniformLocation("mvp");
    uniforms.offset = m_shader->uniformLocation("offset");
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
    tex_wall = cKtxLoader.load(QString(sTexturePath + "/brick.ktx").toStdString().c_str(), 0, f);
    tex_ceiling = cKtxLoader.load(QString(sTexturePath + "/ceiling.ktx").toStdString().c_str(), 0, f);
    tex_floor = cKtxLoader.load(QString(sTexturePath + "/floor.ktx").toStdString().c_str(), 0, f);

    GLuint textures[] = { tex_floor, tex_wall, tex_ceiling };

    for (int i = 0; i < 3; i++) {
        f->glBindTexture(GL_TEXTURE_2D, textures[i]);

        /*************************
        基本的两个纹理过滤模式GL_NEAREST和GL_LINEAR,参数的形式诸如GL_<FILTER>_MIPMAP_<SELECTOR>
        *************************/
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    m_shader->release();
    m_vao->release();
}

void GlWidget::initializeGL()
{
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();

    if (f == nullptr) {
        f = this->context()->functions();
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

    GLuint textures[] = { tex_wall, tex_floor, tex_wall, tex_ceiling };
    for (int i = 0; i < 4; i++) {
        QMatrix4x4 matrix;
        matrix.rotate(90.f * i, 0.0f, 0.0f, 1.0f);
        matrix.translate(-0.5f, 0.0f, -10.0f);
        matrix.rotate(90.f, 0.f, 1.f, 0.f);
        matrix.scale(30.f, 1.f, 1.f);

        m_shader->setUniformValue("mvp", projection * matrix);
        m_shader->setUniformValue("offset", currentTime * 0.003f);
        f->glBindTexture(GL_TEXTURE_2D, textures[i]);
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
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}
