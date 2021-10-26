#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLFunctions_4_2_Compatibility>

#include "glstructs.h"

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    inline void render(unsigned int instance_count = 1,
                           unsigned int base_instance = 0,
                       QOpenGLFunctions_4_2_Core *f = nullptr)
        {
            render_sub_object(0, instance_count, base_instance, f);
        }

    inline void render(unsigned int instance_count = 1,
                           unsigned int base_instance = 0,
                       QOpenGLFunctions_4_2_Compatibility *f = nullptr)
        {
            render_sub_object(0, instance_count, base_instance, f);
        }

        void render_sub_object(unsigned int object_index,
                               unsigned int instance_count = 1,
                               unsigned int base_instance = 0,
                               QOpenGLFunctions_4_2_Core *f = nullptr);

        void render_sub_object(unsigned int object_index,
                               unsigned int instance_count = 1,
                               unsigned int base_instance = 0,
                               QOpenGLFunctions_4_2_Compatibility *f = nullptr);

        void get_sub_object_info(unsigned int index, GLuint &first, GLuint &count)
        {
            if (index >= num_sub_objects)
            {
                first = 0;
                count = 0;
            }
            else
            {
                first = sub_object[index].first;
                count = sub_object[index].count;
            }
        }

        unsigned int get_sub_object_count() const           { return num_sub_objects; }
        GLuint       get_vao() const                        { return vao; }
        void load(const char * filename, QOpenGLFunctions_4_2_Core *f);
        void load(const char * filename, QOpenGLFunctions_4_2_Compatibility *f);
        void free(QOpenGLFunctions_4_2_Core *f);
        void free(QOpenGLFunctions_4_2_Compatibility *f);

private:
    GLuint                  data_buffer;
    GLuint                  vao;
    GLuint                  index_type;
    GLuint                  index_offset;

    enum { MAX_SUB_OBJECTS = 256 };

    unsigned int            num_sub_objects;
    SB6M_SUB_OBJECT_DECL    sub_object[MAX_SUB_OBJECTS];
};

#endif // OBJECTLOADER_H
