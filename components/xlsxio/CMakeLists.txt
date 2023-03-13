include(${COMPONENT_CMAKE_PATH})

add_subdirectory(xlsxio EXCLUDE_FROM_ALL)

target_include_directories(${COMPENENT_MAIN_TARGET}
PUBLIC xlsxio/include/
)
target_compile_definitions(${COMPENENT_MAIN_TARGET}
PUBLIC -DDLL_EXPORT_XLSXIO=
)
target_compile_definitions(xlsxio_read_STATIC
PUBLIC -DDLL_EXPORT_XLSXIO=
)
target_compile_definitions(xlsxio_write_STATIC
PUBLIC -DDLL_EXPORT_XLSXIO=
)
include_directories(
xlsxio/include/
)


#添加到组件库
components_add_library(xlsxio_read_STATIC)
components_add_library(xlsxio_write_STATIC)
