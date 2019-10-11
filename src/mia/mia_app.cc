/**
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Seth Johnson, 2/15/15, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  Daniel Keefe, 2018, UMN -- ported to MinGfx
  ...
*/

#include "mia/mia_app.h"
#include <assert.h>
#include <mingfx.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <imagetools/image_editor.h>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

MiaApp::MiaApp(int width, int height, const ColorData &background_color)
    : GraphicsApp(width, height, "Medical Image Analysis (MIA)"),
      tool_name_(ToolStamp::name()),
      tool_color_(ColorData(0.8, 0.2, 0.2)),
      tool_radius_(14.0),
      painting_(false),
      blur_radius_(5.0),
      sharpen_radius_(5.0),
      thresh_cutoff_(0.5),
      quant_bins_(5) {
  PixelBuffer *buf = new PixelBuffer(width, height, background_color);
  image_editor_.set_pixel_buffer(buf);
}

MiaApp::~MiaApp() {}

void MiaApp::InitNanoGUI() {
  // Setup the GUI window
  nanogui::Window *window = new nanogui::Window(screen(), "MIA Tools");
  window->setPosition(Eigen::Vector2i(10, 10));
  window->setSize(Eigen::Vector2i(200, 100));
  window->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Button *b;

  // FILE Section

  new nanogui::Label(window, "File", "sans-bold");

  nanogui::Widget *file_io = new nanogui::Widget(window);
  file_io->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                            nanogui::Alignment::Middle, 0, 6));
  b = new nanogui::Button(file_io, "Open");
  b->setFixedSize({72, 20});
  b->setCallback([this] {
    std::string fname =
        nanogui::file_dialog({{"png", "Portable Network Graphics"}}, false);
    if (fname != "") {
      image_editor_.LoadFromFile(fname);
      ResizeWindow(image_editor_.pixel_buffer()->width(),
                   image_editor_.pixel_buffer()->height());
    }
  });
  b = new nanogui::Button(file_io, "Save");
  b->setFixedSize({72, 20});
  b->setCallback([this] {
    std::string fname =
        nanogui::file_dialog({{"png", "Portable Network Graphics"}}, true);
    if (fname != "") {
      image_editor_.SaveToFile(fname);
    }
  });

  // EDIT Section

  new nanogui::Label(window, "Edit", "sans-bold");

  nanogui::Widget *undo_redo = new nanogui::Widget(window);
  undo_redo->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  undo_btn_ = new nanogui::Button(undo_redo, "Undo");
  undo_btn_->setFixedSize({72, 20});
  undo_btn_->setIcon(ENTYPO_ICON_REPLY);
  undo_btn_->setCallback([this]() {
    if (image_editor_.can_undo()) {
      image_editor_.Undo();
      ResizeWindow(image_editor_.pixel_buffer()->width(),
                   image_editor_.pixel_buffer()->height());
    }
  });
  redo_btn_ = new nanogui::Button(undo_redo, "Redo");
  redo_btn_->setFixedSize({72, 20});
  redo_btn_->setIcon(ENTYPO_ICON_FORWARD);
  redo_btn_->setCallback([this]() {
    if (image_editor_.can_redo()) {
      image_editor_.Redo();
      ResizeWindow(image_editor_.pixel_buffer()->width(),
                   image_editor_.pixel_buffer()->height());
    }
  });

  // TOOLS Section

  new nanogui::Label(window, "MIA Tools", "sans-bold");

  nanogui::Widget *tools = new nanogui::Widget(window);
  tools->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  // Stamp
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption("Mark");
  b->setCallback([this]() {
    tool_name_ = ToolStamp::name();
    tool_radius_ = 14;
  });
  b->setPushed(true);

  // Pen
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolPen::name());
  b->setCallback([this]() {
    tool_name_ = ToolPen::name();
    tool_radius_ = 2;
  });

  // Tool Color
  new nanogui::Label(tools, "Tool Color:", "sans-bold");
  ColorData col = tool_color_;
  nanogui::ColorPicker *cp1 = new nanogui::ColorPicker(
      tools, nanogui::Color(col.red(), col.green(), col.blue(), col.alpha()));
  cp1->setFixedSize({150, 20});
  cp1->setFinalCallback([this](const nanogui::Color &c) {
    tool_color_ = ColorData(c.r(), c.g(), c.b(), c.w());
  });

  // FILTERS Section

  nanogui::GridLayout *params_layout = new nanogui::GridLayout(
      nanogui::Orientation::Horizontal, 2, nanogui::Alignment::Middle, 15, 5);
  params_layout->setColAlignment(
      {nanogui::Alignment::Maximum, nanogui::Alignment::Fill});
  params_layout->setSpacing(0, 10);

  new nanogui::Label(window, "Filters", "sans-bold");

  nanogui::Widget *filters = new nanogui::Widget(window);
  filters->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  // BLUR
  nanogui::PopupButton *blur_pb = new nanogui::PopupButton(filters, "Blur");
  blur_pb->setFixedSize({150, 20});

  nanogui::Popup *blur_win = blur_pb->popup();
  blur_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *blur_params = new nanogui::Widget(blur_win);
  blur_params->setLayout(params_layout);

  new nanogui::Label(blur_params, "Blur Amount:", "sans-bold");
  nanogui::Widget *blur_param1 = new nanogui::Widget(blur_params);
  blur_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *br_slider = new nanogui::Slider(blur_param1);
  br_slider->setRange(std::make_pair(0, 10));
  br_slider->setValue(blur_radius_);
  br_slider->setFixedWidth(150);
  nanogui::TextBox *br_text = new nanogui::TextBox(blur_param1);
  br_text->setFixedSize({60, 20});
  br_text->setFontSize(18);
  br_text->setAlignment(nanogui::TextBox::Alignment::Right);
  br_text->setValue(std::to_string(static_cast<int>(blur_radius_)));
  br_slider->setCallback([this, br_text](float value) {
    br_text->setValue(std::to_string(static_cast<int>(value)));
    blur_radius_ = value;
  });
  b = new nanogui::Button(blur_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor_.ApplyBlurFilter(blur_radius_); });

  // SHARPEN
  nanogui::PopupButton *sharp = new nanogui::PopupButton(filters, "Sharpen");
  sharp->setFixedSize({150, 20});

  nanogui::Popup *sharp_win = sharp->popup();
  sharp_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *sharp_params = new nanogui::Widget(sharp_win);
  sharp_params->setLayout(params_layout);

  new nanogui::Label(sharp_params, "Amount:", "sans-bold");
  nanogui::Widget *sharp_param1 = new nanogui::Widget(sharp_params);
  sharp_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *sh_slider = new nanogui::Slider(sharp_param1);
  sh_slider->setRange(std::make_pair(0, 10));
  sh_slider->setValue(sharpen_radius_);
  sh_slider->setFixedWidth(150);
  nanogui::TextBox *sh_text = new nanogui::TextBox(sharp_param1);
  sh_text->setFixedSize({60, 20});
  sh_text->setFontSize(18);
  sh_text->setAlignment(nanogui::TextBox::Alignment::Right);
  sh_text->setValue(std::to_string(static_cast<int>(sharpen_radius_)));
  sh_slider->setCallback([this, sh_text](float value) {
    sh_text->setValue(std::to_string(static_cast<int>(value)));
    sharpen_radius_ = value;
  });

  b = new nanogui::Button(sharp_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor_.ApplySharpenFilter(sharpen_radius_); });

  // EDGE DETECT
  nanogui::PopupButton *edge = new nanogui::PopupButton(filters, "Edge Detect");
  edge->setFixedSize({150, 20});

  nanogui::Popup *edge_win = edge->popup();
  edge_win->setLayout(params_layout);
  b = new nanogui::Button(edge_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor_.ApplyEdgeDetectFilter(); });

  // THRESHOLD
  nanogui::PopupButton *thresh = new nanogui::PopupButton(filters, "Threshold");
  thresh->setFixedSize({150, 20});

  nanogui::Popup *thresh_win = thresh->popup();
  thresh_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *thresh_params = new nanogui::Widget(thresh_win);
  thresh_params->setLayout(params_layout);

  new nanogui::Label(thresh_params, "Cutoff Value:", "sans-bold");
  nanogui::Widget *thresh_param1 = new nanogui::Widget(thresh_params);
  thresh_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *th_slider = new nanogui::Slider(thresh_param1);
  th_slider->setRange(std::make_pair(0, 1));
  th_slider->setValue(thresh_cutoff_);
  th_slider->setFixedWidth(150);
  nanogui::TextBox *th_text = new nanogui::TextBox(thresh_param1);
  th_text->setFixedSize({60, 20});
  th_text->setFontSize(18);
  th_text->setAlignment(nanogui::TextBox::Alignment::Right);
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << thresh_cutoff_;
  th_text->setValue(stream.str());
  th_slider->setCallback([this, th_text](float value) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    th_text->setValue(stream.str());
    thresh_cutoff_ = value;
  });

  b = new nanogui::Button(thresh_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback(
      [this] { image_editor_.ApplyThresholdFilter(thresh_cutoff_); });

  // QUANTIZE
  nanogui::PopupButton *quant_pb =
      new nanogui::PopupButton(filters, "Quantize");
  quant_pb->setFixedSize({150, 20});

  nanogui::Popup *quant_win = quant_pb->popup();
  quant_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *quant_params = new nanogui::Widget(quant_win);
  quant_params->setLayout(params_layout);

  new nanogui::Label(quant_params, "Number of Bins:", "sans-bold");
  nanogui::Widget *quant_param1 = new nanogui::Widget(quant_params);
  quant_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *q_slider = new nanogui::Slider(quant_param1);
  q_slider->setRange(std::make_pair(1, 256));
  q_slider->setValue(quant_bins_);
  q_slider->setFixedWidth(150);
  nanogui::TextBox *q_text = new nanogui::TextBox(quant_param1);
  q_text->setFixedSize({60, 20});
  q_text->setFontSize(18);
  q_text->setAlignment(nanogui::TextBox::Alignment::Right);
  q_text->setValue(std::to_string(quant_bins_));
  q_slider->setCallback([this, q_text](float value) {
    q_text->setValue(std::to_string(static_cast<int>(value)));
    quant_bins_ = static_cast<int>(value);
  });

  b = new nanogui::Button(quant_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] {
    image_editor_.ApplyQuantizeFilter(static_cast<int>(quant_bins_));
  });

  screen()->performLayout();
}

void MiaApp::InitOpenGL() {
  display_texture_.InitFromFloats(image_editor_.pixel_buffer()->width(),
                                  image_editor_.pixel_buffer()->height(),
                                  image_editor_.pixel_buffer()->data());
}

void MiaApp::DrawUsingNanoVG(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, tool_x_, tool_y_, tool_radius_);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 128));
  nvgStroke(ctx);
}

void MiaApp::DrawUsingOpenGL() {
  undo_btn_->setEnabled(image_editor_.can_undo());
  redo_btn_->setEnabled(image_editor_.can_redo());

  if (display_texture_.initialized()) {
    display_texture_.UpdateFromFloats(image_editor_.pixel_buffer()->data());
    ColorData bg = image_editor_.pixel_buffer()->background_color();
    glClearColor(bg.red(), bg.blue(), bg.green(), 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    quick_shapes_.DrawFullscreenTexture(mingfx::Color(1, 1, 1),
                                        display_texture_);
  }
}

void MiaApp::OnMouseMove(const mingfx::Point2 &pos,
                         const mingfx::Vector2 &delta) {
  tool_x_ = pos[0];
  tool_y_ = pos[1];
}

void MiaApp::OnLeftMouseDown(const mingfx::Point2 &pos) {
  tool_x_ = pos[0];
  tool_y_ = pos[1];
  image_editor_.StartStroke(tool_name_, tool_color_, tool_radius_, tool_x_,
                            tool_y_);
  painting_ = true;
}

void MiaApp::OnLeftMouseDrag(const mingfx::Point2 &pos,
                             const mingfx::Vector2 &delta) {
  // note: AddToStroke() is called inside UpdateSimulation to support tools like
  // the spray can that accumulate paint over time when the mouse is held down
  // even if not actually moving.
  tool_x_ = pos[0];
  tool_y_ = pos[1];
}

void MiaApp::OnLeftMouseUp(const mingfx::Point2 &pos) {
  tool_x_ = pos[0];
  tool_y_ = pos[1];
  image_editor_.EndStroke(pos[0], pos[1]);
  painting_ = false;
}

void MiaApp::UpdateSimulation(double dt) {
  if (painting_) {
    image_editor_.AddToStroke(tool_x_, tool_y_);
  }
}

void MiaApp::OnWindowResize(int new_width, int new_height) {
  image_editor_.pixel_buffer()->Resize(new_width, new_height);
  display_texture_ = mingfx::Texture2D();
  display_texture_.InitFromFloats(image_editor_.pixel_buffer()->width(),
                                  image_editor_.pixel_buffer()->height(),
                                  image_editor_.pixel_buffer()->data());
}

void MiaApp::LoadFromFile(const std::string &filename){
  image_editor_.LoadFromFile(filename);
}

void MiaApp::SaveToFile(const std::string &filename){
  image_editor_.SaveToFile(filename);
}

// TOOLS

Tool *MiaApp::GetToolByName(const std::string &name){
  return image_editor_.GetToolByName(name);
}

void MiaApp::StartStroke(const std::string &tool_name, const ColorData &color,
                 float radius, int x, int y){
  image_editor_.StartStroke(tool_name, color, radius, x, y);
}

void MiaApp::AddToStroke(int x, int y){
  image_editor_.AddToStroke(x, y);
}

void MiaApp::EndStroke(int x, int y){
  image_editor_.EndStroke(x, y);
}

// FILTERS

void MiaApp::ApplyBlurFilter(float radius){
  image_editor_.ApplyBlurFilter(radius);
}

void MiaApp::ApplySharpenFilter(float radius){
  image_editor_.ApplySharpenFilter(radius);
}

void MiaApp::ApplyEdgeDetectFilter(){
  image_editor_.ApplyEdgeDetectFilter();
}

void MiaApp::ApplyThresholdFilter(float cutoff_value){
  image_editor_.ApplyThresholdFilter(cutoff_value);
}

void MiaApp::ApplyQuantizeFilter(int num_bins){
  image_editor_.ApplyQuantizeFilter(num_bins);
}

PixelBuffer *MiaApp::pixel_buffer(){
  return image_editor_.pixel_buffer();
}

void MiaApp::set_pixel_buffer(PixelBuffer *buffer){
  image_editor_.set_pixel_buffer(buffer);
}

void MiaApp::FlashPhotoApp::SaveStateForPossibleUndo() {
  image_editor_.SaveStateForPossibleUndo();
}


}  // namespace image_tools
