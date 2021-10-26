#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_2_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QVector4D>

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

    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;

    GLuint tex_alien_array;
    GLuint rain_buffer;

    ktxLoader cKtxLoader;
    ObjectLoader objLoader;
    QOpenGLFunctions_4_2_Compatibility *f = nullptr;

    float currentTime = 0;
    float droplet_x_offset[256], droplet_rot_speed[256], droplet_fall_speed[256];
};

#endif
