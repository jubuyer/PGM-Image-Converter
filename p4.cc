//
// Jubayer Ahmed
// Computational Vision Homework 2
// Program 4 (Extra Credit)
//

#include "image.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace ComputerVisionProjects;

struct ObjectDesc {
  int object_label = 0;
  int area = 0;
  double rows = 0;
  double cols = 0;
  double row_centr = 0;
  double col_centr = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  double theta = 0;
  double theta2 = 0;
  double e_min = 0;
  double e_max = 0;
  double roundedness = 0;
  double orientation = 0;
};

//returns index of object with current_pixel's label from the objects vector
// @brief 
// @param 
// @param s
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
// @brief 
// @param 
// @param 
// @param 
// @param 
// @param 
void incrementObjVals(std::vector<ObjectDesc>& objects, std::set<int>& labels, int current_pixel, int row_coord, int col_coord) {
  int obj_index;
  
  // pixel is part of object
  if(current_pixel > 0) {
    // if current pixel label has already been discovered
    if(labels.find(current_pixel) != labels.end()) {
      // find the object struct with the corresponding label in objects vector
      obj_index = FindObject(objects, current_pixel);
      // add row and col coords to the objects row
      objects[obj_index].rows += row_coord;
      objects[obj_index].cols += col_coord;
    }
  }
} 

// increases area of each object with label current_pixel and creates new objects as necessary
// @brief 
// @param 
// @param 
// @param 
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

// @brief 
// @param 
// @param 
// @param 
void CalculateMoments(Image input, std::vector<ObjectDesc>& objects, std::set<int>& labels) {
  size_t input_rows = input.num_rows();
  size_t input_cols = input.num_columns();
  int current_pixel = 0;

  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < input_cols; ++j) {
      current_pixel = input.GetPixel(i, j);
      
      int obj_index;
  
      // pixel is part of object
      if(current_pixel > 0) {
      // if current pixel label has already been discovered
        if(labels.find(current_pixel) != labels.end()) {
          // find the object struct with the corresponding label in objects vector
          obj_index = FindObject(objects, current_pixel);
          // calculate a b and c. x corresponds to i, and y corresponds to j
          objects[obj_index].a += pow((i - objects[obj_index].row_centr),2);
          objects[obj_index].b += 2*(i - objects[obj_index].row_centr)*(j - objects[obj_index].col_centr);
          objects[obj_index].c += pow((j - objects[obj_index].col_centr),2);
        }
      }
    }
  }
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

  double theta = 0.0;
  double theta2 = 0.0;
  double E_min = 0.0;
  double E_max = 0.0;
  int x_orient = 0.0;
  int y_orient = 0.0;

  ofstream output(output_descriptions_filename);

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

  CalculateMoments(input, Objects, labels);

  for(int i = 0; i < length; i++) {
    // calculate min theta and max theta
    Objects[i].theta = atan2(Objects[i].b, (Objects[i].a-Objects[i].c)) / 2.0;
    Objects[i].theta2 = Objects[i].theta + M_PI / 2.0;
    theta = Objects[i].theta;
    theta2 = Objects[i].theta2;

    // calculate E_min and E_max
    Objects[i].e_min = (Objects[i].a*pow(sin(theta), 2)) - (Objects[i].b*sin(theta)*cos(theta)) + (Objects[i].c*pow(cos(theta), 2));
    Objects[i].e_max = (Objects[i].a*pow(sin(theta2), 2)) - (Objects[i].b*sin(theta2)*cos(theta2)) + (Objects[i].c*pow(cos(theta2), 2));

    // calculate roundedness
    E_min = Objects[i].e_min;
    E_max = Objects[i].e_max;

    Objects[i].roundedness = E_min / E_max;

    // calculate orientation
    Objects[i].orientation = 180.0 * (theta / M_PI);

    // draw lines
    x_orient = Objects[i].row_centr + 30 * cos(theta); // x value of point on orientation line
    y_orient = Objects[i].col_centr + 30 * sin(theta); // x value of point on orientation line

    DrawLine(Objects[i].row_centr, Objects[i].col_centr, x_orient, y_orient, 150, &input);

    // printing out information (debugging purposes)
    // cout << i << " ";
    // cout << Objects[i].area << " ";
    // cout << Objects[i].row_centr << " ";
    // cout << Objects[i].col_centr << " ";

    // cout << "a: " << setprecision(9) << Objects[i].a << " b: " << setprecision(9) << Objects[i].b << " c: ";
    // cout << setprecision(9) << Objects[i].c << " ";
    // cout << "theta: " << theta << " ";
    // cout << "emin: " << Objects[i].e_min << " ";
    // cout << "roundedness: " << Objects[i].roundedness << " ";
    // cout << "orientation: " << Objects[i].orientation << endl;
 
    // writing to output file
    // output << i << " ";
    // output << Objects[i].row_centr << " ";
    // output << Objects[i].col_centr << " ";
    // output << Objects[i].e_min << " ";
    // output << Objects[i].area << " ";
    // output << Objects[i].roundedness << " ";
    // output << Objects[i].orientation << "\n";
  }
  
}

// @brief Compute object properties
// @param input_filename the name of the input labeled image
// @param input_descriptions_filename the name of the input descriptions file (txt)
// @param output_image_filename the name of the output image
void FindLabeledObject(const string &input_filename, const string &input_descriptions_filename, const string &output_filename) {
  cout << "Compute properties" << endl;
  cout << "Input labeled image filename: " << input_filename << endl;
  cout << "input descriptions filename: " << input_descriptions_filename << endl;
  cout << "Output image filename: " << output_filename << endl;
  
  string object_label_str = "";
  string row_centr_str = "";
  string col_centr_str = "";
  string e_min_str = "";
  string area_str = "";
  string roundedness_str = "";
  string orientation_str = "";

  int object_label = 0;
  double row_centr = 0;
  double col_centr = 0;
  double e_min = 0;
  int area = 0;
  double roundedness = 0;
  double orientation = 0;

  int current_pixel;
  ifstream fin(input_descriptions_filename);

  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;
    exit(1); // exit if failed to open the file
  }

  while(fin >> object_label_str >> row_centr_str >> col_centr_str >> e_min_str >> area_str >> roundedness_str >> orientation_str) {
    cout << object_label_str << " " << row_centr_str << " "  << col_centr_str << " "  << e_min_str << " " << area_str << " ";
    cout << roundedness_str << " "  << orientation_str << endl;

    std::vector<ObjectDesc> Objects;

    ObjectDesc new_object;
    new_object.object_label = stoi(object_label_str); // set new label
    new_object.area += 1; // increase area
  }

}

int main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s {input labeled image} {input descriptions file} {output image}\n", argv[0]);
    return 0;
  }
  
  const string input_filename(argv[1]);
  const string input_descriptions_filename(argv[2]);
  const string output_filename(argv[3]);

  FindLabeledObject(input_filename, input_descriptions_filename, output_filename);
  
  return 0;
}
