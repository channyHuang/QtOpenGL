#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr)
{
    m_sProPath = CONFIG2QSTR(PRO_PATH);

    model_matrix.setToIdentity();
    model_matrix.scale(7.f);
    view_position = QVector3D(0.f, 0.f, 150.f);
    light_position = QVector3D(20.f, 20.f, 0.f);

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

    uniforms[0].mv_matrix = m_shader->uniformLocation("mv_matrix");
    uniforms[0].proj_matrix = m_shader->uniformLocation("proj_matrix");
    uniforms[0].view_matrix = m_shader->uniformLocation("view_matrix");
    uniforms[0].specular_power = m_shader->uniformLocation("specular_power");
    uniforms[0].specular_albedo = m_shader->uniformLocation("specular_albedo");

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

    objLoader.load((m_sProPath + "/../resources/dragon.sbm").toStdString().c_str(), this->context()->versionFunctions<QOpenGLFunctions_4_2_Compatibility>());

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

    view_matrix.setToIdentity();
    view_matrix.lookAt(view_position, QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 1.f, 0.f));
    light_proj_matrix.setToIdentity();
    light_proj_matrix.frustum(-1.f, 1.f, -1.f, 1.f, 1.f, 200.f);
    light_view_matrix.setToIdentity();
    light_view_matrix.lookAt(light_position, QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 1.f, 0.f));

    m_shader->setUniformValue(uniforms[0].mv_matrix, view_matrix * model_matrix);
    m_shader->setUniformValue(uniforms[0].view_matrix, view_matrix);
    m_shader->setUniformValue(uniforms[0].proj_matrix, projection);

    m_shader->setUniformValue(uniforms[0].specular_power, 30.f);
    m_shader->setUniformValue(uniforms[0].specular_albedo, QVector3D(1.f, 1.f, 1.f));

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
