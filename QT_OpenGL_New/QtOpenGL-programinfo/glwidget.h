#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "textoverlay.h"

static const struct type_to_name_entry
{
    GLenum type;
    const char * name;
}

type_to_name_table[] =
{
    GL_FLOAT,                       "float",
    GL_FLOAT_VEC2,                  "vec2",
    GL_FLOAT_VEC3,                  "vec3",
    GL_FLOAT_VEC4,                  "vec4",
    GL_DOUBLE,                      "double",
    GL_DOUBLE_VEC2,                 "dvec2",
    GL_DOUBLE_VEC3,                 "dvec3",
    GL_DOUBLE_VEC4,                 "dvec4",
    GL_INT,                         "int",
    GL_INT_VEC2,                    "ivec2",
    GL_INT_VEC3,                    "ivec3",
    GL_INT_VEC4,                    "ivec4",
    GL_UNSIGNED_INT,                "uint",
    GL_UNSIGNED_INT_VEC2,           "uvec2",
    GL_UNSIGNED_INT_VEC3,           "uvec3",
    GL_UNSIGNED_INT_VEC4,           "uvec4",
    GL_BOOL,                        "bool",
    GL_BOOL_VEC2,                   "bvec2",
    GL_BOOL_VEC3,                   "bvec3",
    GL_BOOL_VEC4,                   "bvec4",
    GL_NONE,                        NULL
};

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
    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;

    QString sProPath;
    QMatrix4x4 projection;
    QTimer timer;

    struct {
        GLint mv_matrix;
        GLint proj_matrix;
    } uniforms;

    textOverlay overlay;
    QOpenGLFunctions_4_3_Compatibility *f = nullptr;

    float currentTime = 0;

};

#endif
