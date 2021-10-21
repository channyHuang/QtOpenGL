#include "glwidget.h"

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent), m_vbo(nullptr), m_vao(nullptr), m_shader(nullptr){

}
GlWidget::~GlWidget(){

}

static const char* VERTEX_SHADER_CODE =
        "#version 410 core                                                 \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
        "                                                                  \n"
        "    gl_Position = vertices[gl_VertexID];                          \n"
        "}                                                                 \n";

static const char* FRAGMENT_SHADER_CODE =
        "#version 410 core                                                 \n"
       "                                                                  \n"
       "out vec4 color;                                                   \n"
       "                                                                  \n"
       "void main(void)                                                   \n"
       "{                                                                 \n"
       "    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
       "}                                                                 \n";

static const char* TESSELLATE_CONTROL_SHADER_CODE =
        "#version 410 core                                                                 \n"
        "                                                                                  \n"
        "layout (vertices = 3) out;                                                        \n"
        "                                                                                  \n"
        "void main(void)                                                                   \n"
        "{                                                                                 \n"
        "    if (gl_InvocationID == 0)                                                     \n"
        "    {                                                                             \n"
        "        gl_TessLevelInner[0] = 5.0;                                               \n"
        "        gl_TessLevelOuter[0] = 5.0;                                               \n"
        "        gl_TessLevelOuter[1] = 5.0;                                               \n"
        "        gl_TessLevelOuter[2] = 5.0;                                               \n"
        "    }                                                                             \n"
        "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
        "}                                                                                 \n";

static const char* TESSELLATE_EVALIUATION_SHADER_CODE =
        "#version 410 core                                                                 \n"
        "                                                                                  \n"
        "layout (triangles, equal_spacing, cw) in;                                         \n"
        "                                                                                  \n"
        "void main(void)                                                                   \n"
        "{                                                                                 \n"
        "    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
        "                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
        "                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
        "}                                                                                 \n";

void GlWidget::initializeGL()
{
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, VERTEX_SHADER_CODE);
    m_shader->addShaderFromSourceCode(QOpenGLShader::TessellationControl, TESSELLATE_CONTROL_SHADER_CODE);
    m_shader->addShaderFromSourceCode(QOpenGLShader::TessellationEvaluation, TESSELLATE_EVALIUATION_SHADER_CODE);
    m_shader->addShaderFromSourceCode(QOpenGLShader::Fragment, FRAGMENT_SHADER_CODE);
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }

    m_vao = new QOpenGLVertexArrayObject();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vao->create();
    m_vao->bind();

    m_vbo->create();
    m_vbo->bind();

    m_vbo->release();
    m_vao->release();
}

void GlWidget::paintGL()
{
    static const GLfloat green[] = {0.f, 0.25f, 0.f, 1.f};
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(green[0], green[1], green[2], green[3]);
    m_vao->bind();
    m_shader->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    f->glDrawArrays(GL_PATCHES, 0, 3);
    m_shader->release();
    m_vao->release();
}

void GlWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}
