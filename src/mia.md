Getting Started with Mia     {#mia}
============
This app is like a simplified version of Photoshop. In this app, you can open a
file, save the file, also use tools and filters to modified the current picture.
When Flashphoto is running, there should always be exactly one active tool or
filter. Also, there is a command line mode of mia which you can make cahnges to
a .png picture.

In the GUI mode:

The open button is easy to use, you can just click it, and a window will
pop up and let you choose the desired file you want to open.

The save button is just like open. You can click it, and a window will
pop up to let you choose the desired directory and the desired file name.
For example, you want to put the file under the folder
liux4093/csci3081/3081_F18/repo-liux4093/PROJ, and name the file with "123.png".
You need to do exactly the same as in the picture.
![picture]
[picture]: @ref open_mia.png "open" width = 10cm

The functions of all the tools and filters are:

Tools:

Pen: This tool is designed to look like a pen.  It makes an opaque, circular
mark with constant intensity.  This means that when the pen is applied to the
canvas the digital ink from the pen completely covers any color that had
previously been applied to the canvas at that position.  The color of the pen
can be set interactively using the GUI.
![picture_pen]
[picture_pen]: @ref pen.png "pen" width = 10cm

Stamp: This tool is is hardcoded to stamp a bullseye pattern, one circle inside
another, that clinicians can use to mark important areas on the image.
![picture_stamp]
[picture_stamp]: @ref stamp.png "stamp" width = 10cm

Filters:

Blur Filter: Use a Gaussian Blur image convolution kernel to blur the image in
proportion to the amount specified in the GUI.
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

Threshold Filter: Each of the color channels will be rounded up to the maximum
value of 1.0 or down to the minimum value of 0.0 based on whether the pixel’s
value is greater or less than the GLUI input value, respectively.
![picture_threshold]
[picture_threshold]: @ref threshold.png "threshold" width = 10cm

Quantize Filter: Reduce the number of colors in the image by binning.  If using
4 bins, there will only be 4 possible intensity values for each color channel,
spaced evenly: 0%, 33%, 66%, and 100%.  Adjust each color channel value R, G,
and B to put it into the nearest bin.
![picture_quantize]
[picture_quantize]: @ref quantize.png "quantize" width = 10cm

In the command line mode:
You can only apply filters to the desired files.

If you want to display a help message for a –h argument or any set of invalid
arguments. Use some commands like this:
    * mia –h
    * mia <any invalid arguments>

If you want to load an image specified by the first filename and save it out to
the second filename.  With no other arguments specified, this is equivalent to
copying the image file.
    * mia in.png out.png

If you want to run an image processing command before saving out the new file.  
For example, to sharpen an image using a kernel of radius 5 and save the output
to a new image:
    * mia in.png –sharpen 5 out.png

If you want to run multiple image processing commands in order.  For example,
sharpen an image by amount 5, then run an edge detection filter, then save the
output to a new image:
    * mia in.png –sharpen 5 –edgedetect out.png

The full command lists are:
    * -blur r:             apply a gaussian blur of radius r
    * -edgedetect:         apply an edge detection filter
    * -sharpen r:          apply a sharpening filter of radius r
    * -red s:              scale the red channel by factor s
    * -green s:            scale the green channel by factor s
    * -blue s:             scale the blue channel by factor s
    * -quantize n:         quantize each color channel into n bins
    * -saturate s:         saturate colors by scale factor s
    * -threshold c:        threshold using cutoff value c
    * -motionblur-n-s r:   north-south motion blur with kernel radius r
    * -motionblur-e-w r:   east-west motion blur with kernel radius r
    * -motionblur-ne-sw r: ne-sw motion blur with kernel radius r
    * -motionblur-nw-se r: nw-se motion blur with kernel radius r

Citations:
CSCI 3081W iteration2 handout
