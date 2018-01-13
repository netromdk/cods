# Require C++14 standard.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_COMPILER_WARNINGS "-Wno-unused-parameter -Wempty-body -Woverloaded-virtual -Wtautological-compare")
set(CLANG_WARNINGS "-Wnull-arithmetic -Woverriding-method-mismatch")
set(GCC_WARNINGS "-Wuseless-cast")

# Warnings turned into errors.
set(COMMON_COMPILER_ERRORS "-Werror=return-type -Werror=delete-incomplete -Werror=delete-non-virtual-dtor -Werror=float-equal -Werror=reorder -Werror=uninitialized -Werror=unreachable-code")
set(CLANG_ERRORS "-Werror=inconsistent-missing-override -Werror=unused-private-field -Werror=division-by-zero -Werror=return-stack-address")
set(GCC_ERRORS "")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic-errors ${COMMON_COMPILER_WARNINGS} ${COMMON_COMPILER_ERRORS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Some release optimization flags for GCC/Clang.
if (NOT WIN32)
  # Clang/GCC
  set(REL_OPTS "-pipe -fno-exceptions -fvisibility=hidden -fvisibility-inlines-hidden -ffast-math -funroll-loops")

  # GCC only
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(REL_OPTS "${REL_OPTS} -fno-implement-inlines")

  # Clang only
  elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(REL_OPTS "${REL_OPTS} -Ofast")
  endif()

  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${REL_OPTS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${REL_OPTS}")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${REL_OPTS}")
endif()

message("Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
    OUTPUT_VARIABLE GCC_VERSION
    )
  if (NOT (GCC_VERSION VERSION_GREATER 5.0 OR GCC_VERSION VERSION_EQUAL 5.0))
    message(FATAL_ERROR "Requires GCC >= 5.0.")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
    OUTPUT_VARIABLE CLANG_VERSION
    )
  if (NOT (CLANG_VERSION VERSION_GREATER 3.8 OR CLANG_VERSION VERSION_EQUAL 3.8))
    message(FATAL_ERROR "Requires Clang >= 3.8.")
  elseif(APPLE)
    # Use libstdc++ on Linux but libc++ on macOS.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
elseif (MSVC AND MSVC14)
  # C++14 support is implicitly enabled.
else()
  message(FATAL_ERROR "Your compiler does not support C++14 - aborting!")
endif()
