cmake_minimum_required(VERSION 3.0.0)

set(target QtOpenGLtexture)
project(${target})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


FILE(GLOB HEADERS "*.h" "*.hpp")
FILE(GLOB SOURCES "*.c" "*.cpp")

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(Qt5PrintSupport)

include_directories(${target}
	${OpenGL_DIR}
	)

link_directories(${target}
	${OpenGL_DIR}
	)

add_executable(${target}
	${SOURCES}
	${HEADERS}
	)

target_link_libraries(${target} 
	Qt5::Widgets
	Qt5::PrintSupport
	Qt5::Gui
	Qt5::OpenGL
	${OPENGL_LIBRARIES}
	)

#set as startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target})