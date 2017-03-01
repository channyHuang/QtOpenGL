#OpenGL Projection Deom, setting params

SET(CMAKE_PREFIX_PATH  "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib")

PROJECT(glProjectionDemo)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 REQUIRED)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

set(MISTUDIO_HEADERS 
	data.h
	glprojectiondemo.h
	glWindow.h
	glWindow3D.h
	matrixClass.h
	)
	
set(MISTUDIO_UIS
	glprojectiondemo.ui
	)
	
set(MISTUDIO_QRCS glprojectiondemo.qrc)

set(MISTUDIO_SRCS
	data.cpp
	glprojectiondemo.cpp
	glWindow.cpp
	glWindow3D.cpp
	matrixClass.cpp
	main.cpp
	${MISTUDIO_QRCS}
	)

QT5_WRAP_CPP (MISTUDIO_HEADERS_MOC ${MISTUDIO_HEADERS})
QT5_WRAP_UI (MISTUDIO_UIS_UIC ${MISTUDIO_UIS})
QT5_ADD_RESOURCES (MISTUDIO_QRC_RCC ${MISTUDIO_QRCS})
	
add_executable(glProjectionDemo
	${SRC_LIST}
	${MISTUDIO_HEADERS_MOC}
	${MISTUDIO_UIS_UIC}
	${MISTUDIO_QRC_RCC}
	glProjectionDemo.qrc
	)
	
target_link_libraries(glProjectionDemo
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	)