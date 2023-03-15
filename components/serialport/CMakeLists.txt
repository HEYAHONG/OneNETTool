include(${COMPONENT_CMAKE_PATH})


#serialport库
file(GLOB SERIALPORT_CXX_C_FILES *.cpp *.h *.hpp *.c)
add_library(serialport ${SERIALPORT_CXX_C_FILES})
target_include_directories(serialport
PUBLIC ./
)

if(WIN32)
target_link_libraries(serialport ws2_32)
endif()

if(CYGWIN)
target_link_libraries(serialport ws2_32)
endif()

find_package(Boost 1.70.0 REQUIRED COMPONENTS thread system date_time regex serialization)
target_link_libraries(serialport Boost::boost Boost::thread Boost::system Boost::date_time Boost::regex Boost::serialization)


#添加到组件库
components_add_library(serialport)
