# Project Declaration

project('gst-shark-tracers', 'c', 'cpp',
        version : '3.20.0',
        default_options : [ 'warning_level=1',
                            'buildtype=debugoptimized',
                            'c_std=c11', 'cpp_std=c++17']
       )

# Compiler Arguments
compiler = meson.get_compiler('cpp')
compiler_version = compiler.version().split('.')[0].to_int()
if compiler_version >= 9
  message('GCC >= 9.0.0 detected, applying extra arguments.')
  add_global_arguments('-Wpessimizing-move', language : 'cpp')
  add_global_arguments('-Wredundant-move', language : 'cpp')
  add_global_arguments('-fconcepts', language : 'cpp')
endif

# Include Directories
hailo_general_inc = [include_directories(get_option('libgeneral_path'))]

# Xtensor Include Directories
xtensor_base_inc = include_directories(get_option('libxtensor'), is_system: true)
xtensor_inc = [xtensor_base_inc]
if get_option('include_blas')
  xtensor_blas_inc = include_directories(get_option('libblas'), is_system: true)
  xtensor_inc += [xtensor_blas_inc]
endif

# Extra Compiler Arguments
xtensor_args = []  # '-mavx2', '-ffast-math' --> TODO: Causes arm issues
debug_args = ['-g', '-O0']

# Gstreamer Dependencies
gst_req = '>= 1.0.0'
gst_dep = dependency('gstreamer-1.0', version : gst_req,
  fallback : ['gstreamer', 'gst_dep'])
gst_base_dep = dependency('gstreamer-base-1.0', version : gst_req,
  fallback : ['gstreamer', 'gst_base_dep'])
gst_app_dep = dependency('gstreamer-app-1.0', version : gst_req,
  fallback : ['gstreamer', 'gst_app_dep'])
gstvideo_dep = dependency('gstreamer-video-1.0', version : gst_req,
  fallback : ['gst-plugins-base', 'video_dep'])

meta_dep = dependency('gsthailometa', version : meson.project_version(), method : 'pkg-config')


# Opencv Dependencies
opencv_dep = dependency('opencv4', version : '>= 4.0', method : 'pkg-config')


# Plugin Dependencies
plugin_deps = [gst_dep, gst_base_dep, gstvideo_dep, gst_app_dep]
post_deps = []


# Library Arguments
hailo_lib_args = get_option('libargs')

tappas_workspace =  meson.current_source_dir() + '/../../../'


# Project Subdirectories
subdir('tracers')

