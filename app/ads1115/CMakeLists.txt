add_library(ads1115 STATIC)

target_sources(ads1115 PRIVATE 
    "ads1115.cpp"
)

target_include_directories(ads1115 PUBLIC 
    ${CMAKE_SOURCE_DIR}/app/stm32_utility
)

target_link_libraries(ads1115 PRIVATE
    stm32_utility
    stm32cubemx
)

target_compile_options(ads1115 PUBLIC
    -std=c++23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -fconcepts
)
