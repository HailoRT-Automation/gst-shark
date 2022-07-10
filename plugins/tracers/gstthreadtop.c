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
 * SECTION:gstcpuusage
 * @short_description: log cpu usage stats
 *
 * A tracing module that take cpuusage() snapshots and logs them.
 */

#include <glib/gstdio.h>
#include <unistd.h>
#include <string.h>

#include "gstthreadtop.h"
// #include "gstcpuusagecompute.h"
#include "gstctf.h"

GST_DEBUG_CATEGORY_STATIC (gst_thread_top_debug);
#define GST_CAT_DEFAULT gst_thread_top_debug


void gst_thread_top_init (GstThreadTop * cpu_usage)
{
  gint cpu_num = 0;

  g_return_if_fail (cpu_usage);

  memset (cpu_usage, 0, sizeof (GstThreadTop));
  cpu_usage->cpu_array_sel = FALSE;

  if ((cpu_num = sysconf (_SC_NPROCESSORS_CONF)) == -1) {
    GST_WARNING ("failed to get number of cpus");
    cpu_num = 1;
  }

  cpu_usage->cpu_num = cpu_num;
}

void
gst_cpu_usage_compute (GstThreadTop * cpu_usage)
{
  // gfloat *cpu_load;
  // gint cpu_num;
  // gint cpu_id;
  // FILE *fd;

  // gint *user;
  // gint *user_aux;
  // gint *nice;
  // gint *nice_aux;
  // gint *system;
  // gint *system_aux;
  // gint *idle;
  // gint *idle_aux;

  // gchar cpu_name[CPU_NAME_MAX_SIZE];
  // gint iowait;                  /* Time waiting for I/O to complete */
  // gint irq;                     /* Time servicing interrupts        */
  // gint softirq;                 /* Time servicing softirqs          */
  // gint steal;                   /* Time spent in other OSes when in virtualized env */
  // gint quest;                   /* Time spent running a virtual CPU for guest OS    */
  // gint quest_nice;              /* Time spent running niced guest */
  // gfloat num_value;
  // gfloat den_value;
  // gboolean cpu_array_sel;
  // gint ret;

  // g_return_if_fail (cpu_usage);

  // user = cpu_usage->user;
  // user_aux = cpu_usage->user_aux;
  // nice = cpu_usage->nice;
  // nice_aux = cpu_usage->nice_aux;
  // system = cpu_usage->system;
  // system_aux = cpu_usage->system_aux;
  // idle = cpu_usage->idle;
  // idle_aux = cpu_usage->idle_aux;

  // cpu_array_sel = cpu_usage->cpu_array_sel;
  // cpu_load = cpu_usage->cpu_load;
  // cpu_num = cpu_usage->cpu_num;

  // /* Compute the load for each core */
  // fd = g_fopen ("/proc/stat", "r");
  // if (cpu_array_sel == 0) {
  //   ret = fscanf (fd, "%" S (CPU_NAME_MAX_SIZE) "s %d %d %d %d %d %d %d %d %d %d",
  //       cpu_name, &user[0], &nice[0], &system[0], &idle[0], &iowait, &irq,
  //       &softirq, &steal, &quest, &quest_nice);
  //   for (cpu_id = 0; cpu_id < cpu_num; ++cpu_id) {
  //     ret =
  //         fscanf (fd,
  //         "%" S (CPU_NAME_MAX_SIZE) "s %d %d %d %d %d %d %d %d %d %d", cpu_name,
  //         &user[cpu_id], &nice[cpu_id], &system[cpu_id], &idle[cpu_id], &iowait,
  //         &irq, &softirq, &steal, &quest, &quest_nice);
  //   }
  //   /* Compute the utilization for each core */
  //   for (cpu_id = 0; cpu_id < cpu_num; ++cpu_id) {
  //     num_value =
  //         ((user[cpu_id] + nice[cpu_id] + system[cpu_id]) - (user_aux[cpu_id] +
  //             nice_aux[cpu_id] + system_aux[cpu_id]));
  //     den_value =
  //         ((user[cpu_id] + nice[cpu_id] + system[cpu_id] + idle[cpu_id]) -
  //         (user_aux[cpu_id] + nice_aux[cpu_id] + system_aux[cpu_id] +
  //             idle_aux[cpu_id]));
  //     cpu_load[cpu_id] = 100 * (num_value / den_value);
  //   }
  //   cpu_array_sel = 1;
  // } else {
  //   ret =
  //       fscanf (fd, "%" S (CPU_NAME_MAX_SIZE) "s %d %d %d %d %d %d %d %d %d %d",
  //       cpu_name, &user_aux[0], &nice_aux[0], &system_aux[0], &idle_aux[0],
  //       &iowait, &irq, &softirq, &steal, &quest, &quest_nice);
  //   for (cpu_id = 0; cpu_id < cpu_num; ++cpu_id) {
  //     ret =
  //         fscanf (fd,
  //         "%" S (CPU_NAME_MAX_SIZE) "s %d %d %d %d %d %d %d %d %d %d", cpu_name,
  //         &user_aux[cpu_id], &nice_aux[cpu_id], &system_aux[cpu_id],
  //         &idle_aux[cpu_id], &iowait, &irq, &softirq, &steal, &quest,
  //         &quest_nice);
  //   }
  //   /* Compute the utilization for each core */
  //   for (cpu_id = 0; cpu_id < cpu_num; ++cpu_id) {
  //     num_value =
  //         ((user_aux[cpu_id] + nice_aux[cpu_id] + system_aux[cpu_id]) -
  //         (user[cpu_id] + nice[cpu_id] + system[cpu_id]));
  //     den_value =
  //         ((user_aux[cpu_id] + nice_aux[cpu_id] + system_aux[cpu_id] +
  //             idle_aux[cpu_id]) - (user[cpu_id] + nice[cpu_id] +
  //             system[cpu_id] + idle[cpu_id]));
  //     cpu_load[cpu_id] = 100 * (num_value / den_value);
  //   }
  //   cpu_array_sel = 0;
  // }

  // (void) ret;

  // cpu_usage->cpu_array_sel = cpu_array_sel;
  // fclose (fd);
}



struct _GstThreadTopTracer
{
  GstPeriodicTracer parent;
  GstThreadTop cpu_usage;
};

#define _do_init \
    GST_DEBUG_CATEGORY_INIT (gst_thread_top_debug, "threadtop", 0, "thread resources usage tracer");

G_DEFINE_TYPE_WITH_CODE (GstThreadTopTracer, gst_thread_top_tracer,
    GST_TYPE_PERIODIC_TRACER, _do_init);

static GstTracerRecord *tr_threadtop;

static const gchar threadtop_metadata_event_header[] = "\
event {\n\
    name = threadtop;\n\
    id = %d;\n\
    stream_id = %d;\n\
    fields := struct {\n";

static const gchar threadtop_metadata_event_footer[] = "\
    };\n\
};\n\
\n";

static const gchar floating_point_event_field[] =
    "        floating_point { exp_dig = %lu; mant_dig = %d; byte_order = le; align = 8; } _cpu%d;\n";

static void cpuusage_dummy_bin_add_post (GObject * obj, GstClockTime ts,
    GstBin * bin, GstElement * element, gboolean result);
static gboolean thread_top_thread_func (GstPeriodicTracer * tracer);
static void create_metadata_event (GstPeriodicTracer * tracer);
static void reset_counters (GstPeriodicTracer * tracer);

static void
cpuusage_dummy_bin_add_post (GObject * obj, GstClockTime ts,
    GstBin * bin, GstElement * element, gboolean result)
{
  return;
}

static void
reset_counters (GstPeriodicTracer * tracer)
{
  GstThreadTopTracer *self;

  self = GST_THREAD_TOP_TRACER (tracer);

  gst_thread_top_init (&(self->cpu_usage));
}

static gboolean
thread_top_thread_func (GstPeriodicTracer * tracer)
{
  GstThreadTopTracer *self;
  GstThreadTop *cpu_usage;
  gfloat *cpu_load;
  gint cpu_id;
  gint cpu_load_len;

  self = GST_THREAD_TOP_TRACER (tracer);

  cpu_usage = &self->cpu_usage;

  cpu_load = CPU_USAGE_ARRAY (cpu_usage);
  cpu_load_len = CPU_USAGE_ARRAY_LENGTH (cpu_usage);

  gst_cpu_usage_compute (cpu_usage);

  for (cpu_id = 0; cpu_id < cpu_load_len; ++cpu_id) {
    gst_tracer_record_log (tr_threadtop, cpu_id, cpu_load[cpu_id]);
  }
  do_print_cpuusage_event (THREADTOP_EVENT_ID, cpu_load_len, cpu_load);

  return TRUE;
}

static void
create_metadata_event (GstPeriodicTracer * tracer)
{
  GstThreadTopTracer *self;
  gint cpu_num;
  gchar *mem;
  gchar *mem_start;
  gchar *event_header;
  gsize str_size;
  gsize mem_size;
  gint msg_id;
  gint number_of_bytes;

  self = GST_THREAD_TOP_TRACER (tracer);
  // cpu_num = self->cpu_usage.cpu_num;

  event_header =
      g_strdup_printf (threadtop_metadata_event_footer, THREADTOP_EVENT_ID, 0);

  str_size = strlen (event_header);

  /* Compute event description size
   * size = header + fields + footer
   */
  mem_size =
      str_size + cpu_num * sizeof (floating_point_event_field) +
      sizeof (threadtop_metadata_event_footer);
  mem_start = g_malloc (mem_size);
  mem = mem_start;

  /* Add event header */
  mem += g_strlcpy (mem, event_header, mem_size);
  mem_size -= str_size;

  /* Add event fields */
  for (msg_id = 0; msg_id < cpu_num; ++msg_id) {
    /* floating point field definition:
     * http://diamon.org/ctf/#spec4.1.7
     */
    number_of_bytes = g_snprintf (mem,
        mem_size,
        floating_point_event_field,
        (unsigned long) (sizeof (gfloat) * CHAR_BIT - FLT_MANT_DIG),
        FLT_MANT_DIG, msg_id);

    mem += number_of_bytes;
    mem_size -= number_of_bytes;
  }

  /* Add event footer */
  g_strlcpy (mem, threadtop_metadata_event_footer, mem_size);

  /* Add event in metadata file */
  add_metadata_event_struct (mem_start);
  /* Free allocated memory */
  g_free (mem_start);
  g_free (event_header);
}

static void
gst_thread_top_tracer_class_init (GstThreadTopTracerClass * klass)
{
  GstPeriodicTracerClass *tracer_class;

  tracer_class = GST_PERIODIC_TRACER_CLASS (klass);

  tracer_class->timer_callback = GST_DEBUG_FUNCPTR (thread_top_thread_func);
  tracer_class->reset = GST_DEBUG_FUNCPTR (reset_counters);
  tracer_class->write_header = GST_DEBUG_FUNCPTR (create_metadata_event);

  tr_threadtop = gst_tracer_record_new ("threadtop.class",
      "number", GST_TYPE_STRUCTURE, gst_structure_new ("value",
          "type", G_TYPE_GTYPE, G_TYPE_UINT,
          "description", G_TYPE_STRING, "Core number",
          "flags", GST_TYPE_TRACER_VALUE_FLAGS,
          GST_TRACER_VALUE_FLAGS_AGGREGATED, "min", G_TYPE_UINT, 0, "max",
          G_TYPE_UINT, CPU_NUM_MAX, NULL), "load", GST_TYPE_STRUCTURE,
      gst_structure_new ("value", "type", G_TYPE_GTYPE, G_TYPE_DOUBLE,
          "description", G_TYPE_STRING, "Core load percentage [%]", "flags",
          GST_TYPE_TRACER_VALUE_FLAGS, GST_TRACER_VALUE_FLAGS_AGGREGATED, "min",
          G_TYPE_DOUBLE, 0.0f, "max", G_TYPE_DOUBLE, 100.0f, NULL), NULL);
}

static void
gst_thread_top_tracer_init (GstCPUUsageTracer * self)
{
  GstThreadTop *cpu_usage;

  cpu_usage = &self->cpu_usage;
  gst_cpu_usage_init (cpu_usage);
  cpu_usage->cpu_array_sel = FALSE;

  /* Register a dummy hook so that the tracer remains alive */
  gst_tracing_register_hook (GST_TRACER (self), "bin-add-post",
      G_CALLBACK (cpuusage_dummy_bin_add_post));
}