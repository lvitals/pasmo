cmake_minimum_required(VERSION 3.10)
project(pasmo)

# Define the version
set(PASMO_VERSION "0.5.5")
add_definitions(-DVERSION="${PASMO_VERSION}")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Project source files
set(SOURCES
    asm.h asm.cxx
    asmerror.h asmerror.cxx
    asmfile.h asmfile.cxx
    cpc.h cpc.cxx
    macro.h macro.cxx
    nullstream.h nullstream.cxx
    pasmotypes.h pasmotypes.cxx
    spectrum.h spectrum.cxx
    tap.h tap.cxx
    token.h token.cxx
    tzx.h tzx.cxx
)

# Create the main executable 'pasmo'
add_executable(pasmo pasmo.cxx ${SOURCES})

# ---------------------------------------------------
# Common test sources
# ---------------------------------------------------
set(TEST_COMMON_SOURCES
    test_protocol.cxx
    test_protocol.h
)

# ---------------------------------------------------
# Build the 'test_token' executable
# ---------------------------------------------------
add_executable(test_token 
    test_token.cxx 
    ${TEST_COMMON_SOURCES}
    ${SOURCES}  # Add only the necessary files to test tokens
)

# ---------------------------------------------------
# Build the 'test_asm' executable
# ---------------------------------------------------
add_executable(test_asm 
    test_asm.cxx 
    ${TEST_COMMON_SOURCES}
    ${SOURCES}  # Add only the necessary files to test ASM
)

# ---------------------------------------------------
# Add tests to CTest
# ---------------------------------------------------
enable_testing()

add_test(NAME test_token COMMAND test_token)
add_test(NAME test_asm COMMAND test_asm)

# ---------------------------------------------------
# Define the LOG_DRIVER variable (custom log driver for TAP)
# ---------------------------------------------------
set(LOG_DRIVER "env AM_TAP_AWK='${AWK}' ${CMAKE_SHELL} ${CMAKE_SOURCE_DIR}/tap-driver.sh")

# ---------------------------------------------------
# Define custom tests
# ---------------------------------------------------
set(TESTS
    test_token
    test_asm
    test_cli.sh
)
