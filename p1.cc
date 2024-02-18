//
// Jubayer Ahmed
// Computational Vision Homework 2
// Program 1
//

#include "image.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;



 // @brief Implementation of Task Program 1 to convert to binary image given a threshold.
 //  
 // @param input_filename the name of the input image
 // @param threshold the threshold value
 // @param output_filename the name of the output image
void ConvertToBinary(const string &input_filename, int threshold, const string &output_filename) {
  cout << "Converting to Binary Image" << endl;
  cout << "Input filename: " << input_filename << endl;
  cout << "Threshold: " << threshold << endl;
  cout << "Output filename: " << output_filename << endl;

   // account for non-existent file - covering edge case of file error
    std::ifstream fin(input_filename);
  	if (fin.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}
}

int main(int argc, char **argv){  
  if (argc!=4) {
    printf("Usage: %s input_file threshold output_file\n", argv[0]);
    return 0;
  }
  
  const string input_filename(argv[1]);
  const int threshold = atoi(argv[2]);
  const string output_filename(argv[3]);

  ConvertToBinary(input_filename, threshold, output_filename);

  return 0;
}
