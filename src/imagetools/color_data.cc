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

#include "imagetools/color_data.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

ColorData::ColorData() : red_(1), green_(1), blue_(1), alpha_(1) {}
ColorData::ColorData(float r, float g, float b)
    : red_(r), green_(g), blue_(b), alpha_(1) {}
ColorData::ColorData(float r, float g, float b, float a)
    : red_(r), green_(g), blue_(b), alpha_(a) {}

float ColorData::Luminance() const {
  return static_cast<float>(0.2126) * red_ +
         static_cast<float>(0.7152) * green_ +
         static_cast<float>(0.0722) * blue_;
}

void ColorData::Clamp() {
  red_ = ImageToolsMath::Clamp(this->red(), 0.f, 1.f);
  green_ = ImageToolsMath::Clamp(this->green(), 0.f, 1.f);
  blue_ = ImageToolsMath::Clamp(this->blue(), 0.f, 1.f);
  alpha_ = ImageToolsMath::Clamp(this->alpha(), 0.f, 1.f);
}

// Apply component-wise arithmatic operations
ColorData operator*(const ColorData& a, float f) {
  return ColorData(a.red_ * f, a.green_ * f, a.blue_ * f, a.alpha_ * f);
}

ColorData operator+(const ColorData& a, const ColorData& b) {
  return ColorData(a.red_ + b.red_, a.green_ + b.green_, a.blue_ + b.blue_,
                   a.alpha_ + b.alpha_);
}

ColorData operator-(const ColorData& a, const ColorData& b) {
  return ColorData(a.red_ - b.red_, a.green_ - b.green_, a.blue_ - b.blue_,
                   a.alpha_ - b.alpha_);
}

bool operator==(const ColorData& a, const ColorData& b) {
  // a thresold used to account for numerical imprecision in floating point
  // comparisons
  // EPSILON = 1.0/256.0 to account for 8 bit values (unsigned char) that are saved to files
  static const float EPSILON = 0.004;

  return (fabs(a.red_ - b.red_) < EPSILON &&
          fabs(a.green_ - b.green_) < EPSILON &&
          fabs(a.blue_ - b.blue_) < EPSILON &&
          fabs(a.alpha_ - b.alpha_) < EPSILON);
}

bool operator!=(const ColorData& a, const ColorData& b) {
  return !(a == b);
}

} /* namespace image_tools */
