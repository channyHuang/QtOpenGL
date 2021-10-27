#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "objectloader.h"

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

    ObjectLoader objLoader;

    float currentTime = 0;

    struct {
        GLint diffuse_albedo;
        GLint specular_albedo;
        GLint specular_power;

        GLuint mv_matrix;
        GLuint proj_matrix;
        GLuint view_matrix;
    } uniforms[2];

    GLuint uniforms_buffer;
    QVector3D view_position, light_position;
    QMatrix4x4 model_matrix;
    QMatrix4x4 view_matrix, light_proj_matrix, light_view_matrix;
};

#endif
