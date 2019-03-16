/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#include "imagetools/filter_threshold.h"
#include "imagetools/color_data.h"

namespace image_tools {
FilterThreshold::FilterThreshold() {
  threshold_ = 0.5;
}

FilterThreshold::FilterThreshold(float threshold) {
  threshold_ = threshold;
}

FilterThreshold::~FilterThreshold() {}

ColorData FilterThreshold::CalculateFilteredPixel(
  PixelBuffer *buffer, int x, int y) {
  ColorData old_color = buffer->pixel(x, y);
  float old_red = old_color.red();
  float old_green = old_color.green();
  float old_blue = old_color.blue();
  float average = (static_cast<float>(old_red + old_green + old_blue))/3.0;
  if (average > threshold_) {
    ColorData new_color = ColorData(1, 1, 1);
    return new_color;
  } else {
    ColorData new_color = ColorData(0, 0, 0);
    return new_color;
  }
}

}  // namespace image_tools
