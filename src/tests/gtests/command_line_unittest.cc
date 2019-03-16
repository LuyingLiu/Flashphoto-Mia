#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <math.h>
#include "mia/command_line_processor.h"
#include "imagetools/image_editor.h"
#include "imagetools/filter_channels.h"
#include "imagetools/color_data.h"

using image_tools::CommandLineProcessor;
using image_tools::ImageEditor;
using image_tools::ImageEditorCommand;

class CommandLineProcessorTest : public ::testing::Test {
  public:
    void SetUp( ) override {}
};

// Test invalid command of missing input: mia -motionblur-n-s 3.0 out.png
TEST_F(CommandLineProcessorTest, MissInputTests) {
  CommandLineProcessor processor_error_forget_input = CommandLineProcessor();
  const char* argv1[] = { "./build/bin/mia", "-motionblur-n-s", "3.0", "resources/test.png"};
  int output1 = processor_error_forget_input.ProcessCommandLine(4, const_cast<char**>(argv1));
  int expected_out1 = -1;
  EXPECT_EQ(output1, expected_out1) << "invalid command of missing input is not detected";
}

// Test invalid command of missing an argument: mia in.png -motionblur-ne-sw out.png
TEST_F(CommandLineProcessorTest, MissArgumentTests) {
  CommandLineProcessor processor_error_missing_argument = CommandLineProcessor();
  const char* argv3[] = { "./build/bin/mia", "resources/rose-input.png", "-motionblur-ne-sw", "resources/rose-output.png"};
  int output1 = processor_error_missing_argument.ProcessCommandLine(4, const_cast<char**>(argv3));
  int expected_out1 = -1;
  EXPECT_EQ(output1, expected_out1) << "invalid command of missing argument is not detected";
}

// Test invalid command of typos: mia in.png -sdgedetect out.png
TEST_F(CommandLineProcessorTest, TyposTests) {
  CommandLineProcessor processor_error_typo = CommandLineProcessor();
  const char* argv4[] = { "./build/bin/mia", "resources/rose-input.png", "-sdgedetect", "resources/rose-output.png"};
  int output1 = processor_error_typo.ProcessCommandLine(4, const_cast<char**>(argv4));
  int expected_out1 = -1;
  EXPECT_EQ(output1, expected_out1) << "invalid command of typos is not detected";
}

// Test invalid command of missing output: mia in.png -motionblur-e-w 5.0
TEST_F(CommandLineProcessorTest, MissOutputTests) {
  CommandLineProcessor processor_error_forget_output = CommandLineProcessor();
  const char* argv2[] = {"./build/bin/mia", "resources/rose-input.png", "-motionblur-e-w", "5.0"};
  int output1 = processor_error_forget_output.ProcessCommandLine(4, const_cast<char**>(argv2));
  int expected_out1 = -1;
  EXPECT_EQ(output1, expected_out1) << "invalid command of missing output is not detected";
}

// Test valid command lines of 0 commands: mia in.png out.png
TEST_F(CommandLineProcessorTest, ZeroCommandTests) {
  CommandLineProcessor processor_zero_command = CommandLineProcessor();
  const char* argv5[] = { "./build/bin/mia", "resources/rose-input.png", "resources/rose-output.png"};
  int output1 = processor_zero_command.ProcessCommandLine(3, const_cast<char**>(argv5));
  int expected_out1 = 0;
  EXPECT_EQ(output1, expected_out1) <<  "command lines of 0 commands are not as expected";
}

// Test valid command lines of 1 commands: mia in.png -blur 5.0 out.png
TEST_F(CommandLineProcessorTest, OneCommandTests) {
  CommandLineProcessor processor_one_command = CommandLineProcessor();
  const char* argv6[] = { "./build/bin/mia", "resources/rose-input.png", "-blur", "5.0", "resources/rose-output.png"};
  int output = processor_one_command.ProcessCommandLine(5, const_cast<char**>(argv6));
  int expected_out = 1;
  EXPECT_EQ(output, expected_out) <<  "command lines of 1 command is not as expected";

  std::string output1 = processor_one_command.Command(0)->Name();
  std::string expected_out1 = "blur";
  float output1_radius = processor_one_command.Command(0)->Radius();
  float expected_out1_radius = 5.0;
  EXPECT_EQ(output1, expected_out1) << "command lines of 1 command is not as expected";
  EXPECT_EQ(output1_radius, expected_out1_radius) << "command lines of 1 command is not as expected";
}

// Test valid command lines of 2 commands: mia in.png -edgedetect -sharpen 3.0 out.png
TEST_F(CommandLineProcessorTest, TwoCommandTests) {
  CommandLineProcessor processor_two_commands = CommandLineProcessor();
  const char* argv7[] = { "./build/bin/mia", "resources/rose-input.png", "-edgedetect", "-sharpen", "3.0", "resources/rose-output.png"};
  int output = processor_two_commands.ProcessCommandLine(6, const_cast<char**>(argv7));
  int expected_out = 2;
  EXPECT_EQ(output, expected_out) <<  "command lines of 2 commands are not as expected";

  std::string output1 = processor_two_commands.Command(0)->Name();
  std::string expected_out1 = "edge";
  EXPECT_EQ(output1, expected_out1) << "command lines of 2 commands are not as expected";

  std::string output2 = processor_two_commands.Command(1)->Name();
  std::string expected_out2 = "sharpen";
  float output2_radius = processor_two_commands.Command(1)->Radius();
  float expected_out2_radius = 3.0;
  EXPECT_EQ(output2, expected_out2) << "command lines of 2 commands are not as expected";
  EXPECT_EQ(output2_radius, expected_out2_radius) << "command lines of 2 commands are not as expected";
}
