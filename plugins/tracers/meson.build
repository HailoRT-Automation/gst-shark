################################################
# BUFFER TRACE SOURCES 
################################################
gst_buffer_tracer_sources = [
    'gstbuffer.c'

	gstdot.c \
	gstcpuusagecompute.c \
	gstthreadmonitorcompute.c \
	gstproctimecompute.c \
	gstctf.c \
	gstparser.c
	gstplugin.c \
	gstsharktracer.c \
	gstgraphic.c \
	gstcpuusage.c \
	gstthreadmonitor.c \
	gstproctime.c \
	gstinterlatency.c \
	gstscheduletime.c \
	gstframerate.c \
	gstqueuelevel.c \
	gstbitrate.c \
	gstbuffer.c \
	gstperiodictracer.c


]

shared_library('gsttracers',
    gst_buffer_tracer_sources,
    cpp_args : hailo_lib_args,
    include_directories: [hailo_general_inc, include_directories('./')],
    dependencies : plugin_deps,
    gnu_symbol_visibility : 'default',
    install: true,
    install_dir: get_option('libdir') + '/gstreamer-1.0/',
)
