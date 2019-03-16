/*
This code is a part of student coursework.  It is not an open source
project.

Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/

#include "imagetools/filter.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

Filter::Filter() {}

Filter::~Filter() {}

PixelBuffer* Filter::ApplyToFilter(PixelBuffer *buffer) {
  if (can_calculate_in_place()) {
    SetupFilter();

    int x = buffer->width();
    int y = buffer->height();
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        ColorData new_color = CalculateFilteredPixel(buffer, i, j);
        buffer->set_pixel(i, j, new_color);
      }
    }

    CleanupFilter();
    return buffer;
  } else {
    SetupFilter();

    PixelBuffer new_buffer = *buffer;
    int x = buffer->width();
    int y = buffer->height();
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        ColorData new_color = CalculateFilteredPixel(buffer, i, j);
        new_buffer.set_pixel(i, j, new_color);
      }
    }

    CleanupFilter();
    *buffer = new_buffer;
    return buffer;
  }
}

void Filter::SetupFilter() {}

void Filter::CleanupFilter() {}

bool Filter::can_calculate_in_place() {
  return true;
}

} /* namespace image_tools */
