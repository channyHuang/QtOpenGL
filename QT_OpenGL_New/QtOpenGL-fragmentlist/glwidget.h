#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QVector4D>
#include <QMatrix4x4>

#include <cmath>

#include "objectloader.h"
#include "ktxloader.h"

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

    QOpenGLShaderProgram *m_append_shader, *m_clear_shader, *m_resolve_shader;
    QOpenGLVertexArrayObject *m_vao;

    ObjectLoader objLoader;
    QOpenGLFunctions_4_2_Core *f = nullptr;

    float currentTime = 0;

    struct {
        GLint mvp;
    } uniforms;

    GLuint uniforms_buffer, fragment_buffer, head_pointer_image, atomic_counter_buffer;

    struct uniforms_block {
        QMatrix4x4 mv_matrix;
        QMatrix4x4 view_matrix;
        QMatrix4x4 proj_matrix;
    };

    struct {
        GLuint color;
        GLuint normals;
    } textures;

    QMatrix4x4 projection, model_matrix, view_matrix;
};

#endif
