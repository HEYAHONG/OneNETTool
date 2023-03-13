include(${COMPONENT_CMAKE_PATH})

add_subdirectory(xlsxio EXCLUDE_FROM_ALL)

target_include_directories(${COMPENENT_MAIN_TARGET}
PUBLIC xlsxio/include/
)
include_directories(
xlsxio/include/
)


#添加到组件库
components_add_library(xlsxio_read_STATIC)
components_add_library(xlsxio_write_STATIC)
