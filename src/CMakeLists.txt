
add_compile_definitions(_POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)

if(APPLE)
    add_definitions(-D_DARWIN_C_SOURCE)
endif()

find_program(LINT "clang-tidy")
IF (LINT)
    set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,-cppcoreguidelines-init-variables,-clang-analyzer-security.insecureAPI.strcpy,-concurrency-mt-unsafe,-android-cloexec-accept,-android-cloexec-dup,-google-readability-todo,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-cert-dcl03-c,-hicpp-static-assert,-misc-static-assert,-altera-struct-pack-align,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling;--quiet")
ENDIF ()

# Make an executable
add_executable(ascii2morse ${SOURCE_LIST} ${TO_MORSE_MAIN_SOURCE} ${HEADER_LIST})
add_executable(morse2ascii ${SOURCE_LIST} ${TO_ASCII_MAIN_SOURCE} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ascii2morse PRIVATE ../include)
target_include_directories(ascii2morse PRIVATE /usr/include)
target_include_directories(ascii2morse PRIVATE /usr/local/include)
target_link_directories(ascii2morse PRIVATE /usr/lib)
target_link_directories(ascii2morse PRIVATE /usr/local/lib)

target_include_directories(morse2ascii PRIVATE ../include)
target_include_directories(morse2ascii PRIVATE /usr/include)
target_include_directories(morse2ascii PRIVATE /usr/local/include)
target_link_directories(morse2ascii PRIVATE /usr/lib)
target_link_directories(morse2ascii PRIVATE /usr/local/lib)

# All users of this library will need at least C11
target_compile_features(ascii2morse PUBLIC c_std_11)
target_compile_options(ascii2morse PRIVATE -g)
target_compile_options(ascii2morse PRIVATE -fstack-protector-all -ftrapv)
target_compile_options(ascii2morse PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(ascii2morse PRIVATE -Wdouble-promotion -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wnull-dereference -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wunused-local-typedefs -Wstrict-overflow=5 -Wmissing-noreturn -Walloca -Wfloat-equal -Wdeclaration-after-statement -Wshadow -Wpointer-arith -Wabsolute-value -Wundef -Wexpansion-to-defined -Wunused-macros -Wno-endif-labels -Wbad-function-cast -Wcast-qual -Wwrite-strings -Wconversion -Wdangling-else -Wdate-time -Wempty-body -Wsign-conversion -Wfloat-conversion -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wlong-long -Wvariadic-macros -Wdisabled-optimization -Wstack-protector -Woverlength-strings)
target_compile_features(morse2ascii PUBLIC c_std_11)
target_compile_options(morse2ascii PRIVATE -g)
target_compile_options(morse2ascii PRIVATE -fstack-protector-all -ftrapv)
target_compile_options(morse2ascii PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(morse2ascii PRIVATE -Wdouble-promotion -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wnull-dereference -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wunused-local-typedefs -Wstrict-overflow=5 -Wmissing-noreturn -Walloca -Wfloat-equal -Wdeclaration-after-statement -Wshadow -Wpointer-arith -Wabsolute-value -Wundef -Wexpansion-to-defined -Wunused-macros -Wno-endif-labels -Wbad-function-cast -Wcast-qual -Wwrite-strings -Wconversion -Wdangling-else -Wdate-time -Wempty-body -Wsign-conversion -Wfloat-conversion -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wlong-long -Wvariadic-macros -Wdisabled-optimization -Wstack-protector -Woverlength-strings)


find_library(LIBSOCKET socket)
find_library(LIBDC_ERROR dc_error REQUIRED)
find_library(LIBDC_POSIX dc_posix REQUIRED)
find_library(LIBDC_UTIL dc_util REQUIRED)
find_library(LIBDC_FSM dc_fsm REQUIRED)
find_library(LIBDC_APPLICATION dc_application REQUIRED)
find_library(LIBCONFIG config REQUIRED)

target_link_libraries(ascii2morse PRIVATE ${LIBM})
target_link_libraries(ascii2morse PRIVATE ${LIBDC_ERROR})
target_link_libraries(ascii2morse PRIVATE ${LIBDC_POSIX})
target_link_libraries(ascii2morse PRIVATE ${LIBDC_UTIL})
target_link_libraries(ascii2morse PRIVATE ${LIBDC_FSM})
target_link_libraries(ascii2morse PRIVATE ${LIBDC_APPLICATION})
target_link_libraries(ascii2morse PRIVATE ${LIBCONFIG})

target_link_libraries(morse2ascii PRIVATE ${LIBM})
target_link_libraries(morse2ascii PRIVATE ${LIBDC_ERROR})
target_link_libraries(morse2ascii PRIVATE ${LIBDC_POSIX})
target_link_libraries(morse2ascii PRIVATE ${LIBDC_UTIL})
target_link_libraries(morse2ascii PRIVATE ${LIBDC_FSM})
target_link_libraries(morse2ascii PRIVATE ${LIBDC_APPLICATION})
target_link_libraries(morse2ascii PRIVATE ${LIBCONFIG})

set_target_properties(ascii2morse PROPERTIES OUTPUT_NAME "ascii2morse")
set_target_properties(morse2ascii PROPERTIES OUTPUT_NAME "morse2ascii")

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)

add_custom_target(
        format
        COMMAND clang-format
        -i
        ${HEADER_LIST}
        ${SOURCE_LIST}
        ${MAIN_SOURCE}
)
