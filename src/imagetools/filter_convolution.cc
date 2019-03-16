/*
This code is a part of student coursework.  It is not an open source
project.

Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#include <assert.h>
#include <algorithm>
#include <cmath>
#include "imagetools/image_tools_math.h"
#include "imagetools/filter.h"
#include "imagetools/filter_convolution.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

ConvolutionFilter::ConvolutionFilter(): kernel_(NULL) {}

ConvolutionFilter::~ConvolutionFilter() {
  if (kernel_ != NULL) {
    delete kernel_;
  }
}

void ConvolutionFilter::SetupFilter() {
  kernel_ = CreateKernel();
}

ColorData ConvolutionFilter::CalculateFilteredPixel(
  PixelBuffer *buffer, int x, int y) {
  int kernel_size = kernel_->width();
  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;
  int w = buffer->width();
  int h = buffer->height();

  // loop through the neighbors, including the edges.
  for (int filterY = 0; filterY < kernel_size; filterY++) {
    for (int filterX = 0; filterX < kernel_size; filterX++) {
      int pixelX = (x - kernel_size/ 2 + filterX + w) % w;
      int pixelY = (y - kernel_size/ 2 + filterY + h) % h;
      red += buffer->pixel(pixelX, pixelY).red() *
        kernel_->value(filterX, filterY);
      green += buffer->pixel(pixelX, pixelY).green() *
        kernel_->value(filterX, filterY);
      blue += buffer->pixel(pixelX, pixelY).blue() *
        kernel_->value(filterX, filterY);
    }
  }

  float r = ImageToolsMath::Clamp(red, static_cast<float>(0.0),
    static_cast<float>(1.0));
  float g = ImageToolsMath::Clamp(green, static_cast<float>(0.0),
    static_cast<float>(1.0));
  float b = ImageToolsMath::Clamp(blue, static_cast<float>(0.0),
    static_cast<float>(1.0));
  ColorData new_color = ColorData(r, g, b);

  return new_color;
}

// Needs to be implemented.
void ConvolutionFilter::CleanupFilter() {}

bool ConvolutionFilter::can_calculate_in_place() {
  return false;
}

} /* namespace image_tools */
