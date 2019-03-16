/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/
#include <cmath>
#include "imagetools/filter_convolution_blur.h"
#include "imagetools/filter_convolution_sharpen.h"
#include "imagetools/color_data.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

ConvolutionFilterSharpen::ConvolutionFilterSharpen() {
  radius_ = 5.0;
}

ConvolutionFilterSharpen::ConvolutionFilterSharpen(float radius) {
  radius_ = radius;
}

ConvolutionFilterSharpen::~ConvolutionFilterSharpen() {}

void ConvolutionFilterSharpen::SetRadius(float radius) {
  radius_ = radius;
}

float ConvolutionFilterSharpen::Radius() {
  return radius_;
}

FloatMatrix* ConvolutionFilterSharpen::CreateKernel() {
  FloatMatrix* kernel =
    new FloatMatrix(round(radius_ * 2.0) + 1, round(radius_ * 2.0) + 1);

  for (int j = 0; j < kernel->height(); j++) {
    for (int i = 0; i < kernel->width(); i++) {
      int x = i - kernel->width() / 2;
      int y = j - kernel->height() / 2;
      float dist = sqrt(x * x + y * y);
      float intensity = ImageToolsMath::Gaussian(dist, radius_);
      kernel->set_value(i, j, intensity);
    }
  }
  kernel->Normalize();

  // Negate all the values
  kernel->Scale(-1.0);

  // Add two to the middle
  float middle_value = kernel->value(kernel->width() / 2, kernel->height() / 2);
  kernel->set_value(kernel->width() / 2, kernel->height() / 2,
                    middle_value + 2.0);

  return kernel;
}

}  // namespace image_tools
