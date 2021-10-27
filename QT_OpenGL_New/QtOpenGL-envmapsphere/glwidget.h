#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

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
    QOpenGLFunctions_4_4_Compatibility *f = nullptr;
    QMatrix4x4 projection;

    ObjectLoader objLoader;
    ktxLoader texLoader;

    float currentTime = 0;

    struct {
        GLuint mv_matrix;
        GLuint proj_matrix;
    } uniforms;

    QMatrix4x4 mv_matrix;

    GLuint envmaps[3];
    int index = 0;
};

#endif
