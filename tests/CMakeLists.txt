include_directories(
  gtest/
  gtest/include
  )

if (LINUX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

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
  set_tests_properties(
    ${name}
    PROPERTIES LABELS "test"
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

# Tests

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

add_cods_test(
  Deque
  Deque.cpp
  )

add_cods_test(
  PriorityQueue
  PriorityQueue.cpp
  )

add_cods_test(
  RingBuffer
  RingBuffer.cpp
  )

add_cods_test(
  Bitset
  Bitset.cpp
  )

# Performance tests

macro(add_cods_perf name)
  add_executable(
    ${name}
    ${ARGV}
    )
  add_test(
    NAME ${name}
    COMMAND ${name}
    )
  set_tests_properties(
    ${name}
    PROPERTIES LABELS "perf"
    )
  target_link_libraries(
    ${name}
    gtest
    )
  include_directories(
    gtest/include
    ..
    )
endmacro(add_cods_perf)

add_cods_perf(
  PerfVector
  PerfVector.cpp
  )

add_cods_perf(
  PerfHashMap
  PerfHashMap.cpp
  )
