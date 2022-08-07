################################################
# BUFFER TRACE SOURCES 
################################################
gst_buffer_tracer_sources = [

	'gstdot.c',
	'gstcpuusagecompute.c',
	'gstthreadmonitorcompute.c',
	'gstproctimecompute.c',
	'gstctf.c',
	'gstparser.c',
	'gstplugin.c',
	'gstsharktracer.c',
	'gstgraphic.c',
	'gstcpuusage.c',
	'gstthreadmonitor.c',
	'gstproctime.c',
	'gstinterlatency.c',
	'gstscheduletime.c',
	'gstframerate.c',
	'gstqueuelevel.c',
	'gstbitrate.c',
	'gstbuffer.c',
	'gstperiodictracer.c',
]

glib_dep = dependency('glib-2.0')
gio_dep = dependency('gio-2.0')

shared_library('gstsharktracers',
    gst_buffer_tracer_sources,
    cpp_args : hailo_lib_args,
    include_directories: [hailo_general_inc, include_directories('./')],
    dependencies : plugin_deps+[glib_dep, gio_dep],
    gnu_symbol_visibility : 'default',
    install: true,
	c_args : '-DGST_USE_UNSTABLE_API',
    install_dir: get_option('libdir') + '/gstreamer-1.0/',
)
