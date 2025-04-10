cmake_minimum_required(VERSION 3.16)

project(Sort_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

qt_add_executable(Sort_app
    ${PROJECT_SOURCES}
    image.qrc
    main_sort.h main_sort.cpp main_sort.ui
    main_app.h main_app.cpp main_app.ui
    choosesort.h choosesort.cpp choosesort.ui
    selectsort.h selectsort.cpp selectsort.ui
    upfile.h upfile.cpp upfile.ui
    sorting.h sorting.cpp

    downfile.h downfile.cpp downfile.ui
    writedata.h writedata.cpp writedata.ui
    outdata.h outdata.cpp outdata.ui
    randomdata.h randomdata.cpp randomdata.ui
    inforofsort.h inforofsort.cpp inforofsort.ui
    choosetocomparion.h choosetocomparion.cpp choosetocomparion.ui
    outcomparion.h outcomparion.cpp outcomparion.ui

)

target_link_libraries(Sort_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Sort_app PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Sort_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sort_app)
endif()
