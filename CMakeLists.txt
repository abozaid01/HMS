cmake_minimum_required(VERSION 3.5)

project(HMS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        welcome.h welcome.cpp welcome.ui
        admin.h admin.cpp admin.ui
        patient.h patient.cpp
        adminportal.h adminportal.cpp adminportal.ui
        patientdetail.h patientdetail.cpp patientdetail.ui
        receptionist.h receptionist.cpp receptionist.ui
        receptionistdetail.h receptionistdetail.cpp receptionistdetail.ui
        doctor.h doctor.cpp doctor.ui
        doctordetail.h doctordetail.cpp doctordetail.ui
        resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HMS
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET HMS APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(HMS SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(HMS
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(HMS PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(HMS PRIVATE Qt6::Sql)


set_target_properties(HMS PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HMS)
endif()
