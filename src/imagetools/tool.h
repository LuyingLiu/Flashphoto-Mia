/*
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Seth Johnson, 2/15/15, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  ...
*/

#ifndef IMAGETOOLS_TOOL_H_
#define IMAGETOOLS_TOOL_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** The base class for an image editing tool.  Every tool "has a" mask.
 Subclasses must define this mask by filling in the CreateMask factory method.
 This base class will then be able to apply the mask to a pixel buffer as the
 tool is dragged around interactively. */
class Tool {
 public:
  Tool();
  virtual ~Tool();

  /** Subclasses must fill in this factory method to define the mask for the
   specific tool they implement. */
  virtual FloatMatrix *CreateMask(float radius) = 0;

  /** The controller (typically the GUI class) must call this method each time
   the user starts a new stroke.  The buffer, paint_color, and radius are
   saved in state variables so that they can be used by subsequent calls to
   AddToStroke() and EndStroke(). */
  virtual void StartStroke(PixelBuffer *buffer, int x, int y,
                           const ColorData &paint_color, float radius);

  /** The controller should call this function after calling StartStroke() to
   add additional line segments to the stroke each time the mouse moves. In
   other words, each call to StartStroke() should by followed by multiple
   calls to AddToStroke().  Keep calling AddToStroke() until the user lifts
   up the mouse button. */
  virtual void AddToStroke(int x, int y);

  /** The controller must call this method to complete the stroke when the
   user releases the mouse button. */
  void EndStroke(int x, int y);

  /** This function will stamp the current mask onto the current buffer exactly
   one time at a location centered at (x,y) within the buffer. */
  void StampMaskOntoBuffer(int x, int y);

  /** This function returns the current paint color used with the tool.  In
   most cases, this is the same as the paint_color passed in to the
   StartStroke() function.  However, some tools, like the blur tool, have
   "special paint" that depends on the underlying pixels in the canvas or some
   other factors.  Thus, this function provides a hook for subclasses to
   override the default paint color to implement special paint colors. */
  virtual ColorData LookupPaintColor(int x, int y);

  /** This function combines (i.e., blends) a paint_color with an underlying
   canvas_color given a mask_intensity.  The default algorithm uses a standard
   blending function:
     paint_color * mask_intensity  +  canvas_color * (1.0 - mask_intensity)
   Some tools require a custom blend.  Thus, this function provides a hook for
   subclasses to override the default blending function. */
  virtual ColorData CombinePaintAndCanvasColor(const ColorData &paint_color,
                                               const ColorData &canvas_color,
                                               float mask_intensity);

  /** Most tools only apply "paint" when they are moved on the canvas, but
   some, like a spray can continue applying more paint over time even if
   they are held in the same place.  Subclasses should override this function
   and return true if the tool allows paint to accumulate even when held
   stationary.  The default implmentation returns false. */
  virtual bool applies_paint_when_stationary();

 protected:
  ColorData paint_color_;
  FloatMatrix *mask_;
  PixelBuffer *buffer_;
  float stamp_overlap_;
  int last_x_;
  int last_y_;

 private:
  // Making the copy constructor and assignment operator private makes it
  // impossible to copy, move, or assign Tools.  This is nice because it means
  // we do not need to worry about accidentally having more than one tool
  // point to the same mask or application strategy.  Each tool owns exactly
  // one of each of these and is in charge of deleting them when it gets
  // deleted.
  Tool(const Tool &rhs) = delete;
  Tool &operator=(const Tool &rhs) = delete;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_TOOL_H_
