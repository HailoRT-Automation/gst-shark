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
 * SECTION:gstdetections
 * @short_description: log current idendity
 *
 * A tracing module that prints detections info at every sink pad
 */

#include "gstdetections.hpp"
#include "gstctf.hpp"
#include "../../../core/hailo/gstreamer/metadata/gst_hailo_meta.hpp"
#include "../../../core/hailo/general/hailo_common.hpp"

GST_DEBUG_CATEGORY_STATIC(gst_detections_debug);
#define GST_CAT_DEFAULT gst_detections_debug

struct _GstDetectionsTracer
{
    GstSharkTracer parent;
};

#define _do_init \
    GST_DEBUG_CATEGORY_INIT(gst_detections_debug, "detections", 0, "detections tracer");

G_DEFINE_TYPE_WITH_CODE(GstDetectionsTracer, gst_detections_tracer,
                        GST_SHARK_TYPE_TRACER, _do_init);

static void gst_detections_buffer_pre(GObject *self, GstClockTime ts,
                                      GstPad *pad, GstBuffer *buffer);

static GstTracerRecord *tr_detections;

/*
static const gchar buffer_metadata_event[] = "event {\n\
    name = detections;\n\
    id = %d;\n\
    stream_id = %d;\n\
    fields := struct {\n\
        string pad;\n\
        integer { size = 64; align = 8; signed = 0; encoding = none; base = 10; } pts;\n\
        integer { size = 64; align = 8; signed = 0; encoding = none; base = 10; } dts;\n\
        integer { size = 64; align = 8; signed = 0; encoding = none; base = 10; } duration;\n\
        integer { size = 64; align = 8; signed = 0; encoding = none; base = 10; } offset;\n\
        integer { size = 64; align = 8; signed = 0; encoding = none; base = 10; } offset_end;\n\
        integer { size = 64; align = 8; signed = 0; encoding = none; base = 10; } size;\n\
        integer { size = 32; align = 8; signed = 0; encoding = none; base = 10; } flags;\n\
        integer { size = 32; align = 8; signed = 0; encoding = none; base = 10; } refcount;\n\
    };\n\
};\n\
\n";
*/

static void
gst_detections_buffer_pre(GObject *self, GstClockTime ts, GstPad *pad,
                          GstBuffer *buffer)
{
    HailoROIPtr hailo_roi;
    if (NULL == buffer)
    {
        return;
    }
    hailo_roi = get_hailo_main_roi(buffer, false);
    if (NULL == hailo_roi)
    {
        return;
    }

    for (auto obj : hailo_roi->get_objects())
    {
        if (obj->get_type() == HAILO_DETECTION)
        {
            HailoDetectionPtr detection = std::dynamic_pointer_cast<HailoDetection>(obj);
            auto detection_bbox = detection->get_bbox();
            gst_tracer_record_log(tr_detections, detection->get_label().c_str(),
                                  detection_bbox.xmin(),
                                  detection_bbox.ymin());
        }
    }
}

/* tracer class */
static void
gst_detections_tracer_class_init(GstDetectionsTracerClass *klass)
{
    //   gchar *metadata_event;

    tr_detections = gst_tracer_record_new("detections.class",
                                          "label",
                                          GST_TYPE_STRUCTURE, gst_structure_new("value", "type", G_TYPE_GTYPE, G_TYPE_STRING, "description", G_TYPE_STRING, "The detection's label", NULL),
                                          "xmin",
                                          GST_TYPE_STRUCTURE, gst_structure_new("value", "type", G_TYPE_GTYPE, G_TYPE_FLOAT, "description", G_TYPE_STRING, "the minimum x value of the bounding box", NULL),
                                          "ymin",
                                          GST_TYPE_STRUCTURE, gst_structure_new("value", "type", G_TYPE_GTYPE, G_TYPE_FLOAT, "description", G_TYPE_STRING, "the minimum y value of the bounding box", NULL),
                                          NULL);

    //   metadata_event = g_strdup_printf (detections_metadata_event, BUFFER_EVENT_ID, 0);
    //   add_metadata_event_struct (metadata_event);
    //   g_free (metadata_event);
}

static void
gst_detections_tracer_init(GstDetectionsTracer *self)
{
    GstSharkTracer *tracer = GST_SHARK_TRACER(self);

    gst_shark_tracer_register_hook(tracer, "pad-push-pre",
                                   G_CALLBACK(gst_detections_buffer_pre));
}
