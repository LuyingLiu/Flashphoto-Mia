/**
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

#include "imagetools/image_editor_commands.h"

#include "imagetools/image_editor.h"

namespace image_tools {

ImageEditorCommand::ImageEditorCommand(ImageEditor *image_editor)
    : image_editor_(image_editor) {}

ImageEditorCommand::~ImageEditorCommand() {}

BlurFilterCommand::BlurFilterCommand(ImageEditor *image_editor, float radius)
    : ImageEditorCommand(image_editor), radius_(radius) {}

BlurFilterCommand::~BlurFilterCommand() {}

void BlurFilterCommand::Execute() { image_editor_->ApplyBlurFilter(radius_); }

EdgeFilterCommand::EdgeFilterCommand(ImageEditor *image_editor)
    : ImageEditorCommand(image_editor) {}

EdgeFilterCommand::~EdgeFilterCommand() {}

void EdgeFilterCommand::Execute() { image_editor_->ApplyEdgeDetectFilter(); }

SharpenFilterCommand::SharpenFilterCommand(ImageEditor *image_editor,
                                           float radius)
    : ImageEditorCommand(image_editor), radius_(radius) {}

SharpenFilterCommand::~SharpenFilterCommand() {}

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

void ChannelsFilterCommand::Execute() {
  image_editor_->ApplyChannelsFilter(r_, g_, b_);
}

QuantizeFilterCommand::QuantizeFilterCommand(ImageEditor *image_editor,
                                             int bins)
    : ImageEditorCommand(image_editor), bins_(bins) {}

QuantizeFilterCommand::~QuantizeFilterCommand() {}

void QuantizeFilterCommand::Execute() {
  image_editor_->ApplyQuantizeFilter(bins_);
}

SaturateFilterCommand::SaturateFilterCommand(ImageEditor *image_editor,
                                             float scale)
    : ImageEditorCommand(image_editor), scale_(scale) {}

SaturateFilterCommand::~SaturateFilterCommand() {}

void SaturateFilterCommand::Execute() {
  image_editor_->ApplySaturateFilter(scale_);
}

ThresholdFilterCommand::ThresholdFilterCommand(ImageEditor *image_editor,
                                               float cutoff)
    : ImageEditorCommand(image_editor), cutoff_(cutoff) {}

ThresholdFilterCommand::~ThresholdFilterCommand() {}

void ThresholdFilterCommand::Execute() {
  image_editor_->ApplyThresholdFilter(cutoff_);
}

MotionBlurFilterCommand::MotionBlurFilterCommand(
    ImageEditor *image_editor, float radius,
    MBlurDir dir)
    : ImageEditorCommand(image_editor), radius_(radius), dir_(dir) {}

MotionBlurFilterCommand::~MotionBlurFilterCommand() {}

void MotionBlurFilterCommand::Execute() {
  image_editor_->ApplyMotionBlurFilter(radius_, dir_);
}

UndoCommand::UndoCommand(ImageEditor *image_editor)
    : ImageEditorCommand(image_editor) {}

UndoCommand::~UndoCommand() {}

void UndoCommand::Execute() { image_editor_->Undo(); }

RedoCommand::RedoCommand(ImageEditor *image_editor)
    : ImageEditorCommand(image_editor) {}

RedoCommand::~RedoCommand() {}

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

void StartStrokeCommand::Execute() {
  image_editor_->StartStroke(tool_name_, color_, radius_, x_, y_);
}

AddToStrokeCommand::AddToStrokeCommand(ImageEditor *image_editor, int x, int y)
    : ImageEditorCommand(image_editor), x_(x), y_(y) {}

AddToStrokeCommand::~AddToStrokeCommand() {}

void AddToStrokeCommand::Execute() { image_editor_->AddToStroke(x_, y_); }

EndStrokeCommand::EndStrokeCommand(ImageEditor *image_editor, int x, int y)
    : ImageEditorCommand(image_editor), x_(x), y_(y) {}

EndStrokeCommand::~EndStrokeCommand() {}

void EndStrokeCommand::Execute() { image_editor_->EndStroke(x_, y_); }

LoadCommand::LoadCommand(ImageEditor *image_editor, const std::string &filename)
    : ImageEditorCommand(image_editor), filename_(filename) {}

LoadCommand::~LoadCommand() {}

void LoadCommand::Execute() { image_editor_->LoadFromFile(filename_); }

SaveCommand::SaveCommand(ImageEditor *image_editor, const std::string &filename)
    : ImageEditorCommand(image_editor), filename_(filename) {}

SaveCommand::~SaveCommand() {}

void SaveCommand::Execute() { image_editor_->SaveToFile(filename_); }

}  // namespace image_tools
