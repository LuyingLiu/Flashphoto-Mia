/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/
#include <cmath>
#include "imagetools/filter_convolution_edge.h"
#include "imagetools/color_data.h"

namespace image_tools {

ConvolutionFilterEdge::ConvolutionFilterEdge() {}

ConvolutionFilterEdge::~ConvolutionFilterEdge() {}

FloatMatrix* ConvolutionFilterEdge::CreateKernel() {
  FloatMatrix *kernel = new FloatMatrix(1);
  for (int filterY = 0; filterY < 3; filterY++) {
    for (int filterX = 0; filterX < 3; filterX++) {
      if (filterX == 1 && filterY == 1) {
        kernel->set_value(filterX, filterY, 8);
      } else {
        kernel->set_value(filterX, filterY, -1);
      }
    }
  }
  return kernel;
}

}  // namespace image_tools
