CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
ENABLE_TESTING()


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

FIND_PACKAGE(Doxygen)
FIND_PACKAGE(Boost REQUIRED)


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -pedantic -Wextra")
SET(SOFT_FLAGS "${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wcast-align -Wfloat-equal -Wpointer-arith")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror-implicit-function-declaration -Wmain -Wmissing-braces")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wparentheses -Wsequence-point -Wreturn-type -Wswitch")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-compare  -Wconversion")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-noreturn  -Wsign-conversion -Wunused ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing -Wstrict-overflow -Wconversion")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdisabled-optimization -Wsuggest-attribute=noreturn ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wsuggest-attribute=pure ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op -Wunsafe-loop-optimizations ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wunused-parameter -Wshadow  -Weffc++")

ADD_DEFINITIONS(-DNOT_USE_ML)


############################
# LIBS
############################

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/ELL/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/)

############################
# LazyChords Lib
############################

SET(LazyChordsLib_SRCS
    src/Music.cpp
    src/MusicRules.cpp
    src/Utilities.cpp
)


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/)
ADD_LIBRARY(LazyChordsLib ${LazyChordsLib_SRCS})


############################
# Tests
############################

#SET(CMAKE_CXX_FLAGS "${SOFT_FLAGS}")
SET(Tests_SRCS
    tests/MusicRulesTest.cpp
    tests/musicTest.cpp
    tests/TestMain.cpp
)

INCLUDE_DIRECTORIES(tests/)
ADD_EXECUTABLE(runTests ${Tests_SRCS})
TARGET_LINK_LIBRARIES(runTests LazyChordsLib)
TARGET_LINK_LIBRARIES(runTests m)

ADD_TEST(runTests runTests -d yes)

############################
# DOxygen
############################
IF(DOXYGEN_FOUND)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    ADD_CUSTOM_TARGET(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
ENDIF(DOXYGEN_FOUND)


############################
# Coverage
############################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage_cobertura(Lazychord_lib_coverage ${PROJECT_SOURCE_DIR}/runTests coverage)
endif()