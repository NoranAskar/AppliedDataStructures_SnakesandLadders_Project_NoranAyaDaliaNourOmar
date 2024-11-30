project(Code_lib)

set(HEADER_FILES
        snakes_and_ladders.h
        DEQ.h
)

set(SOURCE_FILES
        snakes_and_ladders.cpp
        DEQ.cpp
)

add_library(Code_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})