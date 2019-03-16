/*
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Daniel Keefe, 2018, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  ...
*/

#ifndef IMAGETOOLS_IMAGE_EDITOR_H_
#define IMAGETOOLS_IMAGE_EDITOR_H_

#include <deque>
#include <string>

#include "imagetools/pixel_buffer.h"

// filters
#include "imagetools/filter_convolution_blur.h"
#include "imagetools/filter_convolution_edge.h"
#include "imagetools/filter_convolution_motion_blur.h"
#include "imagetools/filter_convolution_sharpen.h"
#include "imagetools/filter_channels.h"
#include "imagetools/filter_quantize.h"
#include "imagetools/filter_saturate.h"
#include "imagetools/filter_threshold.h"

// tools
#include "imagetools/tool_blur.h"
#include "imagetools/tool_calligraphy_pen.h"
#include "imagetools/tool_chalk.h"
#include "imagetools/tool_eraser.h"
#include "imagetools/tool_highlighter.h"
#include "imagetools/tool_pen.h"
#include "imagetools/tool_spray_can.h"
#include "imagetools/tool_stamp.h"


namespace image_tools {

/** This is the major class of the FlashPhoto application.  In the
 model-view-controller paradigm, we can think of this class as implementing
 the model for an ImageEditor that could be controlled by various controllers
 (e.g., interactive mouse and keyboard, command line) and viewed different
 ways (e.g., interactively with a GUI, with files written to disk). */
class ImageEditor {
 public:
   /** Creates an editor with a NULL pixel buffer.  You will need to set the
    pixel buffer before performing any editing operations. */
   ImageEditor();

  /** The ImageEditor requires a current pixel buffer, so this is the preferred
   constructor. */
  explicit ImageEditor(PixelBuffer *buffer);

  /** Deletes the current pixel buffer if not null. */
  virtual ~ImageEditor();

  // FILE SAVING AND LOADING

  /** Loads a pixel buffer from a PNG formatted file. */
  void LoadFromFile(const std::string &filename);

  /** Saves the current pixel buffer to a PNG file. */
  void SaveToFile(const std::string &filename);

  // TOOLS

  Tool *GetToolByName(const std::string &name);

  /** Call this from the controller to being a new stroke at pixel (x,y) using
   the tool named tool_name and the specified color and radius.  Since it
   takes multiple frames to complete a stroke the tool_name, color, and radius
   are saved as state variables and are used for subsequent calls to
   AddToStroke() and EndStroke(). */
  void StartStroke(const std::string &tool_name, const ColorData &color,
                   float radius, int x, int y);

  /** Call this from the controller to add to a stroke that was recently
   started with a call to StartStroke(). */
  void AddToStroke(int x, int y);

  /** Call this from the controller to end a stroke started with
   StartStroke(). */
  void EndStroke(int x, int y);

  // FILTERS

  /** Call this from the controller to apply the blur filter to the current
   pixel buffer using the current blur filter state. */
  void ApplyBlurFilter(float radius);

  /** Call this from the controller to apply the filter to the current
   pixel buffer using the current motion blur filter state. */
  void ApplyMotionBlurFilter(float radius, MBlurDir dir);

  /** Call this from the controller to apply the sharpen filter to the current
   pixel buffer using the current sharpen filter state. */
  void ApplySharpenFilter(float radius);

  /** Call this from the controller to apply the edge detect filter to the
   current
   pixel buffer using the current edge detect filter state. */
  void ApplyEdgeDetectFilter();

  /** Call this from the controller to apply the threshold filter to the current
   pixel buffer using the current threshold filter state. */
  void ApplyThresholdFilter(float cutoff_value);

  /** Call this from the controller to apply the saturate filter to the current
   pixel buffer using the current saturate filter state. */
  void ApplySaturateFilter(float scale_factor);

  /** Call this from the controller to apply the channels filter to the current
   pixel buffer using the current channels filter state. */
  void ApplyChannelsFilter(float red_scale, float green_scale,
                           float blue_scale);

  /** Call this from the controller to apply the quantize filter to the current
   pixel buffer using the current quantize filter state. */
  void ApplyQuantizeFilter(int num_bins);

  /** Undo the last operation applied to the pixel buffer. */
  void Undo();

  /** Redo the last undone operation. */
  void Redo();

  /** True if the the log of applied commands is not empty, i.e., it is
   possible to perform an undo operation. */
  bool can_undo();

  /** True if the log of undone commands is not empty, i.e., it is possible to
   perform a redo operation. */
  bool can_redo();

  PixelBuffer *pixel_buffer();

  void set_pixel_buffer(PixelBuffer *buffer);

  void SaveStateForPossibleUndo();

 private:
  ConvolutionFilterBlur f_blur_;
  ConvolutionFilterEdge f_edge_;
  ConvolutionFilterMotionBlur f_motion_blur_;
  ConvolutionFilterSharpen f_sharpen_;
  FilterChannels f_channels_;
  FilterQuantize f_quantize_;
  FilterSaturate f_saturate_;
  FilterThreshold f_threshold_;

  ToolBlur t_blur_;
  ToolCalligraphyPen t_calligraphy_pen_;
  ToolChalk t_chalk_;
  ToolEraser t_eraser_;
  ToolHighlighter t_highlighter_;
  ToolPen t_pen_;
  ToolSprayCan t_spray_can_;
  ToolStamp t_stamp_;

  // state data saved during calls to StartStroke, AddToStroke, EndStroke
  Tool *current_tool_;
  ColorData tool_color_;
  float tool_radius_;

  PixelBuffer *current_buffer_;

  unsigned int max_undos_;
  std::deque<PixelBuffer *> saved_states_;   // undo
  std::deque<PixelBuffer *> undone_states_;  // redo
};

}  // namespace image_tools

#endif  // IMAGETOOLS_IMAGE_EDITOR_H_
