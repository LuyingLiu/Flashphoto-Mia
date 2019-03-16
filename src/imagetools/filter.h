/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#ifndef IMAGETOOLS_FILTER_H_
#define IMAGETOOLS_FILTER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** The base class for an image filter.
 This base class will then be able to apply filter to a pixel buffer as the
 tool is dragged around interactively. */
class Filter {
 public:
  Filter();
  virtual ~Filter();

  /* This function applies the filer to the image, and returns a new image
  after filter. If the filters can operate in place, we can apply the filter to
  the original buffer directly. Otherwise, we need to save a copy of the
  original buffer before modifying. */
  PixelBuffer* ApplyToFilter(PixelBuffer *buffer);

  /** The controller (typically the GUI class) must call this method each time
   the user starts a new filter. This sets up the filter. */
  virtual void SetupFilter();

  /** The controller should call this function after calling SetupFilter() to
   calculate the ColorData for each pixel, each call to SetupFilter() should be
   followed by multiple calls to CalculateFilteredPixel().  Keep calling
   CalculateFilteredPixel() until the image has be traversed. */
  virtual ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y)
    = 0;

  /** The controller must call this method to complete the image filtering
   when the image has been traversed. */
  virtual void CleanupFilter();

  /** Some filters can operate in place, while others cannot. Subclasses
   should override this function and return false if the filter cannot operate
   in place. The default implmentation returns true. */
  virtual bool can_calculate_in_place();
};

}  // namespace image_tools

#endif  // FLASHPHOTO_FILTER_H_
