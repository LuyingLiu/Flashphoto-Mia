/*
 This file is part of the CSCI-3081W Project.

 This code is to be used for student coursework.  It is not an open source
 project.
 Copyright (c) 2015-2018 Luying Liu.

 Original Author(s) of this File:
 Luying Liu, 2018, University of Minnesota
 */

#ifndef MIA_COMMAND_LINE_PROCESSOR_H_
#define MIA_COMMAND_LINE_PROCESSOR_H_

#include <cmath>
#include <string>
#include <vector>
#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "mia/image_editor_commands.h"

namespace image_tools {

/** Base class for implementing command line parsing for mia. Each input
 commands can be added to a command queue(named with command_list_), and
 execute the commands if the input commands are valid. This
 structure follows the Command Design Pattern. */

class CommandLineProcessor {
 public:
    CommandLineProcessor();

    virtual ~CommandLineProcessor();

    ImageEditorCommand* Command(int ID);

    /** Function to do command line parsing and executing.  */
    int ProcessCommandLine(int argc, char *argv[]);

 private:
     ImageEditor *image_editor_;
     PixelBuffer *current_buffer_;
     std::vector<ImageEditorCommand*> command_list_;
};
}  // namespace image_tools

#endif  // MIA_COMMAND_LINE_PROCESSOR_H_
