/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_CHANNELS_H_
#define IMAGETOOLS_FILTER_CHANNELS_H_

#include <cmath>
#include <string>
#include "imagetools/color_data.h"
#include "imagetools/filter.h"

namespace image_tools {

/** @brief This filter is like a saturation filter, but operates on the Red,
Green, and/or Blue channel separately. Given some scale factors from the user
(one float each for red, green, and blue), this filter simply multiplies the R,
G, and B component for each pixel in the image by the scale factor. */
class FilterChannels : public Filter {
 public:
  FilterChannels();
  FilterChannels(float red_scale, float green_scale, float blue_scale);
  virtual ~FilterChannels();

  inline float RedScale() const { return red_scale_; }
  inline float GreenScale() const { return green_scale_; }
  inline float BlueScale() const { return blue_scale_; }

  inline void SetRedScale(float red_scale) {
    red_scale_ = red_scale;
  }
  inline void SetGreenScale(float green_scale) {
    green_scale_ = green_scale;
  }
  inline void SetBlueScale(float blue_scale) {
    blue_scale_ = blue_scale;
  }

  ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y) override;

 private:
  float red_scale_;
  float green_scale_;
  float blue_scale_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_CHANNELS_H_
