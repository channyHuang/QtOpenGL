SOURCE_FILES = $$files($${PWD}/*.cpp, false)
HEADER_FILES = $$files($${PWD}/*.h, false)

DEFINES += COMMON_PRO_PATH=$${PWD}


SOURCES += $${SOURCE_FILES} \


HEADERS += $${HEADER_FILES} \

RESOURCE_FILES = $$files($${PWD}/*.qrc, false)

RESOURCES += $${RESOURCE_FILES}
