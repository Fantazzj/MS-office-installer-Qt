cmake_minimum_required(VERSION 3.5)

project(MS-office-installer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES translations/MS-office-installer_it_IT.ts)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(QT_NO_DEBUG_OUTPUT)
    add_compile_definitions(QT_NO_INFO_OUTPUT)
endif ()

add_compile_definitions(SEPARATOR="------")

set(PROJECT_SOURCES
        main.cpp
        src/installer.hpp
        src/installer.cpp
        src/installer.ui
        src/languageSelector.ui
        src/languageSelector.hpp
        src/languageSelector.cpp
        src/OfficeDeploymentTool.hpp
        src/OfficeDeploymentTool.cpp
        src/ConfigGenerator.hpp
        src/ConfigGenerator.cpp
        ${TS_FILES}
        )

qt_add_executable(MS-office-installer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )

target_link_libraries(MS-office-installer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MS-office-installer PROPERTIES
        WIN32_EXECUTABLE FAlSE #TRUE to prevent creating console
        )

install(TARGETS MS-office-installer
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(MS-office-installer)
