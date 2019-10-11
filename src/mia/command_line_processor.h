#ifndef FLASHPHOTO_COMMAND_LINE_PROCESSOR_H_
#define FLASHPHOTO_COMMAND_LINE_PROCESSOR_H_

#include <cmath>
#include <string>
#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "imagetools/image_editor_commands.h"

namespace image_tools {
  class CommandLineProcessor {
   public:
    CommandLineProcessor();

    virtual ~CommandLineProcessor();

    void SetCommand(int ID, ImageEditorCommand *ImageEditorCommand);

    void CommandUsed(int ID);

    void ProcessCommandLine(int argc, char *argv[]);

   private:
     ImageEditor *image_editor_;
     ImageEditorCommand* m_ImageEditorCommand_[15];
  };
}  // namespace image_tools

#endif  // FLASHPHOTO_COMMAND_LINE_PROCESSOR_H_
