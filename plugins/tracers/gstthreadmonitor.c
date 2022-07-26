/* GstShark - A Front End for GstTracer
 * Copyright (C) 2018 RidgeRun Engineering <manuel.leiva@ridgerun.com>
 *
 * This file is part of GstShark.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
/**
 * SECTION:gstthreadmonitor
 * @short_description: log cpu usage stats
 *
 * A tracing module that take threadmonitor() snapshots and logs them.
 */

#include <glib/gstdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "gstthreadmonitor.h"
#include "gstthreadmonitorcompute.h"
#include "gstctf.h"

GST_DEBUG_CATEGORY_STATIC(gst_thread_monitor_debug);
#define GST_CAT_DEFAULT gst_thread_monitor_debug

struct _GstThreadMonitorTracer
{
  GstPeriodicTracer parent;
  GstThreadMonitor thread_monitor;
  uint pid;
};

#define _do_init \
  GST_DEBUG_CATEGORY_INIT(gst_thread_monitor_debug, "threadmonitor", 0, "threadmonitor tracer");

G_DEFINE_TYPE_WITH_CODE(GstThreadMonitorTracer, gst_thread_monitor_tracer,
                        GST_TYPE_PERIODIC_TRACER, _do_init);

static GstTracerRecord *tr_threadmonitor;

static const gchar threadmonitor_metadata_event_header[] = "\
event {\n\
    name = threadmonitor;\n\
    id = %d;\n\
    stream_id = %d;\n\
    fields := struct {\n";

static const gchar threadmonitor_metadata_event_footer[] = "\
    };\n\
};\n\
\n";

static const gchar floating_point_event_field[] =
    "        floating_point { exp_dig = %lu; mant_dig = %d; byte_order = le; align = 8; } _cpu%d;\n";

static void threadmonitor_dummy_bin_add_post(GObject *obj, GstClockTime ts,
                                             GstBin *bin, GstElement *element, gboolean result);
static gboolean thread_monitor_thread_func(GstPeriodicTracer *tracer);
static void create_metadata_event(GstPeriodicTracer *tracer);
// static void reset_counters (GstPeriodicTracer * tracer);

static void
threadmonitor_dummy_bin_add_post(GObject *obj, GstClockTime ts,
                                 GstBin *bin, GstElement *element, gboolean result)
{
  return;
}

// static void
// reset_counters (GstPeriodicTracer * tracer)
// {
//   GstThreadMonitorTracer *self;

//   self = GST_THREAD_MONITOR_TRACER (tracer);

//   gst_thread_monitor_init (&(self->thread_monitor));
// }

static gboolean
thread_monitor_thread_func(GstPeriodicTracer *tracer)
{
  GstThreadMonitorTracer *self;
  GstThreadMonitor *thread_monitor;

  gchar *thread_name = NULL;
  // gchar *thread_cpu_usage=NULL;
  // gchar *thread_memory_usage=NULL;

  gchar *thread_cpu_usage = NULL;
  gchar *thread_memory_usage = NULL;

  self = GST_THREAD_MONITOR_TRACER(tracer);
  thread_monitor = &self->thread_monitor;
  gst_thread_monitor_compute(tr_threadmonitor,thread_monitor, &thread_name, &thread_cpu_usage, &thread_memory_usage);

  do_print_threadmonitor_event(THREADMONITOR_EVENT_ID);

  return TRUE;
}

static void
create_metadata_event(GstPeriodicTracer *tracer)
{
  // GstThreadMonitorTracer *self;
  gint cpu_num;
  gchar *mem;
  gchar *mem_start;
  gchar *event_header;
  gsize str_size;
  gsize mem_size;
  gint msg_id;
  gint number_of_bytes;

  // self = GST_THREAD_MONITOR_TRACER (tracer);
  // cpu_num = self->cpu_usage.cpu_num;
  cpu_num = 12;
  event_header =
      g_strdup_printf(threadmonitor_metadata_event_header, THREADMONITOR_EVENT_ID, 0);

  str_size = strlen(event_header);

  /* Compute event description size
   * size = header + fields + footer
   */
  mem_size =
      str_size + cpu_num * sizeof(floating_point_event_field) +
      sizeof(threadmonitor_metadata_event_footer);
  mem_start = g_malloc(mem_size);
  mem = mem_start;

  /* Add event header */
  mem += g_strlcpy(mem, event_header, mem_size);
  mem_size -= str_size;

  /* Add event fields */
  for (msg_id = 0; msg_id < cpu_num; ++msg_id)
  {
    /* floating point field definition:
     * http://diamon.org/ctf/#spec4.1.7
     */
    number_of_bytes = g_snprintf(mem,
                                 mem_size,
                                 floating_point_event_field,
                                 (unsigned long)(sizeof(gfloat) * CHAR_BIT - FLT_MANT_DIG),
                                 FLT_MANT_DIG, msg_id);

    mem += number_of_bytes;
    mem_size -= number_of_bytes;
  }

  /* Add event footer */
  g_strlcpy(mem, threadmonitor_metadata_event_footer, mem_size);

  /* Add event in metadata file */
  add_metadata_event_struct(mem_start);
  /* Free allocated memory */
  g_free(mem_start);
  g_free(event_header);
}

static void
gst_thread_monitor_tracer_class_init(GstThreadMonitorTracerClass *klass)
{
  GstPeriodicTracerClass *tracer_class;

  tracer_class = GST_PERIODIC_TRACER_CLASS(klass);

  tracer_class->timer_callback = GST_DEBUG_FUNCPTR(thread_monitor_thread_func);
  // tracer_class->reset = GST_DEBUG_FUNCPTR (reset_counters);
  tracer_class->write_header = GST_DEBUG_FUNCPTR(create_metadata_event);

  tr_threadmonitor = gst_tracer_record_new("threadmonitor.class",
                                           "name", GST_TYPE_STRUCTURE,
                                           gst_structure_new("value", "type", G_TYPE_GTYPE, G_TYPE_STRING,
                                                             "description", G_TYPE_STRING,
                                                             "thread name", "flags", GST_TYPE_TRACER_VALUE_FLAGS,
                                                             GST_TRACER_VALUE_FLAGS_AGGREGATED, NULL),
                                           "cpu_usage",
                                           GST_TYPE_STRUCTURE,
                                           gst_structure_new("value", "type", G_TYPE_GTYPE, G_TYPE_DOUBLE,
                                                             "description", G_TYPE_STRING, "CPU usage of thread percentage [%]", "flags",
                                                             GST_TYPE_TRACER_VALUE_FLAGS, GST_TRACER_VALUE_FLAGS_AGGREGATED, "min",
                                                             G_TYPE_DOUBLE, 0.0f, "max", G_TYPE_DOUBLE, 100.0f, NULL),

                                           "memory_usage",
                                           GST_TYPE_STRUCTURE,
                                           gst_structure_new("value", "type", G_TYPE_GTYPE, G_TYPE_DOUBLE,
                                                             "description", G_TYPE_STRING, "Memory usage of thread percentage [%]", "flags",
                                                             GST_TYPE_TRACER_VALUE_FLAGS, GST_TRACER_VALUE_FLAGS_AGGREGATED, "min",
                                                             G_TYPE_DOUBLE, 0.0f, "max", G_TYPE_DOUBLE, 100.0f, NULL),
                                           NULL);
}

static void
gst_thread_monitor_tracer_init(GstThreadMonitorTracer *self)
{

  GstThreadMonitor *thread_monitor;
  thread_monitor = &self->thread_monitor;
  self->pid = getpid();
  gst_thread_monitor_init(thread_monitor);
  // cpu_usage->cpu_array_sel = FALSE;

  /* Register a dummy hook so that the tracer remains alive */
  gst_tracing_register_hook(GST_TRACER(self), "bin-add-post",
                            G_CALLBACK(threadmonitor_dummy_bin_add_post));
}
