
#project (TestLibrary)

##For the shared library:
#set ( PROJECT_LINK_LIBS libtestStudent.so )
#link_directories( ~/exploringBB/extras/cmake/studentlib_shared/build )

#include_directories(~/exploringBB/extras/cmake/studentlib_shared/include)

#add_executable(libtest libtest.cpp)
#target_link_libraries(libtest ${PROJECT_LINK_LIBS} )

cmake_minimum_required(VERSION 2.8.9)

project(IDStest)

set ( PROJECT_LINK_LIBS libueye_api.so )
link_directories( /usr/lib/ )

include_directories( /usr/lib/ )
#include_directories(${/usr/lib/libueye_api64.so.4.90})

add_executable(${PROJECT_NAME}
    "main.cpp"
    )

find_package( OpenCV REQUIRED )

target_link_libraries( IDStest ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} ${PROJECT_LINK_LIBS} )

