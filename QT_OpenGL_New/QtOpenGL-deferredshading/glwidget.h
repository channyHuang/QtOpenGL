#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "objectloader.h"
#include "ktxloader.h"

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    enum
    {
        MAX_DISPLAY_WIDTH = 2048,
        MAX_DISPLAY_HEIGHT = 2048,
        NUM_LIGHTS = 64,
        NUM_INSTANCES = (15 * 15)
    };

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

    QOpenGLShaderProgram *m_shader, *m_shader_light, *m_shader_nm, *m_shader_vis;
    QOpenGLVertexArrayObject *m_vao;

    QMatrix4x4 projection;

    struct {
        GLint loc_vis_mode;
        GLint offset;
    } uniforms;

    GLuint tex_nm, tex_diffuse;
    GLuint gbuffer_tex[3];

    ktxLoader cKtxLoader;
    ObjectLoader objLoader;
    QOpenGLFunctions_4_2_Core *f = nullptr;

    float currentTime = 0;
};

#endif
