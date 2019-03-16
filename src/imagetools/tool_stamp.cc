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

#include "imagetools/tool_stamp.h"

#include "imagetools/mask_factory.h"

namespace image_tools {

ToolStamp::ToolStamp() {
  // the Stamp is circular so the overlap might be able to be a bit smaller
  // than 0.9, but it looks best with a high overlap like 0.9.
  stamp_overlap_ = 0.9;
}

ToolStamp::~ToolStamp() {}

FloatMatrix* ToolStamp::CreateMask(float radius) {
  return MaskFactory::CreateBullseyeMask(radius, 0.2 * radius);
}

void ToolStamp::AddToStroke(int x, int y) {
  (void)x;
  (void)y;
}

}  // namespace image_tools
