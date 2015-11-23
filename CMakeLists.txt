cmake_minimum_required(VERSION 2.8.0)

project(duplo-gui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

file(GLOB ${CMAKE_PROJECT_NAME}Sources "*.cpp")
file(GLOB ${CMAKE_PROJECT_NAME}Headers "*.h")
file(GLOB ${CMAKE_PROJECT_NAME}Resources "*.qrc" )
file(GLOB ${CMAKE_PROJECT_NAME}UIS "*.ui")

qt5_add_resources(${CMAKE_PROJECT_NAME}ResourceSources ${${CMAKE_PROJECT_NAME}Resources})
qt5_wrap_ui(${CMAKE_PROJECT_NAME}UI_SRCS ${${CMAKE_PROJECT_NAME}UIS})

add_executable(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}Sources} ${${CMAKE_PROJECT_NAME}Headers} 
	${${CMAKE_PROJECT_NAME}ResourceSources} ${${CMAKE_PROJECT_NAME}UI_SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets)
qt5_use_modules(${CMAKE_PROJECT_NAME} Widgets)

if (UNIX)
  install(TARGETS ${CMAKE_PROJECT_NAME}
          RUNTIME DESTINATION bin)
elseif (WIN32)
  install(TARGETS ${CMAKE_PROJECT_NAME}
          DESTINATION .)
endif()
