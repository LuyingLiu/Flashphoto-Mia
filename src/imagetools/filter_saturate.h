/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_SATURATE_H_
#define IMAGETOOLS_FILTER_SATURATE_H_

#include <cmath>
#include <string>
#include "imagetools/color_data.h"
#include "imagetools/filter.h"

namespace image_tools {

/** @brief Saturation is a measure of how vibrant the colors in the image are.
A completely non-saturated image would be a grayscale version of the image. This
filter changes the saturation of a pixel buffer.*/
class FilterSaturate : public Filter {
 public:
  FilterSaturate();
  explicit FilterSaturate(float scale);
  virtual ~FilterSaturate();

  inline float scale() const { return scale_; }
  inline void SetScale(float scale) {
    scale_ = scale;
  }
  ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y) override;

 private:
  float scale_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_SATURATE_H_
