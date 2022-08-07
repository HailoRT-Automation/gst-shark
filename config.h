/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define this to enable Graphviz capabilities */
#define ENABLE_GRAPHVIZ 1

/* The GIO library directory. */
#define GIO_LIBDIR "/usr/lib/x86_64-linux-gnu"

/* The GIO modules directory. */
#define GIO_MODULE_DIR "/usr/lib/x86_64-linux-gnu/gio/modules"

/* The GIO install prefix. */
#define GIO_PREFIX "/usr"

/* Define this to enable the tracer for reading of the CPU usage */
#define GST_CPUUSAGE_ENABLE 1

/* Define if extra runtime checks should be enabled */
#define GST_ENABLE_EXTRA_CHECKS 1

/* Extra platform specific plugin suffix */
/* #undef GST_EXTRA_MODULE_SUFFIX */

/* Defined if gcov is enabled to force a rebuild due to config.h changing */
/* #undef GST_GCOV_ENABLED */

/* Defined when registry scanning through fork is unsafe */
/* #undef GST_HAVE_UNSAFE_FORK */

/* Default errorlevel to use */
#define GST_LEVEL_DEFAULT GST_LEVEL_ERROR

/* GstShark API Version */
#define GST_SHARK_API_VERSION "0.0"

/* data dir */
#define GST_SHARK_DATADIR "/usr/share"

/* GstShark license */
#define GST_SHARK_LICENSE "LGPL"

/* GstShark date of creation */
#define GST_SHARK_PACKAGE_CREATED "2016-01-29"

/* GstShark mailing list address */
#define GST_SHARK_PACKAGE_MAILINGLIST ""

/* Define if static plugins should be built */
/* #undef GST_SHARK_PLUGIN_BUILD_STATIC */

/* GstShark long description */
#define GST_SHARK_README_LONG "GstShark leverages GStreamers newest instrumentation subsystem by installing a set of custom hooks to the trace points. A variety of data analytics are extracted and presented to the user in a graphical, friendly way.  "

/* GstShark short description */
#define GST_SHARK_README_SHORT "A Front End for GstShark "

/* GstShark read-only git repo */
#define GST_SHARK_REPO_BROWSE "https://github.com/RidgeRun/gst-shark"

/* GstShark download address */
#define GST_SHARK_REPO_DOWNLOAD ""

/* GstShark git repo */
#define GST_SHARK_REPO_LOCATION "git@github.com:RidgeRun/gst-shark.git"

/* GstShark Version Major */
#define GST_SHARK_VERSION_MAJOR 0

/* GstShark Version Micro */
#define GST_SHARK_VERSION_MICRO 2

/* GstShark Version Minor */
#define GST_SHARK_VERSION_MINOR 7

/* GstShark Version Nano */
#define GST_SHARK_VERSION_NANO 1

/* Define this to use the tracers API of GStreamer version >= $GST_REQ_STABLE
   */
#define GST_STABLE_RELEASE 1

/* Define if the target CPU is AARCH64 */
/* #undef HAVE_CPU_AARCH64 */

/* Define if the target CPU is an Alpha */
/* #undef HAVE_CPU_ALPHA */

/* Define if the target CPU is an ARC */
/* #undef HAVE_CPU_ARC */

/* Define if the target CPU is an ARM */
/* #undef HAVE_CPU_ARM */

/* Define if the target CPU is a CRIS */
/* #undef HAVE_CPU_CRIS */

/* Define if the target CPU is a CRISv32 */
/* #undef HAVE_CPU_CRISV32 */

/* Define if the target CPU is a HPPA */
/* #undef HAVE_CPU_HPPA */

/* Define if the target CPU is an x86 */
/* #undef HAVE_CPU_I386 */

/* Define if the target CPU is a IA64 */
/* #undef HAVE_CPU_IA64 */

/* Define if the target CPU is a M68K */
/* #undef HAVE_CPU_M68K */

/* Define if the target CPU is a MIPS */
/* #undef HAVE_CPU_MIPS */

/* Define if the target CPU is a PowerPC */
/* #undef HAVE_CPU_PPC */

/* Define if the target CPU is a 64 bit PowerPC */
/* #undef HAVE_CPU_PPC64 */

/* Define if the target CPU is a S390 */
/* #undef HAVE_CPU_S390 */

/* Define if the target CPU is a SPARC */
/* #undef HAVE_CPU_SPARC */

/* Define if the target CPU is a x86_64 */
/* #undef HAVE_CPU_X86_64 */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Defined if compiling for OSX */
/* #undef HAVE_OSX */

/* Define if RDTSC is available */
/* #undef HAVE_RDTSC */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if valgrind should be used */
#define HAVE_VALGRIND 1

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
#define HAVE_VALGRIND_VALGRIND_H 1

/* Defined if compiling for Windows */
/* #undef HAVE_WIN32 */

/* the host CPU */
#define HOST_CPU "x86_64"

/* library dir */
#define LIBDIR "/usr/lib/x86_64-linux-gnu"

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "gst-shark"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://github.com/RidgeRun/gst-shark"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GstShark"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GstShark 0.7.2.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gst-shark"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://github.com/RidgeRun/gst-shark"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.7.2.1"

/* directory where plugins are located */
#define PLUGINDIR "/usr/lib/x86_64-linux-gnu/gstreamer-1.0"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* the target CPU */
#define TARGET_CPU ""

/* Version number of package */
#define VERSION "0.7.2.1"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* We need at least WinXP SP2 for __stat64 */
/* #undef __MSVCRT_VERSION__ */
