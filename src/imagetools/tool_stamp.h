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

#ifndef IMAGETOOLS_TOOL_STAMP_H_
#define IMAGETOOLS_TOOL_STAMP_H_

#include <string>
#include "imagetools/tool.h"

namespace image_tools {

/** @brief Stamps a single X marks the spot. */
class ToolStamp : public Tool {
 public:
  ToolStamp();
  virtual ~ToolStamp();

  static const std::string name() { return "Stamp"; }

  /** The stamp tool overrides AddToStroke to make it do nothing.  This way,
   each time the stamp tool is used it produces just a single mark on the
   canvas at the first location where it is applied. */
  void AddToStroke(int x, int y) override;

  FloatMatrix* CreateMask(float radius) override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_STAMP_H_
