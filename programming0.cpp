#include <iostream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main() {  
    // 500x500 - 3 color channels (RGB)
    CImg<unsigned char> img(500, 500, 1, 3, 0);

    // Set corner colors using direct pixel access
    // Top left corner
    img(0, 0, 0, 0) = 0;      // Red channel
    img(0, 0, 0, 1) = 255;   // Green channel
    img(0, 0, 0, 2) = 0;    // Blue channel

    // Top right corner
    img(img.width()-1, 0, 0, 0) = 255;    // Red channel
    img(img.width()-1, 0, 0, 1) = 0;     // Green channel
    img(img.width()-1, 0, 0, 2) = 0;    // Blue channel

    // Bottom left corner
    img(0, img.height()-1, 0, 0) = 128;    // Red channel
    img(0, img.height()-1, 0, 1) = 0;     // Green channel
    img(0, img.height()-1, 0, 2) = 128;  // Blue channel

    // Bottom right corner
    img(img.width()-1, img.height()-1, 0, 0) = 0;    // Red channel
    img(img.width()-1, img.height()-1, 0, 1) = 0;     // Green channel
    img(img.width()-1, img.height()-1, 0, 2) = 255;  // Blue channel

    // Interpolate across top and bottom rows 
    for (float x = 0; x < img.width(); ++x) {
        // Calculate the horizontal interpolation factor (0 to 1)
        float horizontalFactor = x / (img.width() - 1.0f);
        // Interpolate between top left and top right
        for (int color = 0; color < 3; ++color) {
            img(x, 0, 0, color) = (unsigned char)((1 - horizontalFactor) * img(0, 0, 0, color) + horizontalFactor * img(img.width()-1, 0, 0, color));
            img(x, img.height()-1, 0, color) = (unsigned char)((1 - horizontalFactor) * img(0, img.height()-1, 0, color) + horizontalFactor * img(img.width()-1, img.height()-1, 0, color));
        }
    }

    // Interpolate down the columns 
    for (int x = 0; x < img.width(); ++x) {
        for (int y = 1; y < img.height() - 1; ++y) { // Skip first and last rows -- like the sheet
            float verticalFactor = y / (img.height() - 1.0f);
            for (int color = 0; color < 3; ++color) {
                // Interpolate between top and bottom rows for each column
                img(x, y, 0, color) = (unsigned char)((1 - verticalFactor) * img(x, 0, 0, color) + verticalFactor * img(x, img.height()-1, 0, color));
            }
        }
    }

    // Display the image
    CImgDisplay disp(img, "Interpolated Image");
    while (!disp.is_closed()) {
        disp.wait();
    }

    // Save the interpolated image
    img.save("interpolated_image.bmp");

    return 0;
}


/*

I had to look up a couple of youtube vvideos for this assignment. Links:
- https://www.youtube.com/watch?v=0XAE9Q9jfBY

Here’s an explanation of how I approached coding:
- CImg library for image creation
- 'iostream` library is included for input/output 

   ```cpp
   CImg<unsigned char> img(500, 500, 1, 3, 0);
   ```
- `500x500` -- specifies the image dimensions (w * h)
- `1` -- allows for single slice (or plane) since it's a 2D image.
- `3` --  3 channels (RGB)
- `0` -- initial value for each pixel is set to zero (black and 255 is white)

- Two nested loops to go through each pixel of the image, x-coordinate(columns) and y-coordinate{rows).
- Outer loop iterates over the x-axis and inner loop iterates over the y-axis.
- Horizontal Interpolation -- interpolate between the left and right corners based on the x-position of the pixel. For example, for each row, the color smoothly transitions from red to purple at the top, and from green to aqua at the bottom.
- Vertical Interpolation -- interpolate vertically based on the y-position of the pixel. This smooths the transition between the top (red to purple) and bottom (green to aqua) rows.



                                                       -- I originally hard coded values before I realized you gave us started code --


    // Set corner colors
    unsigned char topLeft[] = {255, 0, 0};         // Red
    unsigned char topRight[] = {128, 0, 128};     // Purple
    unsigned char bottomLeft[] = {0, 255, 0};    // Green
    unsigned char bottomRight[] = {0, 255, 255};// Aqua

    // Loop through each pixel of the image
    for (int x = 0; x < 500; ++x) {
        for (int y = 0; y < 500; ++y) {

            // Calculate horizontal and vertical interpolation factors (0 to 1)
            float horizontalFactor = x / 499.0f;  // Ranges from 0 at the left to 1 at the right
            float verticalFactor = y / 499.0f;   // Ranges from 0 at the top to 1 at the bottom

            // Linear interpolate between the four corner colors
            for (int color = 0; color < 3; ++color) {
                // Interpolating between top-left and top-right (horizontally)
                float topColor = (1 - horizontalFactor) * topLeft[color] + horizontalFactor * topRight[color];
                // Interpolating between bottom-left and bottom-right (horizontally)
                float bottomColor = (1 - horizontalFactor) * bottomLeft[color] + horizontalFactor * bottomRight[color];
                // Now interpolate between the top and bottom (vertically)
                img(x, y, 0, color) = (unsigned char)((1 - verticalFactor) * topColor + verticalFactor * bottomColor);
            }
        }
    }

   
*/
