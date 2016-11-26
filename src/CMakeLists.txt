include_directories(${CMAKE_SOURCE_DIR})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(/usr/include/SDL2)

set(SOURCE_FILES 
    animate.c
    cage.c
    color.c
    easing.c
    file.c
    font.c
    geometry.c
    image.c
    keyboard.c
    mouse.c
    screen.c
    sound.c
    sprite.c
    timeline.c
    vec.c
    ccage.cc
    
)

set_source_files_properties(${SOURCE_FILES}
                                       PROPERTIES LANGUAGE CXX)
add_library(
  ccage STATIC
    ${SOURCE_FILES}
)

SET_TARGET_PROPERTIES(ccage PROPERTIES LINKER_LANGUAGE CXX)

