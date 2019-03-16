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

#include "mia/command_line_processor.h"
#include "mia/mia_app.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    // command line mode
    image_tools::CommandLineProcessor cmd_processor;
    cmd_processor.ProcessCommandLine(argc, argv);
  } else {
    // gui mode
    image_tools::MiaApp gui(1280, 720, image_tools::ColorData(1, 1, 1));
    // Run returns when the user closes the graphics window.
    gui.Run();
  }
}
