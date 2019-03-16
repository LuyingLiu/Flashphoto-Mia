Common Tasks    {#tasks}
============
If you want to add a new filter to the program, you will first need to determine
whether it is a filter in-place or a convolution filter. A filter in place means
that it only need the ColorData of a single pixel, and it can only change the
ColorData of this pixel. In this case, our Filter class already implements the
ApplyToFilter() function, which applies the filter to the image, and return a
new image. A convolution filter means a filter whose new color for a
pixel depends not only upon the original color of that
pixel but also upon the original colors of its neighbors. In this situation, the
ConvolutionFilter class implements the ApplyToFilter() function. It saves a copy of the original
colors before modifying the image. And it loops through the image to apply the filter.
In both cases, you do not need to worry about how to apply the filter to the image.


*  Here are the steps to add a in-place filter:

1. Decide the algorithm you want to apply to a single pixel. You need to have a
class, say FilterExample, which is a subclass of Filter. The codes for
`filter_example.h` are like this:

    #ifndef IMAGETOOLS_FILTER_EXAMPLE_H_
    #define IMAGETOOLS_FILTER_EXAMPLE_H_

    #include <cmath>
    #include <string>
    #include "imagetools/color_data.h"
    #include "imagetools/filter.h"

    namespace image_tools {

    class FilterExample : public Filter {
     public:
      FilterExample();
      explicit FilterExample(...);
      virtual ~FilterExample();
      ... // declare the getter and setter functions of the class member variables,
      ... // override the CalculateFilteredPixel() function in the header file.

    private:
      ... // class member variables
    };

    }

    #endif

2. For the `filter_example.cc` file, what you need to do is to implement the getter
and setter functions and also the `CalculateFilteredPixel()` function. In the
`ColorData CalculateFilteredPixel(PixelBuffer *buffer, int x, int y)`,
you can get the color of the pixel in the image of `buffer`, with
the index of `(x, y)` using `ColorData color = buffer->pixel(x, y);`. And get
get the RGB data by:

    float red = color.red();
    float green = color.green();
    float blue = color.blue();
    float alpha = color.alpha();

Then you can manipulate with those values and get the new values for `red`, `green`,
`blue` and `alpha`. Then return the new color by:

    ColorData new_color = ColorData(new_red, new_green, new_blue);
    return new_color;
or
    ColorData new_color = ColorData(new_red, new_green, new_alpha);
    return new_color;


*  Here are the steps to add a convolution filter:

1. Decide the algorithm you want to apply to a pixel. You need to have a
class, say ConvolutionFilterExample, which is a subclass of ConvolutionFilter. The codes for
`filter_convolution_example.h` are like this:

    #ifndef IMAGETOOLS_FILTER_CONVOLUTION_EXAMPLE_H_
    #define IMAGETOOLS_FILTER_CONVOLUTION_EXAMPLE_H_

    #include <cmath>
    #include <string>
    #include "imagetools/filter.h"
    #include "imagetools/filter_convolution.h"
    #include "imagetools/color_data.h"
    #include "imagetools/float_matrix.h"
    #include "imagetools/pixel_buffer.h"

    namespace image_tools {

    class ConvolutionFilterExample : public ConvolutionFilter {
     public:
      ConvolutionFilterExample();
      explicit ConvolutionFilterExample(...);
      virtual ~ConvolutionFilterExample();

      ... // declare the getter and setter functions of the class member variables,
      ... // override the CreateKernel() function in the header file.

    private:
      ... // class member variables
    };

    }

    #endif

2. For the `filter_convolution_example.cc` file, what you need to do is to
implement the getter and setter functions and also the `CreateKernel()`
function. In the `FloatMatrix* CreateKernel()`,
you can decide how you want to design the kernel. A kernel is a float matrix which
will be applied to each pixels and its corresponding neighbors. For a kernel with
size kernel_size, it is applied as this:

    for (int filterY = 0; filterY < kernel_size; filterY++) {
      for (int filterX = 0; filterX < kernel_size; filterX++) {
        int pixelX = (x - kernel_size/ 2 + filterX + w) % w;
        int pixelY = (y - kernel_size/ 2 + filterY + h) % h;
        red += buffer->pixel(pixelX, pixelY).red() *
          kernel_->value(filterX, filterY);
        green += buffer->pixel(pixelX, pixelY).green() *
          kernel_->value(filterX, filterY);
        blue += buffer->pixel(pixelX, pixelY).blue() *
          kernel_->value(filterX, filterY);
      }
    }

The `red`, `green`, and `blue` are the corresponding values in the `ColorData`.

When you set the values of a kernel, you can use codes like this:

    for (int j = 0; j < kernel->height(); j++) {
      for (int i = 0; i < kernel->width(); i++) {
        int x = i - kernel->width() / 2;
        int y = j - kernel->height() / 2;
        ... // get the value for index (i, j) in the matrix
        kernel->set_value(i, j, value);
      }
    }

After all the operations, a kernel will return using:

    return kernel;


*  If you want to add the filer to the mia command line mode, you need to do the following:

1. Create a filter command, say ExampleFilterCommand,  which is a subclass of
ImageEditorCommand. YOu should
add the class declaration to the `mia/image_editor_commands.h` file, using this:

    class BlurFilterCommand : public ImageEditorCommand {
     public:
      BlurFilterCommand(...);
      virtual ~BlurFilterCommand();
      std::string Name() override;
      ... // getter of class member variables
      void Execute() override;

     private:
      ... // class member variables
    };

2. Implement the functions in the `mia/image_editor_commands.cc` file.

3. Add the necessary command syntax to the `usage`, and add a if statement like
this to parse the mia command line:

    else if (strcmp(argv[i], ...) == 0) {
          if ((i+1) >= argc || ...) { throw -1; } // Check for the necessary values
          ... // Get the necessary values
          ExampleFilterCommand ... = new ChannelsFilterCommand(...);
          command_list_.push_back(...);
          num_command++;
          i += ...;
    }


*  If you want to add the filer, say ExampleFilter, to one of the GUIs, say mia, you need to do the following:

1. Add a `void ApplyExampleFilter(...);` declaration to the public area of `mia/mia_app.h` file.

2. Add a `FilterExample f_example_;` declaration and necessary class member variables to the private area of `mia/mia_app.h` file.

3. Initialize the class member variables you added in `MiaApp::MiaApp()` function of `mia/mia_app.cc` file.

4. Implement the `ApplyExampleFilter()` function in the `mia/mia_app.cc` file, using codes like this:

    void MiaApp::ApplyExampleFilter(...) {
      image_editor_.ApplyExampleFilter(...);
    }

Citation:
CSCI 3081W iteration1 handout
CSCI 3081W iteration2 handout
