/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/
#include <cmath>
#include "imagetools/image_tools_math.h"
#include "imagetools/filter_convolution_blur.h"
#include "imagetools/color_data.h"

namespace image_tools {

ConvolutionFilterBlur::ConvolutionFilterBlur() {
  radius_ = 5.0;
}

ConvolutionFilterBlur::ConvolutionFilterBlur(float radius) {
  radius_ = radius;
}

ConvolutionFilterBlur::~ConvolutionFilterBlur() {}

float ConvolutionFilterBlur::Radius() {
  return radius_;
}
void ConvolutionFilterBlur::SetRadius(float radius) {
  radius_ = radius;
}

FloatMatrix* ConvolutionFilterBlur::CreateKernel() {
  FloatMatrix *kernel = new FloatMatrix(round(radius_));
  for (int filterY = 0; filterY < (2 * radius_ + 1); filterY++) {
    for (int filterX = 0; filterX < (2 * radius_ + 1); filterX++) {
      float distance = static_cast<double>(sqrt(static_cast<double>
        (pow((radius_ - filterX) , 2) + pow((radius_ - filterY) , 2))));
      float v = ImageToolsMath::Gaussian(distance, radius_);
      kernel->set_value(filterX, filterY, v);
    }
  }
  kernel->Normalize();
  return kernel;
}

}  // namespace image_tools
