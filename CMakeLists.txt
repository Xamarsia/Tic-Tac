find_package( Threads )
add_executable(main clock.cpp main.cpp)
target_link_libraries( main ${CMAKE_THREAD_LIBS_INIT} )