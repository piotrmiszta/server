set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*/*.h")

file(GLOB src "${CMAKE_SOURCE_DIR}/src/*/*.c")


add_library(serverlib STATIC ${src} ${HEADER_LIST})


target_include_directories(serverlib PUBLIC ${INCLUDE_DIR}/server/
											${INCLUDE_DIR}/util
											${INCLUDE_DIR}/client
											${INCLUDE_DIR}/messages
											)
