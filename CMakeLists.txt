cmake_minimum_required (VERSION 3.0)
project (Pamela C)

add_library (Pamela SHARED pamela.c)

target_link_libraries(
  Pamela
  pam
  )
