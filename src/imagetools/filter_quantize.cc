/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#include "imagetools/filter_quantize.h"
#include "imagetools/color_data.h"

namespace image_tools {

FilterQuantize::FilterQuantize() {
  number_bins_ = 5;
}

FilterQuantize::FilterQuantize(int number_bins) {
  number_bins_ = number_bins;
}

FilterQuantize::~FilterQuantize() {}

ColorData FilterQuantize::CalculateFilteredPixel(
  PixelBuffer *buffer, int x, int y) {
  ColorData old_color = buffer->pixel(x, y);
  float old_red = old_color.red();
  float old_green = old_color.green();
  float old_blue = old_color.blue();

  int num_steps = number_bins_- 1;
  if (num_steps > 0) {
    float new_red = round(old_red * num_steps) / num_steps;
    float new_green = round(old_green * num_steps) / num_steps;
    float new_blue = round(old_blue * num_steps) / num_steps;

    ColorData new_color = ColorData(new_red, new_green, new_blue);
    return new_color;
  } else {
    return ColorData(0, 0, 0);
  }
}

}  // namespace image_tools
