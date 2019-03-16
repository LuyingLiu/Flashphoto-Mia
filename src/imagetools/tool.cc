/*
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Seth Johnson, 2/15/15, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  ...
*/

#include "imagetools/tool.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

Tool::Tool() : paint_color_(0.0, 0.0, 0.0, 1.0), mask_(NULL), buffer_(NULL),
 stamp_overlap_(0.5) {
}

Tool::~Tool() {}

void Tool::StartStroke(PixelBuffer *buffer, int x, int y,
                       const ColorData &paint_color, float radius) {
  mask_ = CreateMask(radius);
  paint_color_ = paint_color;
  buffer_ = buffer;
  StampMaskOntoBuffer(x, y);
  last_x_ = x;
  last_y_ = y;
}

void Tool::AddToStroke(int x, int y) {
  // determine change in x and y position since the last stamp
  int delta_x = x - last_x_;
  int delta_y = y - last_y_;

  // based on this tool's stamp_overlap_ parameter, determine the number of
  // times we should stamp the mask in order to properly cover the distance
  // between (last_x, last_y) and (x, y)
  float length = sqrtf(delta_x * delta_x + delta_y * delta_y);
  float ideal_step_size = mask_->height() * (1.0 - stamp_overlap_);
  int nstamps = ceil(length / ideal_step_size);

  if (nstamps == 0) {
    // here, we know that the tool hasn't moved since the last call to
    // this function.  if the tool should apply more paint evan without
    // being moved (like a spray can) then we should apply a stamp again.
    // otherwise, do nothing since we would have already applied a stamp
    // at the current (x,y) the last time through this function.
    if (applies_paint_when_stationary()) {
      StampMaskOntoBuffer(x, y);
      last_x_ = x;
      last_y_ = y;
    }
  } else {
    // find the step size in both x and y based on the number of stamps to apply
    float step_x = static_cast<float>(delta_x) / static_cast<float>(nstamps);
    float step_y = static_cast<float>(delta_y) / static_cast<float>(nstamps);

    // apply the stamp multiple times between (last_x, last_y) and (x,y)
    for (int i = 0; i < nstamps; i++) {
      int x_stamp = last_x_ + round(static_cast<float>(i + 1) * step_x);
      int y_stamp = last_y_ + round(static_cast<float>(i + 1) * step_y);
      StampMaskOntoBuffer(x_stamp, y_stamp);
    }
    last_x_ = x;
    last_y_ = y;
  }
}

void Tool::EndStroke(int x, int y) {
  (void)x;
  (void)y;
  buffer_ = NULL;
  delete mask_;
  mask_ = NULL;
}

void Tool::StampMaskOntoBuffer(int tool_x, int tool_y) {
  int mask_width_2 = mask_->width() / 2;
  int mask_height_2 = mask_->height() / 2;

  int image_left = std::max(tool_x - mask_width_2, 0);
  int image_right = std::min(tool_x + mask_width_2, buffer_->width() - 1);
  int image_top = std::max(tool_y - mask_height_2, 0);
  int image_bottom = std::min(tool_y + mask_height_2, buffer_->height() - 1);

#pragma omp for
  for (int image_y = image_top; image_y < image_bottom; image_y++) {
    for (int image_x = image_left; image_x < image_right; image_x++) {
      ColorData canvas_color = buffer_->pixel(image_x, image_y);

      int mask_x = image_x - (tool_x - mask_width_2);
      int mask_y = image_y - (tool_y - mask_height_2);
      float intensity = mask_->value(mask_x, mask_y);

      ColorData paint_color = LookupPaintColor(image_x, image_y);

      ColorData final_color =
          CombinePaintAndCanvasColor(paint_color, canvas_color, intensity);

      buffer_->set_pixel(image_x, image_y, final_color);
    }
  }
}

ColorData Tool::LookupPaintColor(int x, int y) {
  (void)x;
  (void)y;
  return paint_color_;
}

ColorData Tool::CombinePaintAndCanvasColor(const ColorData &paint_color,
                                           const ColorData &canvas_color,
                                           float mask_intensity) {
  return paint_color * mask_intensity + canvas_color * (1.0 - mask_intensity);
}

bool Tool::applies_paint_when_stationary() { return false; }

} /* namespace image_tools */
