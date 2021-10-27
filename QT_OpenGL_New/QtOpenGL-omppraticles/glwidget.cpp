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
        currentTime += 0.1f;
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

    particles[0] = new PARTICLE[PARTICLE_COUNT];
    particles[1] = new PARTICLE[PARTICLE_COUNT];

    f->glGenBuffers(1, &particle_buffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, particle_buffer);
    f->glBufferStorage(GL_ARRAY_BUFFER,
                    PARTICLE_COUNT * sizeof(PARTICLE),
                    nullptr,
                    GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
    mapped_buffer = (PARTICLE*)f->glMapBufferRange(
        GL_ARRAY_BUFFER,
        0,
        PARTICLE_COUNT * sizeof(PARTICLE),
        GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);

    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        particles[0][i].position[0] = rand() * 1.f / RAND_MAX * 6.0f - 3.0f;
        particles[0][i].position[1] = rand() * 1.f / RAND_MAX * 6.0f - 3.0f;
        particles[0][i].position[2] = rand() * 1.f / RAND_MAX * 6.0f - 3.0f;
        particles[0][i].velocity = particles[0][i].position * 0.001f;

        mapped_buffer[i] = particles[0][i];
    }

    f->glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    f->glBindVertexBuffer(0, particle_buffer, 0, sizeof(PARTICLE));
    f->glEnableVertexAttribArray(0);

    m_shader->release();
    m_vao->release();
}

void GlWidget::initializeGL()
{
    int maxThreads = omp_get_max_threads();
    omp_set_num_threads(maxThreads);

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

    m_shader->release();
    m_vao->release();
}


void GlWidget::update_particles_omp(float deltaTime)
{
    const PARTICLE* const __restrict src = particles[frame_index & 1];
    PARTICLE* const __restrict dst = particles[(frame_index + 1) & 1];

#pragma omp parallel for schedule (dynamic, 16)
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        const PARTICLE& me = src[i];
        QVector3D delta_v(0.f, 0.f, 0.f);

        for (int j = 0; j < PARTICLE_COUNT; j++) {
            if (i == j) continue;
            QVector3D delta_pos = src[j].position - me.position;
            float distance = delta_pos.length();
            QVector3D delta_dir = delta_pos / distance;
            if (distance < 0.005f) distance = 0.005f;
            delta_v += (delta_dir / (distance * distance));
        }
        dst[i].position = me.position + me.velocity;
        dst[i].velocity = me.velocity + delta_v * deltaTime * 0.01f;
        mapped_buffer[i].position = dst[i].position;
    }

    frame_index++;
}

void GlWidget::paintGL()
{
    m_vao->bind();
    m_shader->bind();

    static double previousTime = 0.0;
    float deltaTime = (float)(currentTime - previousTime);
    previousTime = currentTime;

    update_particles_omp(deltaTime);

    static const GLfloat black[] = {0.f, 0.f, 0.f, 0.f};
    f->glViewport(0, 0, this->width(), this->height());
    f->glClearBufferfv(GL_COLOR, 0, black);

    f->glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, PARTICLE_COUNT * sizeof(PARTICLE));
    f->glPointSize(3.0f);
    f->glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);

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
