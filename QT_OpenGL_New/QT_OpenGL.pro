TEMPLATE      = subdirs

contains(DEFINES, PRO_MANUAL) {
#SUBDIRS  += $$PWD/QtOpenGL-window/QtOpenGL-window.pro \
#            $$PWD/QtOpenGL-polygon/QtOpenGL-polygon.pro \
#            $$PWD/QtOpenGL-color/QtOpenGL-color.pro \
#            $$PWD/QtOpenGL-rotate/QtOpenGL-rotate.pro \
#            $$PWD/QtOpenGL-3d/QtOpenGL-3d.pro \
#            $$PWD/QtOpenGL-texture/QtOpenGL-texture.pro \
#            $$PWD/QtOpenGL-light/QtOpenGL-light.pro \
#            $$PWD/QtOpenGL-tessellation/QtOpenGL-tessellation.pro \
#            $$PWD/QtOpenGL-tessellation-gs/QtOpenGL-tessellation-gs.pro \
#            $$PWD/QtOpenGL-ktxview/QtOpenGL-ktxview.pro \
#            $$PWD/QtOpenGL-simpletexcoords/QtOpenGL-simpletexcoords.pro \
#            $$PWD/QtOpenGL-tunnel/QtOpenGL-tunnel.pro \
#            $$PWD/QtOpenGL-tunnel/QtOpenGL-tunnel.pro \

} else {
pro_dirs = $$files($$PWD/*, false)
for(pro_dir, pro_dirs) {
    pro_file = $$files($${pro_dir}/*.pro, false)
    SUBDIRS += $${pro_file}
}
}
