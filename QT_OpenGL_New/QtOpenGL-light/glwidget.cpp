#include "glwidget.h"

static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr), m_vbo(nullptr)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
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
    if (angle != m_Rot[axis]) {
        m_Rot[axis] = angle;
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
        setRotation(m_Rot[0] + 8 * dy, 0);
        setRotation(m_Rot[1] + 8 * dx, 1);
    } else if (e->buttons() & Qt::RightButton) {
        setRotation(m_Rot[0] + 8 * dy, 0);
        setRotation(m_Rot[2] + 8 * dx, 2);
    }
    mousePressPosition = QVector2D(e->localPos());
    update();
}

void GlWidget::initShader() {
    m_shader = new QOpenGLShaderProgram;
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);

    m_shader->bindAttributeLocation("vertex", 0);
    m_shader->bindAttributeLocation("normal", 1);

    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    m_shader->bind();
    m_projMatrixLoc = m_shader->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_shader->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_shader->uniformLocation("normalMatrix");
    m_lightPosLoc = m_shader->uniformLocation("lightPos");
}

void GlWidget::initializeGL()
{
    //init gl environment
    QOpenGLFunctions *f = this->context()->functions();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initShader();

    m_vao = new QOpenGLVertexArrayObject();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vao->create();
    m_vbo->create();

    m_vao->bind();
    m_vbo->bind();
    m_vbo->allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);
    m_shader->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_shader->release();
    m_vbo->release();
    m_vao->release();
}

void GlWidget::paintGL()
{
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_Rot[0] / 16.0f), 1, 0, 0);
    m_world.rotate(m_Rot[1] / 16.0f, 0, 1, 0);
    m_world.rotate(m_Rot[2] / 16.0f, 0, 0, 1);

    m_vao->bind();
    m_vbo->bind();
    m_shader->bind();

    m_shader->setUniformValue(m_projMatrixLoc, projection);
    m_shader->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_shader->setUniformValue(m_normalMatrixLoc, normalMatrix);

    f->glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

    m_shader->release();
    m_vbo->release();
    m_vao->release();
}

void GlWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.01f, zFar = 100.0f, fov = 45.0;
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}
