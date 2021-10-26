#ifndef TEXTOVERLAY_H
#define TEXTOVERLAY_H

#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QString>

#include "ktxloader.h"

class textOverlay
{
public:
    textOverlay();
    ~textOverlay();

    void init(int width, int height, const char* font = nullptr);
    void updateOpenGLFunctions(QOpenGLFunctions_4_2_Core *f);
    void paintGL();
    void drawText(const char* str, int x, int y);
    void scroll(int lines);
    void clear();
    void print(const char* str);
private:
    void initShader();
    void initTexture();

private:
    QOpenGLShaderProgram *m_shader;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLFunctions_4_2_Core *pOpenGLFunc = nullptr;

    GLuint text_buffer, font_texture;

    int buffer_width, buffer_height;

    ktxLoader cTextureLoader;

    QString m_sProPath;

    char* screen_buffer;
    bool dirty = false;
    int cursor_x = 0, cursor_y = 0;
};

#endif // TEXTOVERLAY_H
