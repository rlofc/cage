add_executable(
  wizard 
    src/wizard.cc
)

file(COPY ${CMAKE_SOURCE_DIR}/samples/wizard/res
     DESTINATION
               ${CMAKE_BINARY_DIR}/samples/wizard/)

set_target_properties(wizard
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/samples/wizard/"
)
target_link_libraries(wizard ccage ${COMMON_LIBS})
SET_TARGET_PROPERTIES(wizard PROPERTIES LINKER_LANGUAGE CXX)
