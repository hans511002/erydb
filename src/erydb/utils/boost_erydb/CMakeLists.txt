include_directories(${ENGINE_COMMON_INCLUDES})

set(boost_erydb_LIB_SRCS
    codecvt_error_category.cpp
    cpp_regex_traits.cpp
    cregex.cpp
    c_regex_traits.cpp
    error_code.cpp
    fileiter.cpp
    future.cpp
    greg_month.cpp
    icu.cpp
    instances.cpp
    once.cpp
    operations.cpp
    path.cpp
    path_traits.cpp
    portability.cpp
    posix_api.cpp
    regex.cpp
    regex_debug.cpp
    regex_raw_buffer.cpp
    regex_traits_defaults.cpp
    static_mutex.cpp
    thread.cpp
    tss_null.cpp
    unique_path.cpp
    usinstances.cpp
    utf8_codecvt_facet.cpp
    w32_regex_traits.cpp
    wc_regex_traits.cpp
    wide_posix_api.cpp
    windows_file_codecvt.cpp
    winstances.cpp)

add_library(boost_erydb SHARED ${boost_erydb_LIB_SRCS})

set_target_properties(boost_erydb PROPERTIES VERSION 1.0.0 SOVERSION 1)

install(TARGETS boost_erydb DESTINATION ${ENGINE_LIBDIR})

