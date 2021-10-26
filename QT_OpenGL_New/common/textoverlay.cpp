#include "textoverlay.h"

#define CONFIG2STR(R) #R
#define CONFIG2QSTR(R) CONFIG2STR(R)

textOverlay::textOverlay()
{
    m_sProPath = CONFIG2QSTR(PRO_PATH);
}

textOverlay::~textOverlay() {
    delete[] screen_buffer;
}

void textOverlay::init(int width, int height, const char* font) {
    buffer_width = width;
    buffer_height = height;

    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();

    initShader();

    initTexture();

    screen_buffer = new char[width * height];
    memset(screen_buffer, 0, width * height);
}

void textOverlay::updateOpenGLFunctions(QOpenGLFunctions_4_2_Core *f) {
    pOpenGLFunc = f;
}

void textOverlay::initShader() {
    m_vao->bind();
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    if (m_shader->link()) {
        qDebug("text Shaders link success.");
    } else {
        qDebug("text Shaders link failed!");
    }

    m_vao->release();
}

void textOverlay::initTexture() {
    if (pOpenGLFunc == nullptr) {
        return;
    }

    m_vao->bind();
    m_shader->bind();

    pOpenGLFunc->glGenTextures(1, &text_buffer);
    pOpenGLFunc->glBindTexture(GL_TEXTURE_2D, text_buffer);
    pOpenGLFunc->glTexStorage2D(GL_TEXTURE_2D, 1, GL_RG8UI, buffer_width, buffer_height);

    font_texture = cTextureLoader.load((m_sProPath + "/brick.ktx").toStdString().c_str(), 0, pOpenGLFunc);

    m_shader->release();
    m_vao->release();
}

void textOverlay::clear() {
    memset(screen_buffer, 0, buffer_width * buffer_height);
    dirty = true;
}

void textOverlay::paintGL() {
    if (pOpenGLFunc == nullptr) {
        return;
    }

    m_vao->bind();
    m_shader->bind();

    pOpenGLFunc->glActiveTexture(GL_TEXTURE0);
    pOpenGLFunc->glBindTexture(GL_TEXTURE_2D, text_buffer);
    if (dirty) {
        pOpenGLFunc->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, buffer_width, buffer_height, GL_RED_INTEGER, GL_UNSIGNED_BYTE, screen_buffer);
        dirty = false;
    }

    pOpenGLFunc->glActiveTexture(GL_TEXTURE1);
    pOpenGLFunc->glBindTexture(GL_TEXTURE_2D, font_texture);

    pOpenGLFunc->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_shader->release();
    m_vao->release();
}

void textOverlay::drawText(const char* str, int x, int y) {
    char *dst = screen_buffer + y * buffer_width + x;
    strcpy(dst, str);
    dirty = true;
}

void textOverlay::scroll(int lines) {
    const char* src = screen_buffer + lines * buffer_width;
    char * dst = screen_buffer;

    memmove(dst, src, (buffer_height - lines) * buffer_width);

    dirty = true;
}

void textOverlay::print(const char *str) {
    const char* p = str;
        char c;
        char* dst = screen_buffer + cursor_y * buffer_width + cursor_x;

        while (*p != 0)
        {
            c = *p++;
            if (c == '\n')
            {
                cursor_y++;
                cursor_x = 0;
                if (cursor_y >= buffer_height)
                {
                    cursor_y--;
                    scroll(1);
                }
                dst = screen_buffer + cursor_y * buffer_width + cursor_x;
            }
            else
            {
                *dst++ = c;
                cursor_x++;
                if (cursor_x >= buffer_width)
                {
                    cursor_y++;
                    cursor_x = 0;
                    if (cursor_y >= buffer_height)
                    {
                        cursor_y--;
                        scroll(1);
                    }
                    dst = screen_buffer + cursor_y * buffer_width + cursor_x;
                }
            }
        }

        dirty = true;
}
