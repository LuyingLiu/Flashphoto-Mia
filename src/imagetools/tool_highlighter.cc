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

#include "imagetools/tool_highlighter.h"
#include "imagetools/mask_factory.h"

namespace image_tools {

ToolHighlighter::ToolHighlighter() {
  // since the mask shape is narrow, the overlap needs to be fairly large
  // in order to get a nice continuous stroke.
  stamp_overlap_ = 0.9;
}

ToolHighlighter::~ToolHighlighter() {}

FloatMatrix *ToolHighlighter::CreateMask(float radius) {
  FloatMatrix *mask = MaskFactory::CreateOvalMask(radius, 90.0, 0.333);
  // scaling the mask here makes it transparent
  mask->Scale(0.15);
  return mask;
}

ColorData ToolHighlighter::CombinePaintAndCanvasColor(
    const ColorData &paint_color, const ColorData &canvas_color,
    float mask_intensity) {
  mask_intensity *= canvas_color.Luminance();
  return Tool::CombinePaintAndCanvasColor(paint_color, canvas_color,
                                          mask_intensity);
}

} /* namespace image_tools */
