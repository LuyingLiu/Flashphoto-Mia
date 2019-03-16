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

#ifndef IMAGETOOLS_COLOR_DATA_H_
#define IMAGETOOLS_COLOR_DATA_H_

namespace image_tools {

/** @brief This color data class stores color in floating point format.
 The Red, Green, Blue, and Alpha channels range from 0.0 to 1.0. */
class ColorData {
 public:
  ColorData();
  ColorData(float r, float g, float b);
  ColorData(float r, float g, float b, float a);

  inline float red() const { return red_; }
  inline void set_red(float r) { red_ = r; }

  inline float green() const { return green_; }
  inline void set_green(float g) { green_ = g; }

  inline float blue() const { return blue_; }
  inline void set_blue(float b) { blue_ = b; }

  inline float alpha() const { return alpha_; }
  inline void set_alpha(float a) { alpha_ = a; }

  /** @brief Calculates the "brightness" of the color according to a
   perceptual metric that weights the red, green, and blue components of the
   color non-uniformly to account for the non-uniformity of the human visual
   system. */
  float Luminance() const;

  /** @brief Clamps each channel of the color so that the data are within
   the range [0.0,1.0]. */
  void Clamp();

  /* Arithmetic operators provide shortcuts for applying operations to all
   components of a color. */
  friend ColorData operator*(const ColorData& a, float f);
  friend ColorData operator+(const ColorData& a, const ColorData& b);
  friend ColorData operator-(const ColorData& a, const ColorData& b);

  /** Check for "equality", taking floating point imprecision into account */
  friend bool operator==(const ColorData& a, const ColorData& b);

  /** Check for "inequality", taking floating point imprecision into account */
  friend bool operator!=(const ColorData& a, const ColorData& b);

 private:
  float red_;
  float green_;
  float blue_;
  float alpha_;
};

}  // namespace image_tools

#endif  // FLASHPHOTO_COLOR_DATA_H_
