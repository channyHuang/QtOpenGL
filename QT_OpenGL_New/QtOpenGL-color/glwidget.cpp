#include "glwidget.h"

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent), m_vbo(nullptr), m_vao(nullptr), m_shader(nullptr){

}
GlWidget::~GlWidget(){

}

static const char *vertexShaderSource =
    "#version 150\n"
    "in vec4 posAttr;\n"
    "in vec4 colAttr;\n"
    "out vec4 col;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "#version 150\n"
    "in vec4 col;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "   fragColor = col;\n"
    "}\n";

static const GLfloat VERTEX_DATA[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
};

static GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

void GlWidget::initializeGL()
{
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();

    m_posAttr = m_shader->attributeLocation("posAttr");
    m_colAttr = m_shader->attributeLocation("colAttr");

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(VERTEX_DATA, sizeof(VERTEX_DATA) + sizeof(colors));
    m_vbo->write(sizeof(VERTEX_DATA), colors, sizeof(colors));
    m_vbo->release();

    m_vbo->bind();
    m_shader->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
    m_shader->setAttributeBuffer(m_colAttr, GL_FLOAT, sizeof(VERTEX_DATA), 3);
    m_shader->enableAttributeArray(m_posAttr);
    m_shader->enableAttributeArray(m_colAttr);
    m_vbo->release();

    m_vao->release();
}

void GlWidget::paintGL()
{
    QOpenGLFunctions *f = this->context()->functions();
    const qreal retinaScale = devicePixelRatio();
    f->glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_vao->bind();

    m_shader->bind();
    f->glDrawArrays(GL_TRIANGLES, 0, 3);
    m_shader->release();

    m_vao->release();
}

void GlWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}
