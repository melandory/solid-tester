project(Solid-Test)
cmake_minimum_required(VERSION 2.6.2)

find_package(Qt4 4.6.3 COMPONENTS QtCore REQUIRED)
find_package( KDE4 REQUIRED )

include_directories( 
    ${KDE4_INCLUDE_DIR}
    ${QT_INCLUDES}
)

set(SOLID_TESTER_SRC
    main.cpp
)

set(SOLID_TESTER_H
    AudioCdTest.h
)

qt4_wrap_cpp(SOLID_TESTER_MOC_FILES ${SOLID_TESTER_H})
add_executable(solidtest ${SOLID_TESTER_SRC} ${SOLID_TESTER_MOC_FILES})
target_link_libraries(solidtest ${KDE4_SOLID_LIBRARY} ${QT_QTCORE_LIBRARY})

