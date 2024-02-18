//
// <YOUR NAME>
// Computational Vision Homework 2
// Program 3
//

#include "image.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

// @brief Compute object properties
// @param input_filename the name of the input labeled image
// @param output_descriptions_filename the name of the output descriptions file (txt)
// @param output_image_filename the name of the output image
void ComputeProperties(const string &input_filename, const string &output_descriptions_filename, const string &output_image_filename) {
  cout << "Compute properties" << endl;
  cout << "Input labeled image filename: " << input_filename << endl;
  cout << "Output descriptions filename: " << output_descriptions_filename << endl;
  cout << "Output image filename: " << output_image_filename << endl;
  // .. Code that calls other functions
}

int main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s input_labeled_image output_descriptions(txt) output_image\n", argv[0]);
    return 0;
  }
  
  const string input_filename(argv[1]);
  const string output_descriptions_filename(argv[2]);
  const string output_image_filename(argv[3]);

  ComputeProperties(input_filename, output_descriptions_filename, output_image_filename);
  
  return 0;
}
