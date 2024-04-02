cmake_minimum_required(VERSION 3.5)

project(MS-office-installer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(QT_NO_DEBUG_OUTPUT)
    add_compile_definitions(QT_NO_INFO_OUTPUT)
else ()
    add_compile_definitions(DEBUG)
endif ()

add_compile_definitions(SEPARATOR="------")

set(TS_FILES translations/MS-office-installer_it_IT.ts)

set(PROJECT_SOURCES
        main.cpp
        src/Installer/Installer.hpp
        src/Installer/Installer.cpp
        src/Installer/Installer.ui
        src/LanguageSelector/LanguageSelector.ui
        src/LanguageSelector/LanguageSelector.hpp
        src/LanguageSelector/LanguageSelector.cpp
        src/OfficeDeploymentTool/OfficeDeploymentTool.hpp
        src/OfficeDeploymentTool/OfficeDeploymentTool.cpp
        src/ConfigGenerator/ConfigGenerator.hpp
        src/ConfigGenerator/ConfigGenerator.cpp
        ${TS_FILES}
        src/DataModel/DataModel.hpp
        res/icons.rc)

qt_add_executable(MS-office-installer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
)

target_link_libraries(MS-office-installer
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

qt_add_translations(MS-office-installer
        TS_FILES ${TS_FILES}
        SOURCES src/LanguageSelector/LanguageSelector.ui src/Installer/Installer.ui src/Installer/Installer.cpp
        LUPDATE_OPTIONS -no-ui-lines -no-obsolete
)

#qt_add_lupdate(MS-office-installer
#        TS_FILES ${TS_FILES}
#        SOURCES src/LanguageSelector.ui src/Installer.ui src/installer.cpp
#        OPTIONS -no-obsolete -no-ui-lines
#        )

qt_add_resources(MS-office-installer "contents"
        PREFIX "/"
        FILES
        res/contents.json
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(MS-office-installer PROPERTIES
            WIN32_EXECUTABLE TRUE #prevent creating console
    )
else ()
    set_target_properties(MS-office-installer PROPERTIES
            WIN32_EXECUTABLE FALSE #create console
    )
endif ()

install(TARGETS MS-office-installer
        BUNDLE DESTINATION .
        RUNTIME DESTINATION .
)

qt_generate_deploy_script(TARGET MS-office-installer
        OUTPUT_SCRIPT deploy_script
        CONTENT "
            qt_deploy_runtime_dependencies(
                EXECUTABLE MS-office-installer.exe
                BIN_DIR .
                )
            qt_deploy_qt_conf(
                ${CMAKE_INSTALL_PREFIX}/qt.conf
                BIN_DIR ./bin
                PLUGINS_DIR ./plugins
                TRANSLATIONS_DIR ./translations
                )"
)
install(SCRIPT ${deploy_script})

qt_finalize_executable(MS-office-installer)
