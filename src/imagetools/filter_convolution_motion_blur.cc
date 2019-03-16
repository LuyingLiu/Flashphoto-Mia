/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/
#include <cmath>
#include "imagetools/float_matrix.h"
#include "imagetools/filter_convolution_motion_blur.h"
#include "imagetools/color_data.h"

namespace image_tools {
ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur() {
  radius_ = 5.0;
  dir_ = MBLUR_DIR_N_S;
}

ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur(
  float radius, MBlurDir dir) {
  radius_ = radius;
  dir_ = dir;
}

ConvolutionFilterMotionBlur::~ConvolutionFilterMotionBlur() {}

float ConvolutionFilterMotionBlur::Radius() {
  return radius_;
}

MBlurDir ConvolutionFilterMotionBlur::Dir() {
  return dir_;
}
void ConvolutionFilterMotionBlur::SetRadius(float radius) {
  radius_ = radius;
}
void ConvolutionFilterMotionBlur::SetDir(MBlurDir dir) {
  dir_ = dir;
}

FloatMatrix* ConvolutionFilterMotionBlur::CreateKernel() {
  int radius = static_cast<int>(radius_);
  FloatMatrix* kernel = new FloatMatrix(radius);
  int size = 2 * radius_ + 1;

  if (dir_ == MBLUR_DIR_N_S) {
    for (int filterY = 0; filterY < size; filterY++) {
      for (int filterX = 0; filterX < size; filterX++) {
        if (filterX == radius) {
          kernel->set_value(filterX, filterY,
            (static_cast<float>(1.0)/static_cast<float>(size)));
        } else {
          kernel->set_value(filterX, filterY, 0);
        }
      }
    }
  }

  if (dir_ == MBLUR_DIR_E_W) {
    for (int filterY = 0; filterY < size; filterY++) {
      for (int filterX = 0; filterX < size; filterX++) {
        if (filterY == radius) {
          kernel->set_value(filterX, filterY,
            (static_cast<float>(1.0)/static_cast<float>(size)));
        } else {
          kernel->set_value(filterX, filterY, 0);
        }
      }
    }
  }

  if (dir_ == MBLUR_DIR_NE_SW) {
    for (int filterY = 0; filterY < size; filterY++) {
      for (int filterX = 0; filterX < size; filterX++) {
        if (filterX + filterY == (size - 1)) {
          kernel->set_value(filterX, filterY,
            (static_cast<float>(1.0)/static_cast<float>(size)));
        } else {
          kernel->set_value(filterX, filterY, 0);
        }
      }
    }
  }

  if (dir_ == MBLUR_DIR_NW_SE) {
    for (int filterY = 0; filterY < size; filterY++) {
      for (int filterX = 0; filterX < size; filterX++) {
        if (filterX == filterY) {
          kernel->set_value(filterX, filterY,
            (static_cast<float>(1.0)/static_cast<float>(size)));
        } else {
          kernel->set_value(filterX, filterY, 0);
        }
      }
    }
  }

  return kernel;
}

}  // namespace image_tools
