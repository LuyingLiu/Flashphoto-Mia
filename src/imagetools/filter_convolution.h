/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/filter.h"

namespace image_tools {

/** This is the base class for a convolution filter.  Every filter "has a" mask.
 The new color for a pixel depends not only upon the original color of that
 pixel but also upon the original colors of its neighbors. The Subclasses must
 define this mask by filling in the CreateMask factory method.
 This base class will then be able to apply the mask to a pixel buffer as the
 tool is dragged around interactively. */
class ConvolutionFilter : public Filter {
 public:
  ConvolutionFilter();
  virtual ~ConvolutionFilter();

  virtual FloatMatrix* CreateKernel() = 0;

  void SetupFilter() override;

  ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y) override;

  void CleanupFilter() override;

  /** Convolution filters can not operate in place, so the value is set to false
  for these filters. */
  bool can_calculate_in_place() override;

 private:
  FloatMatrix* kernel_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_CONVOLUTION_H_
