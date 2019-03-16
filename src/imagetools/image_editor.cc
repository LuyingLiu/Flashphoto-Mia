/*
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Daniel Keefe, 2018, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  ...
*/

#include <deque>
#include <string>

#include "imagetools/pixel_buffer.h"
#include "imagetools/image_editor.h"

namespace image_tools {

  ImageEditor::ImageEditor() {}

  ImageEditor::ImageEditor(PixelBuffer *buffer){
    current_buffer_ = buffer;
  }

  ImageEditor::~ImageEditor() {}

  void ImageEditor::LoadFromFile(const std::string &filename){
    if (current_buffer_ != NULL) {
      SaveStateForPossibleUndo();
      current_buffer_->LoadFromFile(filename);
    } else {
      current_buffer_ = new PixelBuffer(filename);
    }
  }

  void ImageEditor::SaveToFile(const std::string &filename){
    current_buffer_->SaveToFile(filename);
  }


  Tool* ImageEditor::GetToolByName(const std::string &name){
    if (name == t_blur_.name()) {
      return &t_blur_;
    } else if (name == t_calligraphy_pen_.name()) {
      return &t_calligraphy_pen_;
    } else if (name == t_chalk_.name()) {
      return &t_chalk_;
    } else if (name == t_eraser_.name()) {
      return &t_eraser_;
    } else if (name == t_highlighter_.name()) {
      return &t_highlighter_;
    } else if (name == t_pen_.name()) {
      return &t_pen_;
    } else if (name == t_spray_can_.name()) {
      return &t_spray_can_;
    } else if (name == t_stamp_.name()) {
      return &t_stamp_;
    } else {
      return NULL;
    }
  }

  void ImageEditor::StartStroke(const std::string &tool_name, const ColorData &color,
                   float radius, int x, int y){
    current_tool_ = GetToolByName(tool_name);
    tool_color_ = color;
    tool_radius_ = radius;
    if ((current_tool_) && (current_buffer_)) {
      SaveStateForPossibleUndo();
      current_tool_->StartStroke(current_buffer_, x, y, tool_color_,
                                 tool_radius_);
    }
  }

  void ImageEditor::AddToStroke(int x, int y){
    if ((current_tool_) && (current_buffer_)) {
      current_tool_->AddToStroke(x, y);
    }
  }

  void ImageEditor::EndStroke(int x, int y){
    if ((current_tool_) && (current_buffer_)) {
      current_tool_->EndStroke(x, y);
    }
  }

  void ImageEditor::ApplyBlurFilter(float radius){
    (void)radius;
    SaveStateForPossibleUndo();
    f_blur_.SetRadius(radius);
    current_buffer_ = f_blur_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplyMotionBlurFilter(float radius,MBlurDir dir){
    (void)radius;
    (void)dir;
    SaveStateForPossibleUndo();
    f_motion_blur_.SetRadius(radius);
    f_motion_blur_.SetDir(dir);
    current_buffer_ = f_motion_blur_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplySharpenFilter(float radius){
    SaveStateForPossibleUndo();
    (void)radius;
    f_sharpen_.SetRadius(radius);
    current_buffer_ = f_sharpen_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplyEdgeDetectFilter(){
    SaveStateForPossibleUndo();
    current_buffer_ = f_edge_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplyThresholdFilter(float cutoff_value){
    SaveStateForPossibleUndo();
    (void)cutoff_value;
    f_threshold_.SetThreshold(cutoff_value);
    current_buffer_ = f_threshold_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplySaturateFilter(float scale_factor){
    SaveStateForPossibleUndo();
    (void)scale_factor;
    f_saturate_.SetScale(scale_factor);
    current_buffer_ = f_saturate_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplyChannelsFilter(float red_scale, float green_scale,
                           float blue_scale){
    (void)red_scale;
    (void)green_scale;
    (void)blue_scale;
    f_channels_.SetRedScale(red_scale);
    f_channels_.SetGreenScale(green_scale);
    f_channels_.SetBlueScale(blue_scale);
    current_buffer_ = f_channels_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::ApplyQuantizeFilter(int num_bins){
    SaveStateForPossibleUndo();
    (void)num_bins;
    f_quantize_.SetNumberBins(num_bins);
    current_buffer_ = f_quantize_.ApplyToFilter(current_buffer_);
  }

  void ImageEditor::Undo(){
    if (can_undo()) {
      // save state for a possilbe redo
      undone_states_.push_front(current_buffer_);

      // make the top state on the undo stack the current one
      current_buffer_ = saved_states_.front();
      saved_states_.pop_front();
    }
  }

  void ImageEditor::Redo(){
    if (can_redo()) {
      // save state for a possible undo
      saved_states_.push_front(current_buffer_);

      // make the top state on the redo stack the current one
      current_buffer_ = undone_states_.front();
      undone_states_.pop_front();
    }
  }

  bool ImageEditor::can_undo(){
    return saved_states_.size();
  }

  bool ImageEditor::can_redo(){
    return undone_states_.size();
  }

  PixelBuffer* ImageEditor::pixel_buffer(){
    return current_buffer_;
  }

  void ImageEditor::set_pixel_buffer(PixelBuffer *buffer){
    current_buffer_ = buffer;
  }

  void ImageEditor::SaveStateForPossibleUndo(){
    PixelBuffer *buffer_copy = new PixelBuffer(*current_buffer_);
    saved_states_.push_front(buffer_copy);

    // remove the oldest undos if we've over our limit
    while (saved_states_.size() > max_undos_) {
      delete saved_states_.back();
      saved_states_.pop_back();
    }

    // committing a new state invalidates the states saved in the redo stack,
    // so, we simply clear out this stack.
    while (!undone_states_.empty()) {
      delete undone_states_.back();
      undone_states_.pop_back();
    }
  }

}  // namespace image_tools
