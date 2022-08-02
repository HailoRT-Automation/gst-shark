/* GstShark - A Front End for GstTracer
 * Copyright (C) 2016-2018 RidgeRun Engineering <carlos.rodriguez@ridgerun.com>
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
 * SECTION:gstnumerator
 * @short_description: log current idendity
 *
 */

#include "gstnumerator.h"
#include "gstctf.h"

GST_DEBUG_CATEGORY_STATIC(gst_numerator_debug);
#define GST_CAT_DEFAULT gst_numerator_debug

struct _GstNumeratorTracer
{
    GstSharkTracer parent;
};

#define _do_init \
    GST_DEBUG_CATEGORY_INIT(gst_numerator_debug, "numerator", 0, "numerator tracer");

G_DEFINE_TYPE_WITH_CODE(GstNumeratorTracer, gst_numerator_tracer,
                        GST_SHARK_TYPE_TRACER, _do_init);

static void gst_numerator_buffer_pre(GObject *self, GstClockTime ts,
                                     GstPad *pad, GstBuffer *buffer);
static void
gst_numerator_buffer_pre(GObject *self, GstClockTime ts, GstPad *pad,
                         GstBuffer *buffer)
{
    buffer->offset = 0;
}


/* tracer class */
static void
gst_numerator_tracer_class_init(GstNumeratorTracerClass *klass)
{}

static void
gst_numerator_tracer_init(GstNumeratorTracer *self)
{
    GstSharkTracer *tracer = GST_SHARK_TRACER(self);

    gst_shark_tracer_register_hook(tracer, "pad-push-pre",
                                   G_CALLBACK(gst_numerator_buffer_pre));
}
