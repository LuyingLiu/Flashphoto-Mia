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

#include "imagetools/tool_eraser.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolEraser::ToolEraser() { stamp_overlap_ = 0.9; }

ToolEraser::~ToolEraser() {}

FloatMatrix *ToolEraser::CreateMask(float radius) {
  return MaskFactory::CreateConstantMask(radius);
}

void ToolEraser::StartStroke(PixelBuffer *buffer, int x, int y,
                             const ColorData &paint_color, float radius) {
  (void)paint_color;
  // The eraser is a special case -- the buffer's background color is used as
  // the paint color for the tool.
  Tool::StartStroke(buffer, x, y, buffer->background_color(), radius);
}

} /* namespace image_tools */
