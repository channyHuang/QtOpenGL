#include "glwidget.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

GlWidget::GlWidget(QWidget* parent):
    QOpenGLWidget (parent),
    m_shader(nullptr), m_vao(nullptr)
{
    sProPath = CONFIG2QSTR(PRO_PATH);
    sProPath += "/../resources/";
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

static const char * type_to_name(GLenum type)
{
    for (const type_to_name_entry * ptr = &type_to_name_table[0]; ptr->name != NULL; ptr++)
    {
        if (ptr->type == type)
            return ptr->name;
    }

    return NULL;
}


void GlWidget::initObjects() {
     if (f == nullptr) {
        return;
    }

    overlay.updateOpenGLFunctions(this->context()->versionFunctions<QOpenGLFunctions_4_2_Core>());
    overlay.init(80, 50);

    m_vao->bind();

    static const GLenum props[] = {GL_TYPE, GL_LOCATION, GL_ARRAY_SIZE};
    static const char * prop_name[] = {"type", "location", "array size"};

    GLint outputs, params[4];
    GLchar name[64];
    const char* type_name;
    f->glGetProgramInterfaceiv(m_shader->programId(), GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &outputs);
    char buffer[1024];
    f->glGetProgramInfoLog(m_shader->programId(), sizeof(buffer), NULL, buffer);

    overlay.print("xxxxxxxxxx");
    overlay.print(buffer);

    for(GLint i = 0; i < outputs; i++)
    {
        f->glGetProgramResourceName(m_shader->programId(), GL_PROGRAM_OUTPUT, i, sizeof(name), NULL, name);
        f->glGetProgramResourceiv(m_shader->programId(), GL_PROGRAM_OUTPUT, i, 3, props, 3, NULL, params);
        type_name = type_to_name(params[0]);
        if (params[2] != 0)
        {
            sprintf(buffer, "Index %d: %s %s[%d] @ location %d.\n", i, type_name, name, params[2], params[1]);
        }
        else
        {
            sprintf(buffer, "Index %d: %s %s @ location %d.\n", i, type_name, name, params[1]);
        }
        overlay.print(buffer);
    }

    m_vao->release();
}

void GlWidget::initializeGL()
{
    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();
    //init gl environment
    f = this->context()->versionFunctions<QOpenGLFunctions_4_3_Compatibility>();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //init shader
    initShader();
    //init data
    initObjects();

    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);

    m_vao->release();
}

void GlWidget::paintGL()
{
    m_vao->bind();
    m_shader->bind();

    static const GLfloat black[] = { 0.f, 0.f, 0.f, 1.0f };
    f->glViewport(0, 0, this->width(), this->height());
    f->glClearBufferfv(GL_COLOR, 0, black);

    overlay.paintGL();

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
