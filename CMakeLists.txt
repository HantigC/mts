cmake_minimum_required(VERSION 3.5)
project(mts LANGUAGES CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
foreach(CFGNAME Debug Release)
    string(TOUPPER ${CFGNAME} UPPER_CFGNAME)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_CFGNAME} ${CMAKE_BINARY_DIR}/bin/${CFGNAME})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_CFGNAME} ${CMAKE_BINARY_DIR}/lib/${CFGNAME})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_CFGNAME} ${CMAKE_BINARY_DIR}/lib/${CFGNAME})
endforeach()

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)


set(MOCV_SRCS_LIST
    src/camera.cpp
    src/opencvx.cpp

    src/geometry/epipolar.cpp
    src/geometry/triangulation.cpp

    src/visualization/camera.cpp

    src/render/model/base.cpp
    src/render/model/camera.cpp
    src/render/model/pcl.cpp

    src/epipolar/draw.cpp

    src/keypoint/draw.cpp

    src/sfm.cpp

    src/utils/convert/cv.cpp
    src/utils/extend/cv/image.cpp
)

set(MOCV_HEADERS_LIST
    src/camera.h
    src/opencvx.h

    src/geometry/epipolar.h
    src/geometry/triangulation.h

    src/visualization/camera.h

    src/render/model/base.h
    src/render/model/camera.h
    src/render/model/pcl.h

    src/epipolar/draw.h
    src/keypoint/draw.h

    src/sfm.h

    src/utils/convert/cv.h
    src/utils/extend/cv/image.h

    )

add_executable( mts 
    src/main.cpp
    ${MOCV_SRCS_LIST}
    ${MOCV_HEADERS_LIST}
    )


find_package(OpenCV REQUIRED)
find_package(Pangolin REQUIRED)
#find_package(Ceres REQUIRED)


target_include_directories(mts PRIVATE include)
target_include_directories(mts PRIVATE src)
target_include_directories(mts PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(mts PRIVATE "/usr/include/eigen3" )
target_include_directories(mts PRIVATE ${Pangolin_INCLUDE_DIRS})
#target_include_directories(mts PRIVATE ${CERES_INCLUDE_DIRS})
#target_link_libraries(mts ${CERES_LIBRARIES})
target_link_libraries(mts ${OpenCV_LIBS})
target_link_libraries(mts ${Pangolin_LIBRARIES})