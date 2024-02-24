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
#include <vector>
#include <set>

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

  Image input;

  ReadImage(input_filename, &input);
  // cout << "Read Image\n";

  size_t input_rows = input.num_rows();
  size_t input_cols = input.num_columns();

  struct ObjectDesc {
    int object_label;
    int area = 0;
    int row_centr;
    int col_centr;
    int e_min;
    int roundedness;
    int orientation;
  };

  std::vector<ObjectDesc> Objects;
  set<int> labels;
  int current_pixel = 0;

  for (int i = 0; i < input_rows; ++i) {
  for (int j = 0; j < input_cols; ++j) {

  }
}

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
