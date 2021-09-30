TEMPLATE      = subdirs

#pro_files = $$files($$PWD/*/*.pro, true)

SUBDIRS  += $$PWD/QtOpenGL-window/QtOpenGL-window.pro \
            $$PWD/QtOpenGL-polygon/QtOpenGL-polygon.pro \
            $$PWD/QtOpenGL-color/QtOpenGL-color.pro \
            $$PWD/QtOpenGL-rotate/QtOpenGL-rotate.pro \
            $$PWD/QtOpenGL-3d/QtOpenGL-3d.pro \
            $$PWD/QtOpenGL-texture/QtOpenGL-texture.pro \
            $$PWD/QtOpenGL-light/QtOpenGL-light.pro \
            $$PWD/hellogl2/hellogl2.pro
