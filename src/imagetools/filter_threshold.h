/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_THRESHOLD_H_
#define IMAGETOOLS_FILTER_THRESHOLD_H_

#include <cmath>
#include <string>
#include "imagetools/color_data.h"
#include "imagetools/filter.h"

namespace image_tools {

  /** @brief This filter turns any pixel with an average intensity value greater
  than the threshold parameter set in the GUI white; otherwise turn the pixel
  black. */
class FilterThreshold : public Filter {
 public:
  FilterThreshold();
  explicit FilterThreshold(float threshold);
  virtual ~FilterThreshold();

  inline float threshold() const { return threshold_; }
  inline void SetThreshold(float threshold) { threshold_ = threshold; }

  ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y) override;

 private:
  float threshold_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_THRESHOLD_H_
