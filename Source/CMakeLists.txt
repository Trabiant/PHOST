cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(PHOST LANGUAGES CXX CUDA)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64")

if(WIN32)
    set(ENV{QML_IMPORT_PATH} "C:/Qt/6.9.0/msvc2022_64/qml")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_COMPILER
    "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.9/bin/nvcc.exe"
    CACHE FILEPATH "Full path to nvcc" FORCE)
set(CMAKE_CUDA_STANDARD       17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS    ON)
add_compile_options(
  "$<$<COMPILE_LANGUAGE:CUDA>:--expt-relaxed-constexpr>"
)
set(CMAKE_AUTOUIC  ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.9 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Quick
    QuickWidgets
)
find_package(CUDAToolkit REQUIRED)

include(FetchContent)
FetchContent_Declare(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.11.0
)
set(SPDLOG_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SPDLOG_BUILD_TESTS    OFF CACHE_INTERNAL "")
FetchContent_MakeAvailable(spdlog)

set(OpenCV_DIR "C:/opencv/opencv/build" CACHE PATH "Path to OpenCVConfig.cmake")
find_package(OpenCV REQUIRED
    COMPONENTS core imgproc imgcodecs highgui calib3d features2d flann videoio
)
message(STATUS "OpenCV include: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs:    ${OpenCV_LIBS}")

set(EIGEN3_INCLUDE_DIR "C:/eigen-3.4.0" CACHE PATH "")
set(SOURCES
  DatasetManager.cpp
  PhotometricStereo.cpp
  RCProcessLauncher.cpp
  TextureGenerator.cpp
  CameraPositionManager.cpp
  ProgressManager.cpp
  Main.cpp
  NormalConverter.cpp
  Window.ui         Window.cpp         Window.h
  ProjectWindow.ui  ProjectWindow.cpp  ProjectWindow.h
  Worker.h
  CameraPosition.h  CameraPositionManager.h
  NormalConverter.cu
  PhotometricStereo.cu
  Config.h
  DatasetManager.h
  ImageData.h
  ImageExtensions.h
  NormalConverter.h
  PhotometricStereo.h
  ProgressManager.h
  RCProcessLauncher.h
  TextureGenerator.h
  MaskEditorView.h
  MaskEditorView.cpp
  HandleItem.h     HandleItem.cpp
  ResizableEllipseItem.h  ResizableEllipseItem.cpp
  Resources.qrc
)

if (WIN32)
  add_executable(${PROJECT_NAME}
    WIN32
    ${SOURCES}
    Resources.qrc
    app.rc
    RainbowText.h
    SlidingIndicatorWidget.h
    RainbowText.cpp
    SlidingIndicatorWidget.cpp
    Worker.cpp
  )
else()
  add_executable(${PROJECT_NAME}
    ${SOURCES}
    Resources.qrc
  )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickWidgets
    spdlog::spdlog ${OpenCV_LIBS} CUDA::cudart
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Config"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Config"
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>:/Zm800>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CUDA_SEPARABLE_COMPILATION ON
  CUDA_ARCHITECTURES "50;52;61;70;75;80;86;89;100"
)

if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
  set(OPENCV_BIN_DIR "C:/opencv/opencv/build/x64/vc16/bin")
  set(CUDA_BIN_DIR  "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.9/bin")

  file(GLOB OPENCV_DLLS "${OPENCV_BIN_DIR}/opencv_world*.dll")
  file(GLOB CUDA_DLLS  "${CUDA_BIN_DIR}/cudart*.dll"
                       "${CUDA_BIN_DIR}/cublas*.dll"
                       "${CUDA_BIN_DIR}/cudnn*.dll")

  if (OPENCV_DLLS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${OPENCV_DLLS}
              $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
  endif()
  if (CUDA_DLLS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${CUDA_DLLS}
              $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
  endif()
endif()
