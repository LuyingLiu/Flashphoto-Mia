/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_MOTION_BLUR_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_MOTION_BLUR_H_

#include <cmath>
#include <string>
#include "imagetools/filter.h"
#include "imagetools/filter_convolution.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
enum MBlurDir { MBLUR_DIR_N_S, MBLUR_DIR_E_W, MBLUR_DIR_NE_SW,
      MBLUR_DIR_NW_SE };
/** @brief This filter blurs the image by convolving it with an appropriate
motion-blurring kernel. It supports four possible blurring directions
(North-to-South, East-to-West, Northeast-to-Southwest, and
Northwest-to-Southeast) and blur according to the amount specified in the GUI.*/
class ConvolutionFilterMotionBlur : public ConvolutionFilter {
 public:
  ConvolutionFilterMotionBlur();
  ConvolutionFilterMotionBlur(float radius, MBlurDir dir);
  virtual ~ConvolutionFilterMotionBlur();

  float Radius();
  MBlurDir Dir();
  void SetRadius(float radius);
  void SetDir(MBlurDir dir);
  FloatMatrix* CreateKernel() override;

 private:
  float radius_;
  MBlurDir dir_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_CONVOLUTION_MOTION_BLUR_H_
