/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define this to enable Graphviz capabilities */
#define ENABLE_GRAPHVIZ 1

/* Define this to enable the tracer for reading of the CPU usage */
#define GST_CPUUSAGE_ENABLE 1

/* GstShark API Version */
#define GST_SHARK_API_VERSION "0.0"

/* GstShark license */
#define GST_SHARK_LICENSE "LGPL"

/* Name of package */
#define PACKAGE "gst-shark"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GstShark"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://github.com/RidgeRun/gst-shark"

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
