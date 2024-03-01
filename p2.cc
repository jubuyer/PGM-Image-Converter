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
#include <algorithm>
#include <set>

using namespace std;
using namespace ComputerVisionProjects;

// @brief Implementation of sequential labeling algorithm
// @param input_filename the name of the input image
// @param output_filename the name of the output image
void PerformSequentialLabeling(const string &input_filename, const string &output_filename) {
  cout << "Sequential labeling" << endl;
  cout << "Input filename: " << input_filename << endl;
  cout << "Output filename: " << output_filename << endl;

  Image input;

  ReadImage(input_filename, &input);

  size_t input_rows = input.num_rows();
  size_t input_cols = input.num_columns();
  int pixels = input_rows*input_cols;

  DisjSets EqClasses(pixels);

  int current_label = 1;
  int current_pixel = 0;
  int diagonal_pixel = 0;
  int left_pixel = 0;
  int top_pixel = 0;
  int min_pixel = 0;
  int left_root = 0;
  int top_root = 0;
  // cout << "Current Label: " << current_label << "\n";

  // First Pass - Assigning Labels
  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      current_pixel = input.GetPixel(i, j);

      if(current_pixel > 0) { // pixel not background
        // calc surrounding pixel values
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

        //surrounded by background
        if((diagonal_pixel == 0) && (left_pixel == 0) && (top_pixel == 0)) {
          input.SetPixel(i, j, current_label);
          current_label++;
          // cout << current_label << "\n";
        } else if(diagonal_pixel > 0) {
          //left diagonal isn't background
          input.SetPixel(i, j, diagonal_pixel);
          // cout << "diag\n";
        } else if(diagonal_pixel == 0) {
          if((left_pixel > 0) && (top_pixel == 0)) {
            //left isn't background
            // cout << "left\n";
            input.SetPixel(i, j, left_pixel);
          } else if(((left_pixel == 0) && (top_pixel > 0))) {
            //top isn't background
            // cout << "top\n";
            input.SetPixel(i, j, top_pixel);
          } else if((left_pixel > 0) && (top_pixel > 0)) {
            //top and left aren't background
            // min_pixel = (top_pixel, left_pixel); // calc min gray level
            input.SetPixel(i, j, top_pixel);
            if(left_pixel != top_pixel) {
              left_root = EqClasses.find(left_pixel);
              top_root = EqClasses.find(top_pixel);

              if(top_root != left_root) {
                EqClasses.unionSets(top_root, left_root);
              }
            }
          }
        }
      } else {
        input.SetPixel(i, j, 0);
      }
    }
  }


  set<int> roots;
  // Second Pass - Resolving equivalent pixels
  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      current_pixel = input.GetPixel(i, j);

      min_pixel = EqClasses.find(current_pixel);
      input.SetPixel(i,j, min_pixel);

      roots.insert(min_pixel);
      // cout << "set to: " << min_pixel << "\n";
    }
  }

  // for(auto x: roots) cout << x << endl;

  set<int> colors;
  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      current_pixel = input.GetPixel(i, j);

      colors.insert(current_pixel);
      // cout << "set to: " << min_pixel << "\n";
    }
  }

  // Debugging number of color labels in PGM
  // for(auto x: colors) cout << x << endl;

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
