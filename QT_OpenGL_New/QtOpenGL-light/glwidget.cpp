#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) R

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
    m_shader(nullptr), m_vao(nullptr), arrayBuf(nullptr), indexBuf(nullptr)
{
    //rotationAxis = QVector3D( 1.0f, 1.0f,  1.0f);
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, [&]{
        angularSpeed *= 0.99;
        if (angularSpeed < 0.01) {
            angularSpeed = 0.0;
        } else {
            rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        }
        update();
    });

    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
}

GlWidget::~GlWidget(){

}

void GlWidget::mousePressEvent(QMouseEvent *e) {
    mousePressPosition = QVector2D(e->localPos());
}
void GlWidget::mouseReleaseEvent(QMouseEvent *e) {
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    qreal acc = diff.length() / 100.0;
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    angularSpeed += acc;
}

void GlWidget::initShader() {
    QString sProPath = CONFIG2QSTR(CONFIG2STR(PRO_PATH));

    m_vao->bind();
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }
    m_vao->release();
}

void GlWidget::initTexture() {
    m_texture = new QOpenGLTexture(QImage(":/image.jpg").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void GlWidget::initializeGL()
{
    m_vao = new QOpenGLVertexArrayObject();
    arrayBuf = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    indexBuf = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);

    arrayBuf->create();
    indexBuf->create();
    m_vao->create();

    //init gl environment
    QOpenGLFunctions *f = this->context()->functions();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //init shader
    initShader();
    initTexture();

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);

    //init data
    initCubeGeometry();

    timer.start();
}

void GlWidget::paintGL()
{
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    m_vao->bind();
    arrayBuf->bind();
    indexBuf->bind();
    m_shader->bind();

    m_shader->setUniformValue("mvp_matrix", projection * matrix);

    m_texture->bind();
    m_shader->setUniformValue("texture", 0);
    m_texture->release();

    m_shader->release();
    arrayBuf->release();
    indexBuf->release();
    m_vao->release();

    drawCubeGeometry();
}

void GlWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}

void GlWidget::initCubeGeometry() {
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    m_vao->bind();
    arrayBuf->bind();
    arrayBuf->allocate(vertices, 24 * sizeof(VertexData));
    arrayBuf->release();
    indexBuf->bind();
    indexBuf->allocate(indices, 34 * sizeof(GLushort));
    indexBuf->release();
    m_vao->release();
}

void GlWidget::drawCubeGeometry() {
    m_vao->bind();
    indexBuf->bind();
    arrayBuf->bind();
    m_texture->bind();

    m_shader->bind();
    quintptr offset = 0;
    int vertexLocation = m_shader->attributeLocation("a_position");
    m_shader->enableAttributeArray(vertexLocation);
    m_shader->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    int texcoordLocation = m_shader->attributeLocation("a_texcoord");
    m_shader->enableAttributeArray(texcoordLocation);
    m_shader->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    QOpenGLFunctions *f = this->context()->functions();
    f->glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    m_shader->release();

    m_texture->release();
    arrayBuf->release();
    indexBuf->release();
    m_vao->release();
}
