#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <math.h>

#include "imagetools/image_editor.h"
#include "imagetools/filter_channels.h"
#include "imagetools/color_data.h"

using image_tools::ImageEditor;
using image_tools::PixelBuffer;
using image_tools::ColorData;

class FilterRegressionTests : public ::testing::Test {
 public:
 void SetUp() override {
    image_editor_truth_ = new ImageEditor();
    image_editor_truth_->set_pixel_buffer(new PixelBuffer(50,50,ColorData(1.0,1.0,1.0,1.0)));
    image_editor_compare_ = new ImageEditor();
    image_editor_compare_->set_pixel_buffer(new PixelBuffer(50,50,ColorData(1.0,1.0,1.0,1.0)));
  }
 protected:
 ImageEditor *image_editor_truth_;
 ImageEditor *image_editor_compare_;
};

// Test blur filter
TEST_F(FilterRegressionTests, FilterBlurTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-blur-5.0.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplyBlurFilter(5.0);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "blur filter is not valid";
}

// Test motion blur filter
TEST_F(FilterRegressionTests, FilterMotionBlurTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-MotionBlur-NE-SW-3.0.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplyMotionBlurFilter(3.0, image_tools::MBLUR_DIR_NE_SW);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "motion blur filter is not valid";
}

// Test sharpen filter
TEST_F(FilterRegressionTests, FilterSharpenTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-Sharpen-7.0.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplySharpenFilter(7.0);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "sharpen filter is not valid";
}

// Test edge detect filter
TEST_F(FilterRegressionTests, FilterEdgeDetectTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-EdgeDetect-3.0.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplyEdgeDetectFilter();
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "edge detect filter is not valid";
}

// Test threshold filter
TEST_F(FilterRegressionTests, FilterThresholdTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-Threshold-0.5.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplyThresholdFilter(0.5);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "threshold filter is not valid";
}

// Test saturate filter
TEST_F(FilterRegressionTests, FilterSaturateTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-Saturate-0.5.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplySaturateFilter(0.5);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "saturate filter is not valid";
}

// Test channels filter
TEST_F(FilterRegressionTests, FilterChannelsTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-Channels-0.5-0.6-0.7.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplyChannelsFilter(0.5, 0.6, 0.7);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "channels filter is not valid";
}

// Test quantize filter
TEST_F(FilterRegressionTests, FilterQuantizeTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-Quantize-5.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);
  image_editor_compare_->ApplyQuantizeFilter(5);
  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "quantize filter is not valid";
}

// Test tool blur
TEST_F(FilterRegressionTests, FilterToolBlurTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolBlur.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Blur", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool blur is not valid";
}

// Test tool calligraphy pen
TEST_F(FilterRegressionTests, FilterToolCalligraphyPenTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolCalligraphyPen.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Caligraphy Pen", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool calligraphy pen is not valid";
}

// Test tool chalk
TEST_F(FilterRegressionTests, FilterToolChalkTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolChalk.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Chalk", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool chalk is not valid";
}

// Test tool eraser
TEST_F(FilterRegressionTests, FilterToolEraserTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolEraser.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Eraser", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool eraser is not valid";
}

// Test tool highlighter
TEST_F(FilterRegressionTests, FilterToolHighlighterTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolHighlighter.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Highlighter", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool highlighter is not valid";
}

// Test tool pen
TEST_F(FilterRegressionTests, FilterToolPenTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolPen.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Pen", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool pen is not valid";
}

// Test tool spray
TEST_F(FilterRegressionTests, FilterToolSprayCanTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolSprayCan.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Spray Can", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool spray can is not valid";
}

// Test tool stamp
TEST_F(FilterRegressionTests, FilterToolStampTests) {
  PixelBuffer *input = new PixelBuffer("resources/rose-input.png");
  PixelBuffer *expected_out = new PixelBuffer("resources/rose-ToolStamp.png");
  image_editor_compare_->set_pixel_buffer(input);
  image_editor_truth_->set_pixel_buffer(expected_out);

  image_editor_compare_->StartStroke("Stamp", ColorData(0.0, 0.0, 0.0, 1.0), 50.0, 500, 0);
  for (int i = 1; i < 500; i++){
    image_editor_compare_->AddToStroke(500, i);
  }
  image_editor_compare_->EndStroke(500, 100);

  PixelBuffer *output = image_editor_compare_->pixel_buffer();
  EXPECT_EQ(*output, *expected_out) << "tool stamp is not valid";
}
