cmake_minimum_required(VERSION 3.10)
project(TRY_FOREIGN_KEY_PERFMANCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directories
set(SQLITE_DIR ${CMAKE_SOURCE_DIR}/bin/sqlite3)
set(VERSION_01_DIR ${CMAKE_SOURCE_DIR}/version_01)
set(VERSION_01_LIB_DIR ${VERSION_01_DIR}/lib)

# Clone SQLite only if the directory itself doesn't exist
if(NOT EXISTS ${SQLITE_DIR})
    message(STATUS "Cloning SQLite3 repository into ${SQLITE_DIR}...")
    execute_process(
        COMMAND git clone https://github.com/sqlite/sqlite.git ${SQLITE_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE GIT_RESULT
        OUTPUT_VARIABLE GIT_OUTPUT
        ERROR_VARIABLE GIT_ERROR
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone SQLite repository:\n${GIT_ERROR}")
    endif()
else()
    message(STATUS "SQLite directory exists, skipping clone.")
endif()

# Check if sqlite3.c exists, if not build it from source
if(NOT EXISTS ${SQLITE_DIR}/sqlite3.c)
    message(STATUS "sqlite3.c not found in ${SQLITE_DIR}. Building from source...")
    
    # Check if we have the source files needed to build
    if(NOT EXISTS ${SQLITE_DIR}/configure)
        message(FATAL_ERROR "SQLite source files not found. The repository might be incomplete or corrupted.")
    endif()
    
    # Build SQLite amalgamation
    execute_process(
        COMMAND ./configure
        WORKING_DIRECTORY ${SQLITE_DIR}
        RESULT_VARIABLE CONFIGURE_RESULT
        OUTPUT_VARIABLE CONFIGURE_OUTPUT
        ERROR_VARIABLE CONFIGURE_ERROR
    )
    
    if(NOT CONFIGURE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to configure SQLite:\n${CONFIGURE_ERROR}")
    endif()
    
    execute_process(
        COMMAND make sqlite3.c
        WORKING_DIRECTORY ${SQLITE_DIR}
        RESULT_VARIABLE MAKE_RESULT
        OUTPUT_VARIABLE MAKE_OUTPUT
        ERROR_VARIABLE MAKE_ERROR
    )
    
    if(NOT MAKE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build SQLite amalgamation:\n${MAKE_ERROR}")
    endif()
    
    # Verify that sqlite3.c was created
    if(NOT EXISTS ${SQLITE_DIR}/sqlite3.c)
        message(FATAL_ERROR "sqlite3.c was not created after build process.")
    endif()
    
    message(STATUS "SQLite amalgamation built successfully.")
else()
    message(STATUS "sqlite3.c found, using existing amalgamation.")
endif()

# Build SQLite3 as a static library
add_library(sqlite3 STATIC ${SQLITE_DIR}/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${SQLITE_DIR})

# Add your main executable
add_executable(version_01
    ${VERSION_01_DIR}/main.cpp
    ${VERSION_01_DIR}/queries.cpp
    ${VERSION_01_DIR}/db.cpp
)

# Link everything together
target_link_libraries(version_01 PRIVATE sqlite3)

# Include project headers
target_include_directories(version_01 PRIVATE
    ${VERSION_01_LIB_DIR}
    ${SQLITE_DIR}
)

# Compiler warnings
target_compile_options(version_01 PRIVATE -Wall -Wextra -Wpedantic)