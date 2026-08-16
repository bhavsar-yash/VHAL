cmake_minimum_required(VERSION 3.16)
project(vhal_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vhalcore STATIC
    src/CanSignalDecoder.cpp
    src/PropertyMapper.cpp
    src/CanVhalPipeline.cpp
    sim/DevelopmentCanTransport.cpp
)

target_include_directories(vhalcore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(vehicle_speed_pipeline_test
    tests/VehicleSpeedPipelineTest.cpp
)

target_link_libraries(vehicle_speed_pipeline_test PRIVATE vhalcore)

enable_testing()
add_test(NAME vehicle_speed_pipeline_test COMMAND vehicle_speed_pipeline_test)
