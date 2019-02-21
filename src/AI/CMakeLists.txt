INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include" )

aux_source_directory(. DIR_LIB_SRCS)
add_library (AI_LIB ${DIR_LIB_SRCS})
