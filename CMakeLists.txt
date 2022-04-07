cmake_minimum_required(VERSION 3.14)

project(Praktyka-2-QML VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
        src/main.cpp
        qml/qml.qrc

        include/PImageStreamer.h src/PImageStreamer.cpp
        include/PImageProvider.h src/PImageProvider.cpp
        include/PImageModifierExecutor.h src/PImageModifierExecutor.cpp

        include/PImageModifierList.h src/PImageModifierList.cpp
        include/PEditableImageModifierList.h src/PEditableImageModifierList.cpp
        include/PEditableImageModifierListModel.h src/PEditableImageModifierListModel.cpp

        include/ImageModifiers/PImageModifierBase.h src/ImageModifiers/PImageModifierBase.cpp
        include/ImageModifiers/PFlipHorizontallyImageModifier.h src/ImageModifiers/PFlipHorizontallyImageModifier.cpp
        include/ImageModifiers/PRotateImageModifier.h src/ImageModifiers/PRotateImageModifier.cpp
        include/ImageModifiers/PGaussianBlurImageModifier.h src/ImageModifiers/PGaussianBlurImageModifier.cpp

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Praktyka-2-QML
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Praktyka-2-QML APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Praktyka-2-QML SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Praktyka-2-QML
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(Praktyka-2-QML
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Praktyka-2-QML
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

target_link_libraries(Praktyka-2-QML PRIVATE ${OpenCV_LIBS})

set_target_properties(Praktyka-2-QML PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(Praktyka-2-QML)
    qt_finalize_executable(Praktyka-2-QML)
endif()
