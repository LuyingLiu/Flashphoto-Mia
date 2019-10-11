/**
This code is a part of student coursework.  It is not an open source
project.
Copyright (c) 2018 Luying Liu of the University of Minnesota.
*/
#include <string.h>

#include "imagetools/filter_channels.h"
#include "imagetools/color_data.h"
#include "imagetools/command_line_processor.h"

namespace image_tools {

void CommandLineProcessor::SetCommand(int ID, ImageEditorCommand *ImageEditorCommand){
  m_ImageEditorCommand_[ID] = ImageEditorCommand;
}

void CommandLineProcessor::CommandUsed(int ID){
  m_ImageEditorCommand_[ID]->Execute();
}

void CommandLineProcessor::ProcessCommandLine(int argc, char *argv[]){
  if (argc < 3){
    printf("usage: mia infile.png [image processing commands ...] outfile.png");
    return;
  }
  int i = 1;
  int num_command = 0;
  while (i < argc){
    int len = strlen(argv[i]);
    const char *last_four = &(argv[i])[len-4];
    if (strcmp(last_four, ".png") == 0){
      if (i == 1){
        std::string str(argv[i]);
        LoadCommand *load = new LoadCommand(image_editor_, str);
        SetCommand(num_command, load);
        num_command ++;
        i++;
      } else if (i == (argc-1)){
        std::string str(argv[i]);
        SaveCommand *save = new SaveCommand(image_editor_, str);
        SetCommand(num_command, save);
        num_command ++;
        i++;
      } else{
        printf("usage: mia infile.png [image processing commands ...] outfile.png");
        return;
      }
    } else {
      if(strcmp(argv[i], "-blur") == 0){
        float radius = atof (argv[i+1]);
        BlurFilterCommand *blur = new BlurFilterCommand(image_editor_, radius);
        SetCommand(num_command, blur);
        num_command ++;
        i += 2;
      } else if(strcmp(argv[i], "-edgedetect") == 0){
        EdgeFilterCommand *edge = new EdgeFilterCommand(image_editor_);
        SetCommand(num_command, edge);
        num_command ++;
        i++;
      } else if(strcmp(argv[i], "-sharpen") == 0){
        float radius = atof (argv[i+1]);
        SharpenFilterCommand *sharpen = new SharpenFilterCommand(image_editor_, radius);
        SetCommand(num_command, sharpen);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-red") == 0){
        float r = atof (argv[i+1]);
        ChannelsFilterCommand *red = new ChannelsFilterCommand(image_editor_, r, 1.0, 1.0);
        SetCommand(num_command, red);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-green") == 0){
        float g = atof (argv[i+1]);
        ChannelsFilterCommand *green = new ChannelsFilterCommand(image_editor_, 1.0, g, 1.0);
        SetCommand(num_command, green);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-blue") == 0){
        float b = atof (argv[i+1]);
        ChannelsFilterCommand *blue = new ChannelsFilterCommand(image_editor_, 1.0, 1.0, b);
        SetCommand(num_command, blue);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-quantize") == 0){
        int quan = atoi (argv[i+1]);
        QuantizeFilterCommand *quantize = new QuantizeFilterCommand(image_editor_, quan);
        SetCommand(num_command, quantize);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-saturate") == 0){
        float scale = atof (argv[i+1]);
        SaturateFilterCommand *saturate = new SaturateFilterCommand(image_editor_, scale);
        SetCommand(num_command, saturate);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-threshold") == 0){
        float cutoff = atof (argv[i+1]);
        ThresholdFilterCommand *threshold = new ThresholdFilterCommand(image_editor_, cutoff);
        SetCommand(num_command, threshold);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-motionblur-n-s") == 0){
        float radius = atof (argv[i+1]);
        MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(image_editor_, radius,
                                MBLUR_DIR_N_S);
        SetCommand(num_command, motionblur);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-motionblur-e-w") == 0){
        float radius = atof (argv[i+1]);
        MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(image_editor_, radius,
                                MBLUR_DIR_E_W);
        SetCommand(num_command, motionblur);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-motionblur-ne-sw") == 0){
        float radius = atof (argv[i+1]);
        MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(image_editor_, radius,
                                MBLUR_DIR_NE_SW);
        SetCommand(num_command, motionblur);
        num_command ++;
        i += 2;
      } else if (strcmp(argv[i], "-motionblur-nw-se") == 0){
        float radius = atof (argv[i+1]);
        MotionBlurFilterCommand *motionblur = new MotionBlurFilterCommand(image_editor_, radius,
                                MBLUR_DIR_NW_SE);
        SetCommand(num_command, motionblur);
        num_command ++;
        i += 2;
      } else {
        printf("usage: mia infile.png [image processing commands ...] outfile.png");
        return;
      }
    }
  }
  for (int j = 0; j < num_command; j++){
    CommandUsed(j);
  }
}

} // namespace image_tools
