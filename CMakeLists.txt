cmake_minimum_required(VERSION 3.5)

project(test_qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick QuickControls2  LinguistTools REQUIRED)

set(TS_FILES test_qml_en_US.ts)

if(ANDROID)
    add_library(test_qml SHARED
      main.cpp
      qml.qrc
      ${TS_FILES}
    )
else()
    add_executable(test_qml
      main.cpp
      fbitemrenderer.h
      qml.qrc
      ${TS_FILES}
    )
endif()

target_compile_definitions(test_qml
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(test_qml
  PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 OpenGL32)

if (WIN32)
    target_link_libraries(test_qml PRIVATE OpenGL32)
endif()

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
