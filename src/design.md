High-Level Design     {#design}
============
We created our own library (libimagetools.a) to hold all the common code for the
two applications, mia and flashphoto.  Then, we can have the two applications we
build refer to our own libimagetools.  Those two applications (flashphoto and mia)
can each build in a separate directory.

When make all is run in the imagetools directory, a library called
libimagetools.a should be built. Flashphoto can be compiled when you run make
all inside src/flashphoto/ directory. And Mia can be compiled when you run make
all inside src/mia/ directory.

WE have also included a project-level Makefile in the PROJ directory.  Running
make all from the /PROJ directory should go into each subdirectory
(libimagetools.a needs to be compiled before flashphoto and mia) and run make
there so that the whole project can be compiled by scratch by running a single
command.

Here is a summary of the directory structure that we used:

*  Makefile
*  docs/
*  resources/
*  src/imagetools/
   *  Makefile
*  src/flashphoto/
   *  Makefile
*  src/mia/
   *  Makefile
*  src/tests/
   *  Makefile

The UML diagram of the imagetools library is:
![picture1]
[picture1]: @ref pic1.png "picture1" width = 25cm
![picture2]
[picture2]: @ref pic2.png "picture2" width = 25cm
![picture3]
[picture3]: @ref pic3.png "picture3" width = 25cm

Following a MVC paradigm, we implement the flashphoto and mia application. In
the flashphoto app, we created a GUI and the GUI is loosely coupled to the rest
of the program, having no responsibilities other than calling functionality in
the ImageEditor class.

While in the mia app, we have two modes, one graphical mode and the other one is
command line mode. The graphical mode is quite similar to flashphoto, using a
GUI calling functionality in the ImageEditor class. The command line mode uses
Command Pattern to implement the functionality. ImageEditorCommand is the base
command class, BlurFilterCommand, EdgeFilterCommand, SharpenFilterCommand,
ChannelsFilterCommand, QuantizeFilterCommand, SaturateFilterCommand,
ThresholdFilterCommand, MotionBlurFilterCommand are the subclasses of
ImageEditorCommand. Each command knows how to execute itself, including sending
and required parameters to the image editor. The CommandLineProcessor does
command line parsing for mia, and can execute the corresponding commands based
on user input. The usage of the mia is quite straightforward. If you start it
without specifying any command-line option, mia should run in a graphical mode.  
When a command-line argument is specified, mia should run in a command-line mode
where this is no graphical user interface. The usage of the mia is implemented
in the main.cc file under src/mia folder.

Citation:
CSCI 3081W iteration1 handout
CSCI 3081W iteration2 handout
