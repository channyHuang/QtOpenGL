cmake_minimum_required(VERSION 3.0)

Project(misRender)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)

file(GLOB ALL_SOURCES
	main.cpp
	misrender.*
	GLWidget.*
	)
	
set(MISTUDIO_HEADERS
	GLWidget.h
	misrender.h
	)
	
set(MISTUDIO_UIS
	misrender.ui
	)
	
set(MISTUDIO_QRCS misrender.qrc)	
	
QT5_WRAP_CPP (MISTUDIO_HEADERS_MOC ${MISTUDIO_HEADERS})
QT5_WRAP_UI (MISTUDIO_UIS_UIC ${MISTUDIO_UIS})
QT5_ADD_RESOURCES (MISTUDIO_QRC_RCC ${MISTUDIO_QRCS})	
	
ADD_EXECUTABLE(misRender
	${ALL_SOURCES}
	${MISTUDIO_HEADERS_MOC}
	${MISTUDIO_UIS_UIC}
	${MISTUDIO_QRC_RCC}
	)
	
qt5_use_modules(misRender Widgets Gui Core OpenGL)	
	
TARGET_LINK_LIBRARIES(misRender
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	Qt5::OpenGL
	)