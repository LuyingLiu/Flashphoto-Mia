/*
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/
#include <string.h>

#include "imagetools/filter_channels.h"
#include "imagetools/color_data.h"
#include "mia/command_line_processor.h"

namespace image_tools {

CommandLineProcessor::CommandLineProcessor() {
  current_buffer_ = new PixelBuffer(150, 150, image_tools::ColorData(1, 1, 1));
  image_editor_ = new ImageEditor();
}

CommandLineProcessor::~CommandLineProcessor() {}

ImageEditorCommand* CommandLineProcessor::Command(int ID) {
  return command_list_[ID];
}

int CommandLineProcessor::ProcessCommandLine(int argc, char *argv[]) {
  image_editor_->set_pixel_buffer(current_buffer_);
  int num_command = 0;
  try {
    if (argc < 3) {
      if (strcmp(argv[1], "-h") == 0) {
        std::cout << "usage: mia infile.png [image processing commands ...]"
          << "outfile.png" << std::endl;
        std::cout << "infile.png:\t\tinput image file in png format"
          << std::endl;
        std::cout << "outfile.png:\t\tfilename to use for saving the result"
          << std::endl;
        std::cout << "image processing comamnds:" << std::endl;
        std::cout << "-blur r:\t\tapply a gaussian blur of radius r"
          << std::endl;
        std::cout << "-edgedetect:\t\tapply an edge detection filter"
          << std::endl;
        std::cout << "-sharpen r:\t\tapply a sharpening filter of radius r"
          << std::endl;
        std::cout << "-red s:\t\t\tscale the red channel by factor s"
          << std::endl;
        std::cout << "-green s:\t\tscale the green channel by factor s"
          << std::endl;
        std::cout << "-blue s:\t\tscale the blue channel by factor s"
          << std::endl;
        std::cout << "-quantize n:\t\tquantize each color channel into n bins"
          << std::endl;
        std::cout << "-saturate s:\t\tsaturate colors by scale factor s"
          << std::endl;
        std::cout << "-threshold c:\t\tthreshold using cutoff value c"
          << std::endl;
        std::cout << "-motionblur-n-s r:\tnorth-south motion blur with kernel"
          << "radius r" << std::endl;
        std::cout << "-motionblur-e-w r:\teast-west motion blur with kernel"
          << "radius r" << std::endl;
        std::cout << "-motionblur-ne-sw r:\tne-sw motion blur with kernel"
          << "radius r" << std::endl;
        std::cout << "-motionblur-nw-se r:\tnw-se motion blur with kernel"
          << "radius r" << std::endl;
        return 0;
      } else { throw -1; }
    }
    int i = 1;
    while (i < argc) {
      if (i == 1) {
        int len = strlen(argv[i]);
        const char *last_four;
        if (len <= 4) {
          last_four = NULL;
          throw -1;
        } else {
          last_four = &(argv[i])[len-4];
        }

        if (strcmp(last_four, ".png") == 0) {
          i++;
        } else {
          throw -1;
        }
      } else if (i == (argc-1)) {
        int len = strlen(argv[i]);
        const char *last_four;
        if (len <= 4) {
          last_four = NULL;
          throw -1;
        } else {
          last_four = &(argv[i])[len-4];
        }

        if (strcmp(last_four, ".png") == 0) {
          i++;
        } else {
          throw -1;
        }
      } else {
        if (strcmp(argv[i], "-blur") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float radius = atof(argv[i+1]);
          BlurFilterCommand *blur = new BlurFilterCommand(image_editor_,
            radius);
          command_list_.push_back(blur);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-edgedetect") == 0) {
          EdgeFilterCommand *edge = new EdgeFilterCommand(image_editor_);
          command_list_.push_back(edge);
          num_command++;
          i++;
        } else if (strcmp(argv[i], "-sharpen") == 0) {
          float radius = atof(argv[i+1]);
          SharpenFilterCommand *sharpen = new SharpenFilterCommand(
            image_editor_, radius);
          command_list_.push_back(sharpen);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-red") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float r = atof(argv[i+1]);
          ChannelsFilterCommand *red = new ChannelsFilterCommand(
            image_editor_, r, 1.0, 1.0);
          command_list_.push_back(red);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-green") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float g = atof(argv[i+1]);
          ChannelsFilterCommand *green = new ChannelsFilterCommand(
            image_editor_, 1.0, g, 1.0);
          command_list_.push_back(green);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-blue") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float b = atof(argv[i+1]);
          ChannelsFilterCommand *blue = new ChannelsFilterCommand(
            image_editor_, 1.0, 1.0, b);
          command_list_.push_back(blue);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-quantize") == 0) {
          if ((i+1) >= argc || atoi(argv[i+1]) <= 0) { throw -1; }
          int quan = atoi(argv[i+1]);
          QuantizeFilterCommand *quantize = new QuantizeFilterCommand(
            image_editor_, quan);
          command_list_.push_back(quantize);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-saturate") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float scale = atof(argv[i+1]);
          SaturateFilterCommand *saturate = new SaturateFilterCommand(
            image_editor_, scale);
          command_list_.push_back(saturate);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-threshold") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float cutoff = atof(argv[i+1]);
          ThresholdFilterCommand *threshold = new ThresholdFilterCommand(
            image_editor_, cutoff);
          command_list_.push_back(threshold);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-motionblur-n-s") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float radius = atof(argv[i+1]);
          MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(
            image_editor_, radius,
                                MBLUR_DIR_N_S);
          command_list_.push_back(motionblur);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-motionblur-e-w") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float radius = atof(argv[i+1]);
          MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(
            image_editor_, radius,
                                MBLUR_DIR_E_W);
          command_list_.push_back(motionblur);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-motionblur-ne-sw") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float radius = atof(argv[i+1]);
          MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(
            image_editor_, radius,
                                MBLUR_DIR_NE_SW);
          command_list_.push_back(motionblur);
          num_command++;
          i += 2;
        } else if (strcmp(argv[i], "-motionblur-nw-se") == 0) {
          if ((i+1) >= argc || atof(argv[i+1]) <= 0.0) { throw -1; }
          float radius = atof(argv[i+1]);
          MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(
            image_editor_, radius,
                                MBLUR_DIR_NW_SE);
          command_list_.push_back(motionblur);
          num_command++;
          i += 2;
        } else {
          throw -1;
        }
      }
    }

    i = argc - 1;
    int len = strlen(argv[i]);
    const char *last_four;
    if (len <= 4) {
      last_four = NULL;
      throw -1;
    } else {
      last_four = &(argv[i])[len-4];
    }

    if (strcmp(last_four, ".png") != 0) {
      throw -1;
    }
  }
  catch (int i) {
    std::cout << "usage: mia infile.png [image processing commands ...]"
      << "outfile.png" << std::endl;
    std::cout << "infile.png:\t\tinput image file in png format"
      << std::endl;
    std::cout << "outfile.png:\t\tfilename to use for saving the result"
      << std::endl;
    std::cout << "image processing comamnds:" << std::endl;
    std::cout << "-blur r:\t\tapply a gaussian blur of radius r"
      << std::endl;
    std::cout << "-edgedetect:\t\tapply an edge detection filter"
      << std::endl;
    std::cout << "-sharpen r:\t\tapply a sharpening filter of radius r"
      << std::endl;
    std::cout << "-red s:\t\t\tscale the red channel by factor s"
      << std::endl;
    std::cout << "-green s:\t\tscale the green channel by factor s"
      << std::endl;
    std::cout << "-blue s:\t\tscale the blue channel by factor s"
      << std::endl;
    std::cout << "-quantize n:\t\tquantize each color channel into n bins"
      << std::endl;
    std::cout << "-saturate s:\t\tsaturate colors by scale factor s"
      << std::endl;
    std::cout << "-threshold c:\t\tthreshold using cutoff value c"
      << std::endl;
    std::cout << "-motionblur-n-s r:\tnorth-south motion blur with kernel"
      << "radius r" << std::endl;
    std::cout << "-motionblur-e-w r:\teast-west motion blur with kernel"
      << "radius r" << std::endl;
    std::cout << "-motionblur-ne-sw r:\tne-sw motion blur with kernel"
      << "radius r" << std::endl;
    std::cout << "-motionblur-nw-se r:\tnw-se motion blur with kernel"
      << "radius r" << std::endl;
    return -1;
  }

  ImageEditorCommand *load = new LoadCommand(image_editor_, argv[1]);
  load->Execute();

  for (int j = 0; j < num_command; j++) {
    command_list_[j]->Execute();
  }

  ImageEditorCommand *save = new SaveCommand(image_editor_, argv[argc - 1]);
  save->Execute();
  return num_command;
}

}  // namespace image_tools
