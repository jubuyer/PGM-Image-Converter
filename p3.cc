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
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;

struct ObjectDesc {
  int object_label = 0;
  int area = 0;
  double rows = 0;
  double cols = 0;
  double row_centr = 0;
  double col_centr = 0;
  double a = 0;
  double b = 0;
  double c = 0;
  double theta = 0;
  int e_min = 0;
  int roundedness = 0;
  int orientation = 0;
};

//returns index of object with current_pixel's label from the objects vector
int FindObject(std::vector<ObjectDesc>& objects, int current_pixel) {
  int length = objects.size();
  int index = -1;

  for(int i = 0; i < length; i++) {
    if(objects[i].object_label == current_pixel)
      index = i;
  }

  return index;
}

// increases num of rows and cols in an object
void incrementObjVals(std::vector<ObjectDesc>& objects, std::set<int>& labels, int current_pixel, int row_coord, int col_coord) {
  int obj_index;
  
  // pixel is part of object
  if(current_pixel > 0) {
    // if current pixel label has already been discovered
    if(labels.find(current_pixel) != labels.end()) {
      // find the object struct with the corresponding label in objects vector
      obj_index = FindObject(objects, current_pixel);
      // add col to the objects row
      objects[obj_index].cols += col_coord;
      objects[obj_index].rows += row_coord;
    }
  }
} 

// increases area of each object with label current_pixel and creates new objects as necessary
void CalculateArea(std::vector<ObjectDesc>& objects, std::set<int>& labels, int current_pixel) {
  int obj_index;

  // pixel is part of object
  if(current_pixel > 0) {
    // if current pixel label has already been discovered
    if(labels.find(current_pixel) != labels.end()) {
      // find the object struct with the corresponding label in objects vector
      obj_index = FindObject(objects, current_pixel);
      // add 1 to the objects area
      objects[obj_index].area += 1;
    } else {
      // add label to set containing discovered labels
      labels.insert(current_pixel);

      // create new object
      ObjectDesc new_object;
      new_object.object_label = current_pixel; // set new label
      new_object.area += 1; // increase area

      // push object into vector
      objects.push_back(new_object);
    }
  }
}

void CalculateMoments(std::vector<ObjectDesc>& objects, std::set<int>& labels, int current_pixel, int row_coord, int col_coord) {

}

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

  std::vector<ObjectDesc> Objects;
  set<int> labels;
  int current_pixel = 0;

  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      current_pixel = input.GetPixel(i, j);
      
      CalculateArea(Objects, labels, current_pixel);

      incrementObjVals(Objects, labels, current_pixel, i, j);
    }
  }

  int length = Objects.size();
  for(int i = 0; i < length; i++) {
    Objects[i].row_centr = Objects[i].rows / Objects[i].area;
    Objects[i].col_centr = Objects[i].cols / Objects[i].area;
  }

  for(int i = 0; i < length; i++) {
    cout << i << " ";
    cout << Objects[i].area << " ";
    cout << Objects[i].row_centr << " ";
    cout << Objects[i].col_centr << endl;
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
