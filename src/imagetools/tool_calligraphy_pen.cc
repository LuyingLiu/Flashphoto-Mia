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

#include "imagetools/tool_calligraphy_pen.h"
#include "imagetools/mask_factory.h"

namespace image_tools {

ToolCalligraphyPen::ToolCalligraphyPen() {
  // since the mask shape is narrow, the overlap needs to be fairly large
  // in order to get a nice continuous stroke.
  stamp_overlap_ = 0.9;
}

ToolCalligraphyPen::~ToolCalligraphyPen() {}

FloatMatrix* ToolCalligraphyPen::CreateMask(float radius) {
  return MaskFactory::CreateOvalMask(radius, 70.0, 0.333);
}

}  // namespace image_tools
