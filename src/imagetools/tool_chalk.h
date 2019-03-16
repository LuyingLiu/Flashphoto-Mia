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

#ifndef IMAGETOOLS_TOOL_CHALK_H_
#define IMAGETOOLS_TOOL_CHALK_H_

#include <string>
#include "imagetools/tool.h"

namespace image_tools {

/** @brief This tool simulates chalk drawing on a rough paper.  The class
 overrides Tool's default color blending function to insert random noise as
 the tool is moved around. */
class ToolChalk : public Tool {
 public:
  ToolChalk();

  virtual ~ToolChalk();

  static const std::string name() { return "Chalk"; }

  void SetSeed(){ seed_ = 100; }

  FloatMatrix *CreateMask(float radius) override;

  ColorData CombinePaintAndCanvasColor(const ColorData &paint_color,
                                       const ColorData &canvas_color,
                                       float mask_intensity) override;

 private:
  static unsigned int seed_;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_CHALK_H_
