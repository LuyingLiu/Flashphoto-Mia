/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_EDGE_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_EDGE_H_

#include <cmath>
#include <string>
#include "imagetools/filter.h"
#include "imagetools/filter_convolution.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** @brief This filter transforms the image into one that only shows the edges
of shapes by convolving it with a 3x3 edge detection kernel. Pixels on the
border of differently colored regions will be bright, while pixels in areas of
low change will be dark.*/
class ConvolutionFilterEdge : public ConvolutionFilter {
 public:
  ConvolutionFilterEdge();
  virtual ~ConvolutionFilterEdge();

  FloatMatrix* CreateKernel() override;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_CONVOLUTION_EDGE_H_
