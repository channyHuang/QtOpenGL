#include "glwidget.h"

#include <cmath>
#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent), m_vbo(nullptr), m_vao(nullptr), m_shader(nullptr){

}
GlWidget::~GlWidget(){

}

static const char* VERTEX_SHADER_CODE =
    "#version 420 core                                                              \n"
    "                                                                               \n"
    "void main(void)                                                                \n"
    "{                                                                              \n"
    "    const vec4 vertices[] = vec4[](vec4(-1.0, -1.0, 0.5, 1.0),                 \n"
    "                                   vec4( 1.0, -1.0, 0.5, 1.0),                 \n"
    "                                   vec4(-1.0,  1.0, 0.5, 1.0),                 \n"
    "                                   vec4( 1.0,  1.0, 0.5, 1.0));                \n"
    "                                                                               \n"
    "    gl_Position = vertices[gl_VertexID];                                       \n"
    "}                                                                              \n";

static const char* FRAGMENT_SHADER_CODE =
        "#version 430 core                                                              \n"
            "                                                                               \n"
            "uniform sampler2D s;                                                           \n"
            "                                                                               \n"
            "uniform float exposure;\n"
            "\n"
            "out vec4 color;                                                                \n"
            "                                                                               \n"
            "void main(void)                                                                \n"
            "{                                                                              \n"
            "    color = texture(s, gl_FragCoord.xy / textureSize(s, 0)) * exposure;                   \n"
            "}                                                                              \n";

void GlWidget::initializeGL()
{
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceCode(QOpenGLShader::Vertex, VERTEX_SHADER_CODE);
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

    QOpenGLFunctions_4_2_Core *f = this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>();
    if (f == nullptr) {
        qDebug() << "not support opengl 4.2";
        return;
    }

    QString sProPath = CONFIG2QSTR(PRO_PATH);
    m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    f->glGenTextures(1, &texture);
    loader.load((sProPath.toStdString() + "/pattern1.ktx"), texture, f);
    f->glBindTexture(GL_TEXTURE_2D, texture);

    m_vbo->release();
    m_vao->release();
}

void GlWidget::paintGL()
{
    static const GLfloat green[] = {0.f, 0.25f, 0.f, 1.f};
    QOpenGLFunctions_4_2_Core *f = this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>();
    if (f == nullptr) {
        qDebug() << "not support opengl 4.2";
        return;
    }
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(green[0], green[1], green[2], green[3]);
    m_vao->bind();
    m_shader->bind();
    f->glViewport(0, 0, this->width(), this->height());
    f->glUniform1f(0, (float)(std::sin(t) * 16.0 + 16.0));
    t += 1.f;
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    m_shader->release();
    m_vao->release();
}

void GlWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}
