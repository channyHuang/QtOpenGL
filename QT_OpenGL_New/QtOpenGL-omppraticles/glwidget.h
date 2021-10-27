#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <omp.h>

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GlWidget(QWidget *partent);
    ~GlWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void initObjects();
    void initShader();

    void update_particles_omp(float deltaTime);
private:
    QString m_sProPath;
    QTimer timer;

    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLFunctions_4_4_Compatibility *f = nullptr;
    QMatrix4x4 projection;

    float currentTime = 0;

    struct PARTICLE {
        QVector3D position, velocity;
    };

    GLuint      particle_buffer;
    PARTICLE *  mapped_buffer;
    PARTICLE *  particles[2];
    int         frame_index = 0;

    const int PARTICLE_COUNT = 1024;
};

#endif
