#OpenGL Translation Deom, setting params

SET(CMAKE_PREFIX_PATH  "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib")

PROJECT(glTranslationDemo)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 REQUIRED)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

set(MISTUDIO_HEADERS 
	data.h
	glm.h
	gltranslationdemo.h
	glWindow.h
	glWindow3D.h
	matrixClass.h
	model.h
	objdata.h
	)
	
set(MISTUDIO_UIS
	gltranslationdemo.ui
	)
	
set(MISTUDIO_QRCS gltranslationdemo.qrc)

set(MISTUDIO_SRCS
	data.cpp
	glm.cpp
	gltranslationdemo.cpp
	glWindow.cpp
	glWindow3D.cpp
	matrixClass.cpp
	model.cpp
	objdata.cpp
	main.cpp
	${MISTUDIO_QRCS}
	)

QT5_WRAP_CPP (MISTUDIO_HEADERS_MOC ${MISTUDIO_HEADERS})
QT5_WRAP_UI (MISTUDIO_UIS_UIC ${MISTUDIO_UIS})
QT5_ADD_RESOURCES (MISTUDIO_QRC_RCC ${MISTUDIO_QRCS})
	
add_executable(glTranslationDemo
	${SRC_LIST}
	${MISTUDIO_HEADERS_MOC}
	${MISTUDIO_UIS_UIC}
	${MISTUDIO_QRC_RCC}
	glTranslationdemo.qrc
	)
	
target_link_libraries(glTranslationDemo
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	)