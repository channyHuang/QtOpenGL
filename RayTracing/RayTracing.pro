TEMPLATE      = subdirs

pro_dirs = $$files($$PWD/*, false)
for(pro_dir, pro_dirs) {
    pro_file = $$files($${pro_dir}/*.pro, false)
    SUBDIRS += $${pro_file}
}
