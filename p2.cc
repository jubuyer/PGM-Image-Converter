//
// <YOUR NAME>
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

// @brief Implementation of sequential labeling algorithm
// @param input_filename the name of the input image
// @param output_filename the name of the output image
void PerformSequentialLabeling(const string &input_filename, const string &output_filename) {
  cout << "Sequential labeling" << endl;
  cout << "Input filename: " << input_filename << endl;
  cout << "Output filename: " << output_filename << endl;
    // .. Code that calls other functions
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
