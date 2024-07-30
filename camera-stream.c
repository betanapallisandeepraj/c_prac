#include <glib.h>
#include <gst/gst.h>

int main(int argc, char *argv[]) {
  GstElement *pipeline, *source, *sink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  GMainLoop *loop;

  /* Initialize GStreamer */
  gst_init(&argc, &argv);

  /* Create the pipeline */
  pipeline = gst_pipeline_new("camera-pipeline");
  source = gst_element_factory_make("v4l2src", "camera-source");
  sink = gst_element_factory_make("ximagesink", "display");

  /* Ensure all elements were created successfully */
  if (!pipeline || !source || !sink) {
    g_printerr("Not all elements could be created.\n");
    return -1;
  }

  /* Configure camera source */
  g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);

  /* Add elements to the pipeline */
  gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);

  /* Link the elements */
  if (gst_element_link(source, sink) != TRUE) {
    g_printerr("Elements could not be linked.\n");
    gst_object_unref(pipeline);
    return -1;
  }

  /* Set the pipeline to the playing state */
  ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr("Unable to set the pipeline to the playing state.\n");
    gst_object_unref(pipeline);
    return -1;
  }

  /* Create a GMainLoop to run the pipeline */
  loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(loop);

  /* Clean up */
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
  g_main_loop_unref(loop);

  return 0;
}
