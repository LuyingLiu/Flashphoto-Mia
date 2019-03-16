/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_QUANTIZE_H_
#define IMAGETOOLS_FILTER_QUANTIZE_H_

#include <cmath>
#include <string>
#include "imagetools/color_data.h"
#include "imagetools/filter.h"

namespace image_tools {

/** @brief This filter reduces the number of unique colors in the image by
binning similar colors.It takes a preset number of bins as input.*/
class FilterQuantize : public Filter {
 public:
  FilterQuantize();
  explicit FilterQuantize(int number_bins);
  virtual ~FilterQuantize();

  inline float NumberBins() const {return number_bins_; }
  inline void SetNumberBins(int number_bins) {
    number_bins_ = number_bins;
  }

  ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y) override;

 private:
  int number_bins_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_QUANTIZE_H_
