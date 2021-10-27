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
    m_shader->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/tcshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/teshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    uniforms.mv_matrix = m_shader->uniformLocation("mv_matrix");
    uniforms.proj_matrix = m_shader->uniformLocation("proj_matrix");
    uniforms.mvp_matrix = m_shader->uniformLocation("mvp_matrix");
    uniforms.dmap_depth = m_shader->uniformLocation("dmap_depth");
    uniforms.enable_fog = m_shader->uniformLocation("enable_fog");

    m_vao->release();
}

void GlWidget::initObjects() {
    if (f == nullptr) {
        qDebug() << "init f failed";
        return;
    }

    m_vao->bind();
    m_shader->bind();

    f->glPatchParameteri(GL_PATCH_VERTICES, 4);
    f->glEnable(GL_CULL_FACE);
    tex_displacement = texLoader.load((m_sProPath + "terragen1.ktx").toStdString().c_str(), 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());
    f->glActiveTexture(GL_TEXTURE1);
    tex_color = texLoader.load((m_sProPath + "terragen_color.ktx").toStdString().c_str(), 0, this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());

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

    static const GLfloat black[] = {0.85f, 0.95f, 1.f, 0.f};
    static const GLfloat one = 1.f;
    f->glViewport(0, 0, this->width(), this->height());
    f->glClearBufferfv(GL_COLOR, 0, black);
    f->glClearBufferfv(GL_DEPTH, 0, &one);

    total_time += (currentTime - last_time);
    last_time = currentTime;

    float curTime = total_time * 0.03f;
    float r = std::sin(curTime * 5.37f) * 15.f + 16.f;
    float h = std::cos(curTime * 4.79f) * 2.f + 3.2f;

    mv_matrix.setToIdentity();
    mv_matrix.lookAt(QVector3D(std::sin(curTime) * r, h, std::cos(curTime) * r), QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 1.f, 0.f));

    m_shader->setUniformValue(uniforms.mv_matrix, mv_matrix);
    m_shader->setUniformValue(uniforms.proj_matrix, projection);
    m_shader->setUniformValue(uniforms.mvp_matrix, projection * mv_matrix);
    m_shader->setUniformValue(uniforms.dmap_depth, enable_displacement ? dmap_depth : 0.f);
    m_shader->setUniformValue(uniforms.enable_fog, enable_fog ? 1 : 0);

    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);

    if (wireframe) {
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        f->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    f->glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);

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
