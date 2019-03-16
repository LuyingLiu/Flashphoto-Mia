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

#include "imagetools/tool_spray_can.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolSprayCan::ToolSprayCan() {
  // overlap should be pretty high since the mask is so transparent
  stamp_overlap_ = 0.75;
}

ToolSprayCan::~ToolSprayCan() {}

FloatMatrix* ToolSprayCan::CreateMask(float radius) {
  FloatMatrix* mask = MaskFactory::CreateLinearFalloffMask(radius);
  mask->Scale(0.1);
  return mask;
}

}  // namespace image_tools
