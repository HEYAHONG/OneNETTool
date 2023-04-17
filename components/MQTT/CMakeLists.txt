include(${COMPONENT_CMAKE_PATH})


include(FindPkgConfig)
#libmosquitto库（MQTT客户端）
pkg_check_modules(LIBMOSQUITTOPP REQUIRED IMPORTED_TARGET libmosquittopp)
pkg_check_modules(LIBMOSQUITTO REQUIRED IMPORTED_TARGET libmosquitto)

#添加到组件库
components_add_library(PkgConfig::LIBMOSQUITTOPP)
components_add_library(PkgConfig::LIBMOSQUITTO)
