cmake_minimum_required(VERSION 3.3)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/gnome-cmake/modules")

project(lampara)

find_package(PkgConfig REQUIRED)
find_package(Vala REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

vala_precompile_target(${PROJECT_NAME}_vala
                       VALA_OBJECTS
                       main.vala
                       application.vala
                       root_window.vala
                       FLAGS --target-glib=2.38
                             --gresources="${CMAKE_CURRENT_SOURCE_DIR}/main.gresource.xml"
                             --header=package.h
                       PACKAGES gtk+-3.0
                                gstreamer-1.0
                                alsa)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GST REQUIRED gstreamer-1.0)
pkg_check_modules(ALSA REQUIRED alsa)

add_custom_command(OUTPUT resources.c
                   COMMAND glib-compile-resources main.gresource.xml --target="${CMAKE_CURRENT_BINARY_DIR}/resources.c" --generate-source
                   WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                   DEPENDS main.gresource.xml root_window.glade)

add_executable(${PROJECT_NAME}
               ${VALA_OBJECTS}
               resources.c
               helpers.c)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_vala)

#target_compile_options(${PROJECT_NAME} PUBLIC -Wall)

target_include_directories(${PROJECT_NAME} PUBLIC ${GLIB_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${GLIB_CFLAGS} ${GLIB_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLIB_LIBRARIES}
                                             ${GLIB_LIBRARY_DIRS}
                                             ${GLIB_LDFLAGS})

target_include_directories(${PROJECT_NAME} PUBLIC ${GTK3_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${GTK3_CFLAGS} ${GTK3_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GTK3_LIBRARIES}
                                             ${GTK3_LIBRARY_DIRS}
                                             ${GTK3_LDFLAGS})

target_include_directories(${PROJECT_NAME} PUBLIC ${GST_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${GST_CFLAGS} ${GST_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GST_LIBRARIES}
                                             ${GST_LIBRARY_DIRS}
                                             ${GST_LDFLAGS})

target_include_directories(${PROJECT_NAME} PUBLIC ${ALSA_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${ALSA_CFLAGS} ${ALSA_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${ALSA_LIBRARIES}
                                             ${ALSA_LIBRARY_DIRS}
                                             ${ALSA_LDFLAGS})
