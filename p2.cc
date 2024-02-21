//
// Jubayer Ahmed
// Computational Vision Homework 2
// Program 2
//

#include "image.h"
#include "DisjSets.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

void PixelLabeler(Image input, size_t row, size_t col, int& current_pixel_label) {
  if(input.GetPixel(row, col) != 0) {
    if(row-1 < 0) { // in first row
      if(col-1 > 0) { // not in first column
        //Labeling pixels in first row
        if(input.GetPixel(row, col) != 0) { // not background pixel
          if(input.GetPixel(row, col-1) == 0) { //if left pixel is background set new label
            input.SetPixel(row,col, current_pixel_label); 
            current_pixel_label-=5; 
            cout << current_pixel_label << "\n";
          } else if (input.GetPixel(row, col-1) != 0) { // if left pixel is labeled, relabel current pixel
            input.SetPixel(row,col, input.GetPixel(row, col-1)); 
          }
        }
      } else { // in first row, first column (first pixel)
        //Labeling first pixel
        if(input.GetPixel(row, col) != 0) { // not background pixel
          input.SetPixel(row,col, current_pixel_label);
          current_pixel_label-=5; 
          cout << current_pixel_label << "\n";
        }
      }
    } else if (row-1 > 0) { // not in first row
      if(col-1 > 0) { // not in first column
        if(input.GetPixel(row, col) != 0) { // not background pixel
          if(input.GetPixel(row-1, col-1) != 0) { //check diagonally adjacent cell
            input.SetPixel(row,col, input.GetPixel(row-1, col-1)); 
          } else if (input.GetPixel(row, col-1) != 0 && input.GetPixel(row-1, col) != 0) { // check double edge case
            input.SetPixel(row,col, input.GetPixel(row, col-1)); 
          } else if (input.GetPixel(row, col-1) != 0 && input.GetPixel(row-1, col) == 0) { // check left cell
            input.SetPixel(row,col, input.GetPixel(row, col-1)); 
          } else if (input.GetPixel(row, col-1) == 0 && input.GetPixel(row-1, col) != 0) { // check top cell
            input.SetPixel(row,col, input.GetPixel(row-1, col)); 
          } else {
            input.SetPixel(row,col, current_pixel_label);
            current_pixel_label-=5; 
            cout << current_pixel_label << "\n";
          }
        }
      } else { // in first column
      //Labeling pixels in first col (not including first pixel)
      if(input.GetPixel(row, col) != 0) {
        if(input.GetPixel(row-1, col) == 0) { // check top pixel
          input.SetPixel(row,col, current_pixel_label);
          current_pixel_label-=5; 
          cout << current_pixel_label << "\n";
        } else if (input.GetPixel(row, col-1) != 0) {
          input.SetPixel(row,col, input.GetPixel(row-1, col)); 
          }
        }
      }
    }
  }
}

// @brief Implementation of sequential labeling algorithm
// @param input_filename the name of the input image
// @param output_filename the name of the output image
void PerformSequentialLabeling(const string &input_filename, const string &output_filename) {
  cout << "Sequential labeling" << endl;
  cout << "Input filename: " << input_filename << endl;
  cout << "Output filename: " << output_filename << endl;

  Image input;

  ReadImage(input_filename, &input);
  cout << "Read Image\n";

  size_t input_rows = input.num_rows();
  size_t input_cols = input.num_columns();
  int current_label = 255;
  cout << "Current Label: " << current_label << "\n";

  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      PixelLabeler(input, i, j, current_label);
      cout << "Current Pixel: (" << i << ", " << j << ") | ";
      cout << "Label: " << current_label << "\n";
    }
  }

}

int main(int argc, char **argv){
  
  if (argc!=3) {
    printf("Usage: %s input_file output_file\n", argv[0]);
    return 0;
  }
  
  const string input_filename(argv[1]);
  const string output_filename(argv[2]);

  PerformSequentialLabeling(input_filename, output_filename);
  
  return 0;
}
