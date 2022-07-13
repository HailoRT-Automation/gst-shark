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
  char **tokens;

  // gint thread_name_loc;
  // gint thread_cpu_usage_loc;
  // gint thread_memory_usage_loc;
  int counter;
  size_t len = 0;
  char *line = NULL;
  ssize_t read;
  // int k;

  // char columns[4096];
  // gint num_columns = 0;

  // char *columns = NULL;
  // gchar *token;
  // gchar *colums_command;

  g_return_if_fail(thread_monitor);

  // colums_command = g_strdup_printf("top -H -p %d -n 1 | grep PID | tr -s ' ' | sed -e 's/\x1b\[[0-9;]*m//g'", getpid());

  // fp = popen(colums_command, "r");

  // if (fp == NULL)
  // {
  //   GST_WARNING("Failed to run command");
  //   return;
  // }
  // if (getline(&line, &len, fp) != -1)
  // {
  //   stripped_line = g_strstrip(line);
  //   columns = (char *)malloc(strlen(stripped_line) + 1);
  //   strcpy(columns, stripped_line);
  //   token = strtok(stripped_line, " ");
  //   while (token != NULL)
  //   {
  //     num_columns++;
  //     token = strtok(NULL, " ");
  //   }
  // }
  // tokens = g_strsplit(columns, " ", num_columns);

  // thread_name_loc = -1;
  // thread_cpu_usage_loc = -1;
  // thread_memory_usage_loc = -1;
  // for (int i = 0; i < num_columns; i++)
  // {
  //   if (strcmp(tokens[i], "COMMAND") == 0)
  //   {
  //     thread_name_loc = i;
  //   }
  //   else if (strcmp(tokens[i], "%CPU") == 0)
  //   {
  //     thread_cpu_usage_loc = i;
  //   }
  //   else if (strcmp(tokens[i], "%MEM") == 0)
  //   {
  //     thread_memory_usage_loc = i;
  //   }
  // }
  // free(columns);
  // pclose(fp);
  // g_free(colums_command);
  // print all loc
  // printf("thread_name_loc: %d\n", thread_name_loc);
  // printf("thread_cpu_usage_loc: %d\n", thread_cpu_usage_loc);
  // printf("thread_memory_usage_loc: %d\n", thread_memory_usage_loc);

  // thread_name_loc = 11;
  // thread_cpu_usage_loc = 8;
  // thread_memory_usage_loc = 9;

  // command = g_strdup_printf("top -H -p %d -n 1 | sed -n '/PID/,/^$/p' | tail -n +2 | tr -s ' ' | grep src | sed -e 's/\x1b\[[0-9;]*m//g'", getpid());
  command = g_strdup_printf("top -H -b -p %d -n 1 | sed -n '/PID/,/^$/p' | tail -n +2 | tr -s ' ' | grep src | sed -e 's/\x1b\[[0-9;]*m//g' | awk '{print $12,$9,$10}'", getpid());
  // command = g_strdup_printf("cat /local/workspace/tappas/top_output_3");
  fp = popen(command, "r");
  if (fp == NULL)
  {
    GST_WARNING("Failed to run command");
    printf("Failed to run command\n");
    return;
  }
  counter = 0;

  // printf("PID: %d\n", getpid());
  while ((read = getline(&line, &len, fp)) != -1)
  {
    // line[0]=' ';
    line = line + 3;
    printf("***PID %d\n",getpid());
    printf("***PRINTING ASCI\n");


    counter++;
    tokens = g_strsplit(line, " ", 3);
    *thread_name = tokens[0];
    *thread_cpu_usage = tokens[1];
    *thread_memory_usage = tokens[2];

    gst_tracer_record_log(tr_threadmonitor, *thread_name, atof(*thread_cpu_usage), atof(*thread_memory_usage));
    *thread_name = NULL;
    *thread_cpu_usage = NULL;
    *thread_memory_usage = NULL;
    line = NULL;
    len = 0;
  }

  // printf("Retrieved line of length %zu:\n", read);
  // print counter
  printf("COUNTER:%d\n", counter);
  pclose(fp);
  g_free(command);
}
