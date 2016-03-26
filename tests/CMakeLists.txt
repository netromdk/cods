include_directories(
  gtest/
  gtest/include
  )

add_library(
  gtest
  gtest/src/gtest-all.cc
  )

macro(add_cods_test name)
  add_executable(
    ${name}
    ${ARGV}
    )
  add_test(
    NAME ${name}
    COMMAND ${name}
    )
  target_link_libraries(
    ${name}
    gtest
    )
  include_directories(
    gtest/include
    ..
    )
endmacro(add_cods_test)

add_cods_test(
  Vector
  Vector.cpp
  )

add_cods_test(
  HashMap
  HashMap.cpp
  )

add_cods_test(
  Set
  Set.cpp
  )

add_cods_test(
  Queue
  Queue.cpp
  )

add_cods_test(
  Stack
  Stack.cpp
  )
