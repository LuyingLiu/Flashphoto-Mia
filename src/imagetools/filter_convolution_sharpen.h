/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_SHARPEN_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_SHARPEN_H_

#include <cmath>
#include <string>
#include "imagetools/filter.h"
#include "imagetools/filter_convolution.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** @brief This filter sharpens the image (accentuate the edges of shapes) in
proportion to the amount specified in the GUI by convolving the image with an
appropriate sharpening kernel.*/
class ConvolutionFilterSharpen : public ConvolutionFilter {
 public:
  ConvolutionFilterSharpen();
  explicit ConvolutionFilterSharpen(float radius);
  virtual ~ConvolutionFilterSharpen();

  void SetRadius(float radius);
  float Radius();
  FloatMatrix* CreateKernel() override;

 private:
  float radius_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_CONVOLUTION_SHARPEN_H_
