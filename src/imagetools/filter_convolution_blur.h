/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_BLUR_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_BLUR_H_

#include <cmath>
#include <string>
#include "imagetools/filter.h"
#include "imagetools/filter_convolution.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** @brief This filter uses a Gaussian Blur image convolution kernel to blur
the image in proportion to the amount specified in the GUI.*/
class ConvolutionFilterBlur : public ConvolutionFilter {
 public:
  ConvolutionFilterBlur();
  explicit ConvolutionFilterBlur(float radius);
  virtual ~ConvolutionFilterBlur();

  float Radius();
  void SetRadius(float radius);
  FloatMatrix* CreateKernel() override;

 private:
  float radius_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_CONVOLUTION_BLUR_H_
