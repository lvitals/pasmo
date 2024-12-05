cmake_minimum_required(VERSION 3.10)
project(pasmo)

# Define the version of the project
set(PASMO_VERSION "0.5.5")
add_definitions(-DVERSION="${PASMO_VERSION}")

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# ---------------------------------------------------
# Source files located in the 'src' directory
# ---------------------------------------------------
set(SOURCES
    src/asm.h src/asm.cxx
    src/asmerror.h src/asmerror.cxx
    src/asmfile.h src/asmfile.cxx
    src/cpc.h src/cpc.cxx
    src/macro.h src/macro.cxx
    src/nullstream.h src/nullstream.cxx
    src/pasmotypes.h src/pasmotypes.cxx
    src/spectrum.h src/spectrum.cxx
    src/tap.h src/tap.cxx
    src/token.h src/token.cxx
    src/tzx.h src/tzx.cxx
)

# ---------------------------------------------------
# Create the main executable 'pasmo'
# ---------------------------------------------------
add_executable(pasmo src/pasmo.cxx ${SOURCES})

# ---------------------------------------------------
# Common test sources located in the 'tests' directory
# ---------------------------------------------------
set(TEST_COMMON_SOURCES
    tests/test_protocol.cxx
    tests/test_protocol.h
)

# ---------------------------------------------------
# Build the 'test_token' executable
# ---------------------------------------------------
add_executable(test_token 
    tests/test_token.cxx
    ${TEST_COMMON_SOURCES}
    ${SOURCES}  # Include necessary source files
)

# ---------------------------------------------------
# Build the 'test_asm' executable
# ---------------------------------------------------
add_executable(test_asm 
    tests/test_asm.cxx
    ${TEST_COMMON_SOURCES}
    ${SOURCES}  # Include necessary source files
)

# ---------------------------------------------------
# Enable CTest for running unit tests
# ---------------------------------------------------
enable_testing()

# Add test targets for CTest
add_test(NAME test_token COMMAND test_token)
add_test(NAME test_asm COMMAND test_asm)

# ---------------------------------------------------
# Define the LOG_DRIVER variable for TAP (Test Anything Protocol)
# ---------------------------------------------------
set(LOG_DRIVER "env AM_TAP_AWK='${AWK}' ${CMAKE_SHELL} ${CMAKE_SOURCE_DIR}/tap-driver.sh")

# ---------------------------------------------------
# Custom test scripts located in the 'tests' directory
# ---------------------------------------------------
set(TEST_SCRIPTS
    tests/test_token
    tests/test_asm
    tests/test_cli.sh
)

# Add a custom target to run test scripts using the defined LOG_DRIVER
add_custom_target(run_tests
    COMMAND ${LOG_DRIVER} ${CMAKE_SOURCE_DIR}/${TEST_SCRIPTS}
    DEPENDS test_token test_asm
)
