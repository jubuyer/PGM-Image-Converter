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

int PixelLabeler(Image input, size_t row, size_t col, int& current_pixel_label) {
  // if(row-1 < 0) { // in first row
  //   if(col-1 > 0) { // not in first column
  //     //Labeling pixels in first row
  //     // not background pixel
  //     if(input.GetPixel(row, col-1) == 0) { //if left pixel is background set new label
  //       input.SetPixel(row,col, current_pixel_label); 
  //       current_pixel_label-=1; 
  //       cout << "r1: " << current_pixel_label << "\n";
  //     } else { // if left pixel is labeled, relabel current pixel
  //       input.SetPixel(row,col, input.GetPixel(row, col-1)); 
  //     }
  //   } else { // in first row, first column (first pixel)
  //     //Labeling first pixel
  //     // not background pixel
  //     input.SetPixel(row,col, current_pixel_label);
  //     current_pixel_label-=1; 
  //     cout <<  "pix1: " << current_pixel_label << "\n";
  //   }
  // } 

  // if(row-1 > 0) { // not in first row
  //   if (col-1 < 0) { // in first column
  //   //Labeling pixels in first col (not including first pixel)  
  //     if(input.GetPixel(row-1, col) == 0) { // check top pixel
  //       input.SetPixel(row,col, current_pixel_label);
  //       current_pixel_label-=1; 
  //       cout <<  "c1: " << current_pixel_label << "\n";
  //     } else {
  //       input.SetPixel(row,col, input.GetPixel(row-1, col)); 
  //     }
  //   } else if ((input.GetPixel(row-1, col-1) == 0) && (input.GetPixel(row, col-1) == 0) && (input.GetPixel(row-1, col) == 0)) { // not in first column and not background pixel
  //     if(input.GetPixel(row-1, col-1) > 0) { //check diagonally adjacent cell
  //       input.SetPixel(row,col, input.GetPixel(row-1, col-1)); 
  //     } else if (input.GetPixel(row, col-1) > 0) { // check left cell
  //       input.SetPixel(row,col, input.GetPixel(row, col-1)); 
  //     } else if (input.GetPixel(row-1, col) > 0) { // check top cell
  //       input.SetPixel(row,col, input.GetPixel(row-1, col)); 
  //     } else if ((input.GetPixel(row, col-1) > 0) && (input.GetPixel(row-1, col) > 0)) { // check double edge case
  //       input.SetPixel(row,col, input.GetPixel(row, col-1)); 
  //     } 
  //   } else {
  //       input.SetPixel(row,col, current_pixel_label);
  //       current_pixel_label-=1; 
  //       cout << row << ", " << col << ": " << current_pixel_label << "\n";
  //     }
  // }

  return current_pixel_label;
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
  // cout << "Read Image\n";

  size_t input_rows = input.num_rows();
  size_t input_cols = input.num_columns();

  int current_label = 255;
  int current_pixel = 0;
  int diagonal_pixel = 0;
  int left_pixel = 0;
  int top_pixel = 0;
  // cout << "Current Label: " << current_label << "\n";

  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      current_pixel = input.GetPixel(i, j);

      if((i-1) > 0) {
        top_pixel = input.GetPixel(i-1, j); // not in first row
      } else {
        top_pixel = 0; //in first row
      }

      if((j-1) > 0) {
        left_pixel = input.GetPixel(i, j-1); //not in first column
      } else {
        left_pixel = 0; // in first column
      }

      if(((i-1) > 0) && ((j-1) > 0)) {
        diagonal_pixel = input.GetPixel(i-1, j-1); // not first pixel
      } else {
        diagonal_pixel = 0; // first pixel
      }

      if(current_pixel > 0) { // pixel not background
        //surrounded by background
        if((diagonal_pixel == 0) && (left_pixel == 0) && (top_pixel == 0)) {
          input.SetPixel(i, j, current_label);
          current_label-=1;
          cout << current_label << "\n";
        } else if(diagonal_pixel > 0) {
          //left diagonal isn't background
          input.SetPixel(i, j, diagonal_pixel);
        } else if (diagonal_pixel == 0) {
          //top and left aren't background
          if((left_pixel > 0) && (top_pixel > 0)) {
            input.SetPixel(i, j, top_pixel);
            input.SetPixel(i, j-1, top_pixel);
          } else if(left_pixel > 0) {
            //left isn't background
            input.SetPixel(i, j, left_pixel);
          } else if(top_pixel > 0) {
            //top isn't background
            input.SetPixel(i, j, top_pixel);
          }
        }
      } else {
        input.SetPixel(i, j, 0);
      }
    }
  }

  WriteImage(output_filename, input);
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
