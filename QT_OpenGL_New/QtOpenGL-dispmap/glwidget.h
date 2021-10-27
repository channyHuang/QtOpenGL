#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "ktxloader.h"

#include <cmath>

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

private:
    QString m_sProPath;
    QTimer timer;

    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLFunctions_4_4_Compatibility *f = nullptr;
    QMatrix4x4 projection;

    ktxLoader texLoader;

    float currentTime = 0;

    struct {
        GLuint mv_matrix;
        GLuint proj_matrix;
        GLuint mvp_matrix;
        GLuint dmap_depth;
        GLuint enable_fog;
    } uniforms;

    QMatrix4x4 mv_matrix;
    GLuint tex_displacement, tex_color;

    float dmap_depth = 6.0f;
    float total_time = 0, last_time = 0;
    bool wireframe = true, enable_fog = false, enable_displacement = true;
};

#endif
