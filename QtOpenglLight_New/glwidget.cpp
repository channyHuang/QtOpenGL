#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr)
{
    m_sProPath = CONFIG2QSTR(PRO_PATH);
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, [&](){
        currentTime += 1.f;
    });
    timer.start();
}

GlWidget::~GlWidget(){

}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GlWidget::setRotation(int angle, int axis)
{
    qNormalizeAngle(angle);
    if (angle != m_vRot[axis]) {
        m_vRot[axis] = angle;
        update();
    }
}

void GlWidget::mousePressEvent(QMouseEvent *e) {
    mousePressPosition = QVector2D(e->localPos());
}

void GlWidget::mouseMoveEvent(QMouseEvent *e) {
    int dx = e->x() - mousePressPosition.x();
    int dy = e->y() - mousePressPosition.y();
    if (e->buttons() & Qt::LeftButton) {
        setRotation(m_vRot[0] + 8 * dy, 0);
        setRotation(m_vRot[1] + 8 * dx, 1);
    } else if (e->buttons() & Qt::RightButton) {
        setRotation(m_vRot[0] + 8 * dy, 0);
        setRotation(m_vRot[2] + 8 * dx, 2);
    }
    mousePressPosition = QVector2D(e->localPos());
    update();
}

void GlWidget::initLight() {
    lights[0].lightPosition = {0.f, 1.f, 0.f, 1.f};
    lights[0].lightShiness = 50.f;
    lights[0].lightAmbient = {1.f, 0.f, 0.f, 1.f};
    lights[0].lightDiffuse = {1.f, 0.f, 0.f, 1.f};
    lights[0].lightSpecular = {1.f, 0.f, 0.f, 1.f};
    lights[0].lightEmission = {0.f, 0.f, 0.f, 1.f};

    lights[1].lightPosition = {0.f, 1.f, 0.f, 1.f};
    lights[1].lightShiness = 50.f;
    lights[1].lightAmbient = {0.f, 1.f, 0.f, 1.f};
    lights[1].lightDiffuse = {0.f, 1.f, 0.f, 1.f};
    lights[1].lightSpecular = {0.f, 1.f, 0.f, 1.f};
    lights[1].lightEmission = {0.f, 0.f, 0.f, 1.f};

    lights[2].lightPosition = {1.f, 0.f, 0.f, 1.f};
    lights[2].lightShiness = 50.f;
    lights[2].lightAmbient = {0.f, 1.f, 0.f, 1.f};
    lights[2].lightDiffuse = {0.f, 0.f, 1.f, 1.f};
    lights[2].lightSpecular = {0.f, 0.f, 1.f, 1.f};
    lights[2].lightEmission = {0.f, 0.f, 0.f, 1.f};
}

void GlWidget::initShader() {
    m_vao->bind();
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");

    m_shader->bindAttributeLocation("vertex", 0);
    m_shader->bindAttributeLocation("normal", 1);

    if (!m_shader->link()) {
        qDebug("Shaders link failed!");
    }

    m_shader->bind();

    m_projMatrixLoc = m_shader->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_shader->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_shader->uniformLocation("normalMatrix");
    m_lightPosLoc = m_shader->uniformLocation("lightPos");

    m_shader->release();
    m_vao->release();
}

void GlWidget::initObjects() {
    m_vao->bind();
    m_shader->bind();

    loader.loadObjFile((m_sProPath + "/cow.obj").toStdString());
    qDebug() << "load obj success " << loader.count();
    m_shader->release();
    m_vao->release();
}

void GlWidget::initializeGL()
{
    f = this->context()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->initializeOpenGLFunctions();
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);
    f->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    m_vao = new QOpenGLVertexArrayObject();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vao->create();
    m_vbo->create();

    initShader();
    initObjects();

    m_vao->bind();
    m_vbo->bind();
    m_vbo->allocate(loader.constData(), loader.count() * sizeof(GLfloat));

    qDebug() << loader.count();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    m_camera.setToIdentity();
    m_camera.translate(0, 0, -10);
    m_shader->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 10));

    m_shader->release();
    m_vbo->release();
    m_vao->release();
}

void GlWidget::paintGL()
{
    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_vRot[0] / 16.0f), 1, 0, 0);
    m_world.rotate(m_vRot[1] / 16.0f, 0, 1, 0);
    m_world.rotate(m_vRot[2] / 16.0f, 0, 0, 1);

    m_vao->bind();
    m_vbo->bind();
    m_shader->bind();

    static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    f->glClearBufferfv(GL_COLOR, 0, black);
    f->glViewport(0, 0, this->width(), this->height());

    currentTime += 0.001f;

    m_shader->setUniformValue(m_projMatrixLoc, projection);
    m_shader->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_shader->setUniformValue(m_normalMatrixLoc, normalMatrix);

    m_shader->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    f->glDrawArrays(GL_TRIANGLES, 0, loader.vertexCount());

    m_shader->setUniformValue(m_lightPosLoc, QVector3D(70, 0, 0));

    m_shader->release();
    m_vbo->release();
    m_vao->release();

    update();
}

void GlWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.01f, zFar = 100.0f, fov = 45.0f;
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}
