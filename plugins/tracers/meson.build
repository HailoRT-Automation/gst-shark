################################################
# BUFFER TRACE SOURCES 
################################################
gst_buffer_tracer_sources = [
    'gstbuffer.c'
]

shared_library('gsttracers',
    gst_buffer_tracer_sources,
    cpp_args : hailo_lib_args,
    include_directories: [hailo_general_inc, include_directories('./')],
    dependencies : post_deps,
    gnu_symbol_visibility : 'default',
    install: true,
    install_dir: get_option('libdir') + '/gstreamer-1.0/',
)
