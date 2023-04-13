include(${COMPONENT_CMAKE_PATH})


#OneNET库
file(GLOB ONENET_CXX_C_FILES *.cpp *.h *.hpp *.c cJSON/cJSON.c cJSON/cJSON_Utils.c)
add_library(OneNET ${ONENET_CXX_C_FILES})
target_include_directories(OneNET
PUBLIC ./ cJSON/
)
set_property(TARGET OneNET PROPERTY C_STANDARD 11)
set_property(TARGET OneNET PROPERTY CXX_STANDARD 20)

#鉴于大多数嵌入式中加密库均是由mbedtls实现,因此采用mbedtls作为加密库
include(CheckIncludeFile)
set(HAVE_MBEDTLS TRUE)

check_include_file("mbedtls/base64.h" HAVE_MBEDTLS_BASE64)
if(NOT HAVE_MBEDTLS_BASE64)
set(HAVE_MBEDTLS FALSE)
endif()

check_include_file("mbedtls/md.h" HAVE_MBEDTLS_MD)
if(NOT HAVE_MBEDTLS_MD)
set(HAVE_MBEDTLS FALSE)
endif()

if(HAVE_MBEDTLS)
target_link_libraries(OneNET mbedcrypto)
else()
message(FATAL_ERROR "mbedtls is not found!")
endif()

#检查config.h与onenet_config.h
set(CMAKE_REQUIRED_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/")
check_include_file("config.h" HAVE_CONFIG_H)
if(HAVE_CONFIG_H)
target_compile_definitions(OneNET
PUBLIC -DHAVE_CONFIG_H)
endif()

set(CMAKE_REQUIRED_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/")
check_include_file("onenet_config.h" HAVE_ONENET_CONFIG_H)
if(HAVE_ONENET_CONFIG_H)
target_compile_definitions(OneNET
PUBLIC -DHAVE_ONENET_CONFIG_H)
endif()

#添加到组件库
components_add_library(OneNET)
