/* GstShark - A Front End for GstTracer
 * Copyright (C) 2016 RidgeRun Engineering <manuel.leiva@ridgerun.com>
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <glib/gstdio.h>
#include "gstthreadmonitor.h"
#include "gstthreadmonitorcompute.h"

#include <unistd.h>
#include <string.h>

// #define CPU_NAME_MAX_SIZE 8
// #define S(arg) XS(arg)
// #define XS(arg) #arg

void gst_thread_monitor_init(GstThreadMonitor *thread_monitor)
{
  g_return_if_fail(thread_monitor);
  memset(thread_monitor, 0, sizeof(GstThreadMonitor));
}

void gst_thread_monitor_compute(GstTracerRecord *tr_threadmonitor, GstThreadMonitor *thread_monitor, gchar **thread_name, gchar **thread_cpu_usage,
                                gchar **thread_memory_usage)
{
  FILE *fp;
  gchar *command;
  gchar *colums_command;
  char **tokens;
  gchar *token;
  gint thread_name_loc;
  gint thread_cpu_usage_loc;
  gint thread_memory_usage_loc;

  char path[4096];
  char *path_stripped;
  char columns[4096];
  gint num_columns = 0;
  g_return_if_fail(thread_monitor);

  colums_command = g_strdup_printf("top -H -p %d -n 1 | grep PID | tr -s ' ' | sed -e 's/\x1b\[[0-9;]*m//g'", getpid());

  fp = popen(colums_command, "r");

  if (fp == NULL)
  {
    GST_WARNING("Failed to run command");
    return;
  }
  while (fgets(path, PATH_MAX, fp) != NULL)
  {
    // printf("path: %s\n", path);
    path_stripped = g_strstrip(path);
    // printf("stripped:%s\n", path_stripped);
    strcpy(columns, path_stripped);
    // get number of words in path
    token = strtok(path_stripped, " ");
    while (token != NULL)
    {
      num_columns++;
      token = strtok(NULL, " ");
    }
  }
  // print num columns
  //  printf("num_columns: %d\n", num_columns);
  tokens = g_strsplit(columns, " ", num_columns);

  thread_name_loc = -1;
  thread_cpu_usage_loc = -1;
  thread_memory_usage_loc = -1;
  for (int i = 0; i < num_columns; i++)
  {
    if (strcmp(tokens[i], "COMMAND") == 0)
    {
      thread_name_loc = i;
    }
    else if (strcmp(tokens[i], "%CPU") == 0)
    {
      thread_cpu_usage_loc = i;
    }
    else if (strcmp(tokens[i], "%MEM") == 0)
    {
      thread_memory_usage_loc = i;
    }
  }

  pclose(fp);
  g_free(colums_command);

  command = g_strdup_printf("top -H -p %d -n 1 | sed -n '/PID/,/^$/p' | tail -n +2 | tr -s ' ' | grep src | sed -e 's/\x1b\[[0-9;]*m//g'", getpid());

  fp = popen(command, "r");
  if (fp == NULL)
  {
    GST_WARNING("Failed to run command");
    return;
  }
  while (fgets(path, PATH_MAX, fp) != NULL)
  {
    path_stripped = g_strstrip(path);
    printf("path stripped: %s",path_stripped);
    tokens = g_strsplit(path_stripped, " ", num_columns);
    *thread_name = tokens[thread_name_loc];
    *thread_cpu_usage = tokens[thread_cpu_usage_loc];
    *thread_memory_usage = tokens[thread_memory_usage_loc];

    // printf("THREAD NAME: %s\n", *thread_name);

    // gst_tracer_record_log(tr_threadmonitor, *thread_name, atof(*thread_cpu_usage), atof(*thread_memory_usage));
    *thread_name = NULL;
    *thread_cpu_usage = NULL;
    *thread_memory_usage = NULL;
  }
  pclose(fp);
  g_free(command);
}
