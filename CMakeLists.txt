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
    src/data/inmemory_ds.cpp

    src/geometry/epipolar.cpp
    src/geometry/triangulation.cpp
    src/geometry/pose.cpp
    src/geometry/rigid3d.cpp

    src/geometry/fundamental.cpp
    src/geometry/essential.cpp

    src/visualization/camera.cpp

    src/render/model/base.cpp
    src/render/model/camera.cpp
    src/render/model/pcl.cpp

    # src/model/image.cpp
    # src/model/camera.cpp

    src/epipolar/draw.cpp
    src/keypoint/draw.cpp

    src/keypoint/sift.cpp

    src/match/bf.cpp

    src/sfm/sfm.cpp

    src/util/convert/cv.cpp
    src/util/extend/cv/image.cpp
)

set(MOCV_HEADERS_LIST
    src/data/dataset.h
    src/data/inmemory_ds.h

    src/geometry/epipolar.h
    src/geometry/fundamental.h
    src/geometry/essential.h
    src/geometry/triangulation.h
    src/geometry/pose.h
    src/geometry/rigid3d.h

    src/model/image.h
    src/model/camera.h
    src/model/keypoint.h

    src/visualization/camera.h

    src/render/model/base.h
    src/render/model/camera.h
    src/render/model/pcl.h

    src/epipolar/draw.h
    src/keypoint/draw.h

    src/keypoint/sift.h
    src/keypoint/keypoint.h
    src/match/match.h
    src/match/bf.h

    src/sfm/sfm.h
    src/util/types.h

    src/util/convert/cv.h
    src/util/extend/cv/image.h

    )



find_package(OpenCV REQUIRED)
find_package(Pangolin REQUIRED)
#find_package(Ceres REQUIRED)

add_library(mts ${MOCV_SRCS_LIST} ${MOCV_HEADERS_LIST})

target_include_directories(mts PUBLIC src)
target_include_directories(mts PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(mts PUBLIC "/usr/include/eigen3" )
target_include_directories(mts PUBLIC ${Pangolin_INCLUDE_DIRS})
#target_include_directories(mts PRIVATE ${CERES_INCLUDE_DIRS})
#target_link_libraries(mts ${CERES_LIBRARIES})
target_link_libraries(mts ${OpenCV_LIBS})
target_link_libraries(mts ${Pangolin_LIBRARIES})

add_subdirectory(apps)