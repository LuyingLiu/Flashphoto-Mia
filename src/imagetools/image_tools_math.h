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

#ifndef IMAGETOOLS_IMAGE_TOOLS_MATH_H_
#define IMAGETOOLS_IMAGE_TOOLS_MATH_H_

#include <algorithm>
#include <cmath>
#include "imagetools/color_data.h"

namespace image_tools {

/** A static class that holds several small math-related functions that are
 useful for manipulating images. */
class ImageToolsMath {
 public:
  /** @brief Linear interpolation between 2 two elements by a factor r. */
  template <typename T>
  static T Lerp(T a, T b, float r) {
    return a + (b - a) * r;
  }

  /** @brief Clamp the value of a type between [high,low] (inclusive). */
  template <typename T>
  static T Clamp(T x, T low, T high) {
    return std::min(std::max(x, low), high);
  }

  /** @brief Get the std deviation of a value in a gaussian distribution. */
  static float Gaussian(float x, float sigma) {
    return exp(
        -(pow(x, 2) / (2 * pow(sigma, 2)) + pow(0, 2) / (2 * pow(sigma, 2))));
  }
};

}  // namespace image_tools

#endif  // FLASHPHOTO_IMAGE_TOOLS_MATH_H_
