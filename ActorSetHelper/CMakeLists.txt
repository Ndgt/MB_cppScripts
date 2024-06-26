project(ActorSetHelper)

add_library(${PROJECT_NAME} SHARED
	tool_register.cpp
	tool.cpp
	widget.cpp
	tool.h
	widget.h 
	BodyIndex.h
	actorsethelper.ui
)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOUIC ON AUTOMOC ON)

target_include_directories(${PROJECT_NAME} PRIVATE)

target_link_libraries(${PROJECT_NAME} PRIVATE fbsdk Qt::Core Qt::Gui Qt::Widgets OpenGL::GL OpenGL::GLU)

mobu_target_finalize(${PROJECT_NAME} plugins)