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

#include "mia/image_editor_commands.h"

#include "imagetools/image_editor.h"

namespace image_tools {

ImageEditorCommand::ImageEditorCommand(ImageEditor *image_editor)
    : image_editor_(image_editor) {}

ImageEditorCommand::~ImageEditorCommand() {}

float ImageEditorCommand::Radius() {
  return 0.0;
}

float ImageEditorCommand::Scale() {
  return 0.0;
}
int ImageEditorCommand::Bins() {
  return 0;
}

BlurFilterCommand::BlurFilterCommand(ImageEditor *image_editor, float radius)
    : ImageEditorCommand(image_editor), radius_(radius) {}

BlurFilterCommand::~BlurFilterCommand() {}

std::string BlurFilterCommand::Name() {
  std::string name = "blur";
  return name;
}

float BlurFilterCommand::Radius() {
  return radius_;
}

void BlurFilterCommand::Execute() { image_editor_->ApplyBlurFilter(radius_); }

EdgeFilterCommand::EdgeFilterCommand(ImageEditor *image_editor)
    : ImageEditorCommand(image_editor) {}

EdgeFilterCommand::~EdgeFilterCommand() {}

std::string EdgeFilterCommand::Name() {
  std::string name = "edge";
  return name;
}

void EdgeFilterCommand::Execute() { image_editor_->ApplyEdgeDetectFilter(); }

SharpenFilterCommand::SharpenFilterCommand(ImageEditor *image_editor,
                                           float radius)
    : ImageEditorCommand(image_editor), radius_(radius) {}

SharpenFilterCommand::~SharpenFilterCommand() {}

std::string SharpenFilterCommand::Name() {
  std::string name = "sharpen";
  return name;
}

float SharpenFilterCommand::Radius() {
  return radius_;
}

void SharpenFilterCommand::Execute() {
  image_editor_->ApplySharpenFilter(radius_);
}

ChannelsFilterCommand::ChannelsFilterCommand(ImageEditor *image_editor,
                                             float red_scale, float green_scale,
                                             float blue_scale)
    : ImageEditorCommand(image_editor),
      r_(red_scale),
      g_(green_scale),
      b_(blue_scale) {}

ChannelsFilterCommand::~ChannelsFilterCommand() {}

std::string ChannelsFilterCommand::Name() {
  std::string name = "channels";
  return name;
}

float ChannelsFilterCommand::Scale() {
  return r_;
}

void ChannelsFilterCommand::Execute() {
  image_editor_->ApplyChannelsFilter(r_, g_, b_);
}

QuantizeFilterCommand::QuantizeFilterCommand(ImageEditor *image_editor,
                                             int bins)
    : ImageEditorCommand(image_editor), bins_(bins) {}

QuantizeFilterCommand::~QuantizeFilterCommand() {}

std::string QuantizeFilterCommand::Name() {
  std::string name = "quantize";
  return name;
}

int QuantizeFilterCommand::Bins() {
  return bins_;
}

void QuantizeFilterCommand::Execute() {
  image_editor_->ApplyQuantizeFilter(bins_);
}

SaturateFilterCommand::SaturateFilterCommand(ImageEditor *image_editor,
                                             float scale)
    : ImageEditorCommand(image_editor), scale_(scale) {}

SaturateFilterCommand::~SaturateFilterCommand() {}

std::string SaturateFilterCommand::Name() {
  std::string name = "saturate";
  return name;
}

float SaturateFilterCommand::Scale() {
  return scale_;
}

void SaturateFilterCommand::Execute() {
  image_editor_->ApplySaturateFilter(scale_);
}

ThresholdFilterCommand::ThresholdFilterCommand(ImageEditor *image_editor,
                                               float cutoff)
    : ImageEditorCommand(image_editor), cutoff_(cutoff) {}

ThresholdFilterCommand::~ThresholdFilterCommand() {}

std::string ThresholdFilterCommand::Name() {
  std::string name = "threshold";
  return name;
}

void ThresholdFilterCommand::Execute() {
  image_editor_->ApplyThresholdFilter(cutoff_);
}

MotionBlurFilterCommand::MotionBlurFilterCommand(
    ImageEditor *image_editor, float radius,
    MBlurDir dir)
    : ImageEditorCommand(image_editor), radius_(radius), dir_(dir) {}

MotionBlurFilterCommand::~MotionBlurFilterCommand() {}

std::string MotionBlurFilterCommand::Name() {
  std::string name = "motionblur";
  return name;
}

void MotionBlurFilterCommand::Execute() {
  image_editor_->ApplyMotionBlurFilter(radius_, dir_);
}

UndoCommand::UndoCommand(ImageEditor *image_editor)
    : ImageEditorCommand(image_editor) {}

UndoCommand::~UndoCommand() {}

std::string UndoCommand::Name() {
  std::string name = "undo";
  return name;
}

void UndoCommand::Execute() { image_editor_->Undo(); }

RedoCommand::RedoCommand(ImageEditor *image_editor)
    : ImageEditorCommand(image_editor) {}

RedoCommand::~RedoCommand() {}

std::string RedoCommand::Name() {
  std::string name = "redo";
  return name;
}

void RedoCommand::Execute() { image_editor_->Redo(); }

StartStrokeCommand::StartStrokeCommand(ImageEditor *image_editor,
                                       const std::string &tool_name,
                                       const ColorData &color, float radius,
                                       int x, int y)
    : ImageEditorCommand(image_editor),
      tool_name_(tool_name),
      color_(color),
      radius_(radius),
      x_(x),
      y_(y) {}

StartStrokeCommand::~StartStrokeCommand() {}

std::string StartStrokeCommand::Name() {
  std::string name = "startstroke";
  return name;
}

void StartStrokeCommand::Execute() {
  image_editor_->StartStroke(tool_name_, color_, radius_, x_, y_);
}

AddToStrokeCommand::AddToStrokeCommand(ImageEditor *image_editor, int x, int y)
    : ImageEditorCommand(image_editor), x_(x), y_(y) {}

AddToStrokeCommand::~AddToStrokeCommand() {}

std::string AddToStrokeCommand::Name() {
  std::string name = "addtostroke";
  return name;
}

void AddToStrokeCommand::Execute() { image_editor_->AddToStroke(x_, y_); }

EndStrokeCommand::EndStrokeCommand(ImageEditor *image_editor, int x, int y)
    : ImageEditorCommand(image_editor), x_(x), y_(y) {}

EndStrokeCommand::~EndStrokeCommand() {}

std::string EndStrokeCommand::Name() {
  std::string name = "endstroke";
  return name;
}

void EndStrokeCommand::Execute() { image_editor_->EndStroke(x_, y_); }

LoadCommand::LoadCommand(ImageEditor *image_editor, const std::string &filename)
    : ImageEditorCommand(image_editor), filename_(filename) {}

LoadCommand::~LoadCommand() {}

std::string LoadCommand::Name() {
  std::string name = "load";
  return name;
}

void LoadCommand::Execute() { image_editor_->LoadFromFile(filename_); }

SaveCommand::SaveCommand(ImageEditor *image_editor, const std::string &filename)
    : ImageEditorCommand(image_editor), filename_(filename) {}

SaveCommand::~SaveCommand() {}

std::string SaveCommand::Name() {
  std::string name = "save";
  return name;
}

void SaveCommand::Execute() { image_editor_->SaveToFile(filename_); }

}  // namespace image_tools
