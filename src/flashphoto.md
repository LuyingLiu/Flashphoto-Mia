Getting Started with FlashPhoto    {#flashphoto}
============
This app is like a simplified version of Photoshop. In this app, you can open a
file, save the file, also use tools and filters to modified the current picture.
When Flashphoto is running, there should always be exactly one active tool or
filter.

The open button is easy to use, you can just click it, and a window will
pop up and let you choose the desired file you want to open.

The save button is just like open. You can click it, and a window will
pop up to let you choose the desired directory and the desired file name.
For example, you want to put the file under the folder
liux4093/csci3081/3081_F18/repo-liux4093/PROJ, and name the file with "123.png".
You need to do exactly the same as in the picure.
![picture]
[picture]: @ref open_flashphoto.png "open" width = 10cm

The functions of all the tools and filters are:

Tools:

Pen: This tool is designed to look like a pen.  It makes an opaque, circular
mark with constant intensity.  This means that when the pen is applied to the
canvas the digital ink from the pen completely covers any color that had
previously been applied to the canvas at that position.  The color of the pen
can be set interactively using the GUI.
![picture_pen]
[picture_pen]: @ref pen.png "pen" width = 10cm

Calligraphy Pen: This tool is designed to look like a calligraphy pen.  It works
almost the same way as the Pen tool.  Like the Pen tool, it is completely opaque
and it covers up any “paint” that was already applied to the canvas.  However,
the difference with the Calligraphy Pen is that the mask is an oval tilted at a
30-degree angle.  The color of the highlighter can be set interactively using
the GUI.
![picture_calligraphy]
[picture_calligraphy]: @ref calligraphy.png "calligraphy" width = 10cm

Chalk: This tool is designed to look like a piece of chalk dragged across a
bumpy surface.  It has a circular mask, but about 40% of the pixels within the
circle are randomly chosen to be completely transparent.  This creates the bumpy
effect.  The chalk color can be set interactively using the GUI.
![picture_chalk]
[picture_chalk]: @ref chalk.png "chalk" width = 10cm

Highlighter:  This tool is designed to look like a highlighter marker.  It uses
an oval mask similar to the Calligraphy Pen, but the oval is oriented
vertically, and the intensity of the mask is set to make the mark
semi-transparent.  The color applied to the canvas is approximately 40% the
color of the highlighter and 60% whatever color is already on the canvas;
however, a special color blending function is used for the highlighter so that
dark colors show through more than light colors.  The color of the highlighter’s
ink can be set interactively using the GUI.
![picture_highlighter]
[picture_highlighter]: @ref highlighter.png "highlighter" width = 10cm

Spray Can: This tool is designed to mimic the look of paint from a spray can.  
It uses a special mask that is circular in shape but has a linear falloff to
mimic the dispersion of color from the spray.  The intensity is strongest at the
center pixel and falls off linearly to zero intensity at the edge of the circle.
The specific paint color can be set interactively using the GUI.
![picture_highlighter]
[picture_spray_can]: @ref spray_can.png "spray_can" width = 10cm

Blur: This tool is designed to make the paint blurring.
![picture_blur_pen]
[picture_blur_pen]: @ref blur_pen.png "blur pen" width = 10cm

Eraser: This tool erases the digital canvas and returns it to its original
background color.  It has a circular mask, and eraser’s color cannot be changed
through the GUI because there is currently no user interface for changing the
canvas background color.
![picture_eraser]
[picture_eraser]: @ref eraser.png "eraser" width = 10cm

Filters:

Threshold Filter: Each of the color channels will be rounded up to the maximum
value of 1.0 or down to the minimum value of 0.0 based on whether the pixel’s
value is greater or less than the GLUI input value, respectively.
![picture_threshold]
[picture_threshold]: @ref threshold.png "threshold" width = 10cm

Saturation Filter: Increase or decrease the colorfulness of the image.
![picture_saturation]
[picture_saturation]: @ref saturation.png "saturation" width = 10cm

Channels Filter: Independently scale up or down the intensity of each color
channel (red, green, and blue).
![picture_channels]
[picture_channels]: @ref channels.png "channels" width = 10cm

Quantize Filter: Reduce the number of colors in the image by binning.  If using
4 bins, there will only be 4 possible intensity values for each color channel,
spaced evenly: 0%, 33%, 66%, and 100%.  Adjust each color channel value R, G,
and B to put it into the nearest bin.
![picture_quantize]
[picture_quantize]: @ref quantize.png "quantize" width = 10cm

Blur Filter: Use a Gaussian Blur image convolution kernel to blur the image in
proportion to the amount specified in the GUI.
![picture_motion_blur]
[picture_motion_blur]: @ref motion_blur.png "motion_blur" width = 10cm

Motion Blur Filter: Blur the image by convolving it with an appropriate
motion-blurring kernel.  Support four possible blurring directions
(North-to-South, East-to-West, Northeast-to-Southwest, and Northwest-to-Southeast)
and blur according to the amount specified in the GUI.
![picture_blur]
[picture_blur]: @ref blur.png "blur" width = 10cm

Sharpen Filter: Sharpen the image (accentuate the edges of shapes) in proportion
to the amount specified in the GUI.
![picture_sharpen]
[picture_sharpen]: @ref sharpen.png "sharpen" width = 10cm

Edge Detection Filter: Transform the image into one that only shows the edges of
shapes by convolving it with a 3x3 edge detection kernel. Pixels on the border
of differently colored regions will be bright, while pixels in areas of low
change will be dark.
![picture_edge_detection]
[picture_edge_detection]: @ref edge_detection.png "edge_detection" width = 10cm

Citations:
CSCI 3081W iteration1 handout
