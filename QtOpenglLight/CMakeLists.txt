cmake_minimum_required(VERSION 3.0)

project(OpenglLightDemo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 REQUIRED)
find_package(Qt5OpenGL REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
endif()

if(QT_WITH_OPENGL)
	find_package(OPENGL REQUIRED)
    find_package(QT5OpenGL REQUIRED)
    qt5_use_modules(${MODULE_NAME} OpenGL)
    target_link_libraries(${MODULE_NAME} ${OPENGL_LIBRARY})
endif()


file(GLOB ALL_SOURCES
	data.*
	glm.*
	mainGLWidget.*
	model.*
	modelGLWidget.*
	objdata.*
	relightingdraft.*
	main.cpp
	)
	
set(MISTUDIO_HEADERS
	mainGLWidget.h
	modelGLWidget.h
	relightingdraft.h
	)
	
set(MISTUDIO_UIS
	relightingdraft.ui
	)
	
set(MISTUDIO_QRCS relightingdraft.qrc)
	
QT5_WRAP_CPP(MISTUDIO_HEADERS_MOC ${MISTUDIO_HEADERS})
QT5_WRAP_UI(MISTUDIO_UIS_UIC ${MISTUDIO_UIS})
QT5_ADD_RESOURCES(MISTUDIO_QRC_RCC ${MISTUDIO_QRCS})

add_executable(OpenglLightDemo
	${ALL_SOURCES}
	${MISTUDIO_HEADERS_MOC}
	${MISTUDIO_UIS_UIC}
	${MISTUDIO_QRC_RCC}
	relightingdraft.qrc
	)

target_link_libraries(OpenglLightDemo
	${OpenGL_LIBS}
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	Qt5::OpenGL
	)	
