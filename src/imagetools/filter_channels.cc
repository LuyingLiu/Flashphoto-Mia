/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#include "imagetools/filter_channels.h"
#include "imagetools/color_data.h"

namespace image_tools {

FilterChannels::FilterChannels() {
  red_scale_ = 1.0;
  green_scale_ = 1.0;
  blue_scale_ = 1.0;
}

FilterChannels::FilterChannels(float red_scale,
  float green_scale, float blue_scale) {
  red_scale_ = red_scale;
  green_scale_ = green_scale;
  blue_scale_ = blue_scale;
}

FilterChannels::~FilterChannels() {}

ColorData FilterChannels::CalculateFilteredPixel(
  PixelBuffer *buffer, int x, int y) {
  ColorData old_color = buffer->pixel(x, y);
  float old_red = old_color.red();
  float old_green = old_color.green();
  float old_blue = old_color.blue();
  ColorData new_color = ColorData(red_scale_ * old_red,
    green_scale_ * old_green, blue_scale_ * old_blue);
  return new_color;
}

}  // namespace image_tools
