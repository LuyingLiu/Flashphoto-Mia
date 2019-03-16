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

#include "imagetools/float_matrix.h"
#include <stdio.h>
#include <iomanip>
#include <iostream>

namespace image_tools {

FloatMatrix::FloatMatrix() : height_(1), width_(1), float_array_(1, 1.0) {}

FloatMatrix::FloatMatrix(int radius)
    : height_(2 * radius + 1),
      width_(2 * radius + 1),
      float_array_((2 * radius + 1) * (2 * radius + 1), 1.0) {}

FloatMatrix::FloatMatrix(int w, int h)
    : height_(h), width_(w), float_array_(w * h, 1.0) {}

FloatMatrix::~FloatMatrix() {}

float FloatMatrix::value(int x, int y) const {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return 0.f;
  } else {
    return float_array_[y * width_ + x];
  }
}

void FloatMatrix::set_value(int x, int y, float v) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return;
  } else {
    float_array_[y * width_ + x] = v;
  }
}

float FloatMatrix::Sum() {
  float s = 0;
  for (int i = 0; i < width(); i++) {
    for (int j = 0; j < height(); j++) {
      s += value(i, j);
    }
  }
  return s;
}

std::ostream& operator<<(std::ostream& s, const FloatMatrix& mat) {
  for (int j = 0; j < mat.height(); j++) {
    for (int i = 0; i < mat.width(); i++) {
      s << std::setprecision(3) << mat.value(i, j);
    }
    s << std::endl;
  }
  return s;
}

void FloatMatrix::Normalize() {
  float s = Sum();
  if (!(s > 0)) {
    return;
  }
  float v;

  for (int i = 0; i < width(); i++) {
    for (int j = 0; j < height(); j++) {
      v = value(i, j);
      set_value(i, j, v / s);
    }
  }
}

void FloatMatrix::Scale(const float c) {
  for (int i = height() * width() - 1; i >= 0; i--) {
    float_array_[i] *= c;
  }
}

} /* namespace image_tools */
