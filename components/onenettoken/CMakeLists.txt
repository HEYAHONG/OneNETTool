include(${COMPONENT_CMAKE_PATH})

#onenettoken库
file(GLOB ONENETTOKEN_CXX_C_FILES *.cpp *.h *.hpp *.c)
add_library(onenettoken ${ONENETTOKEN_CXX_C_FILES})
target_include_directories(onenettoken
PUBLIC ./
)
set_property(TARGET onenettoken PROPERTY C_STANDARD 11)
set_property(TARGET onenettoken PROPERTY CXX_STANDARD 20)

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
target_link_libraries(onenettoken mbedcrypto)
else()
message(FATAL_ERROR "mbedtls is not found!")
endif()


#添加到组件库
components_add_library(onenettoken)
