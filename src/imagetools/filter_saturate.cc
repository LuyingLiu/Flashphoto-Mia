/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#include "imagetools/filter_saturate.h"
#include "imagetools/color_data.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
FilterSaturate::FilterSaturate() {
  scale_ = 1.0;
}

FilterSaturate::FilterSaturate(float scale) {
  scale_ = scale;
}

FilterSaturate::~FilterSaturate() {}

ColorData FilterSaturate::CalculateFilteredPixel(
  PixelBuffer *buffer, int x, int y) {
  ColorData old_color = buffer->pixel(x, y);
  float grey = old_color.Luminance();
  ColorData grey_color = ColorData(grey, grey, grey);
  ColorData new_color = ImageToolsMath::Lerp(grey_color, old_color, scale_);
  return new_color;
}

}  // namespace image_tools
