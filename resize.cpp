// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <string>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"
//./resize.exe horses.ppm horses_400x250.ppm 400 250


using namespace std;

int main(int argc, char *argv[]) {
    Image *img = new Image;
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);
    int original_width = 0;
    int original_height = 0;
    string output_filename = argv[2];
    ofstream output;
    string input_filename = argv[1];
    ifstream myfile;
    myfile.open(input_filename);
    Image_init(img, myfile);
    if (myfile.is_open()) {
        original_height = Image_height(img);
        original_width = Image_width(img);
        if (argc == 4 && (width > 0 && width <= original_width)
            && (height > 0 && height <= original_height)) {
            original_height = height;
            output.open(output_filename);
            if (!output.is_open()) {
                cout << "Error opening file: " << output_filename << endl;
                return 1;
            }
            seam_carve(img, width, original_height);
        } else if (argc == 5 && (width > 0 && width <= original_width)
                   && (height > 0 && height <= original_height)) {
            output.open(output_filename);
            if (!output.is_open()) {
                cout << "Error opening file: " << output_filename << endl;
                return 1;
            }
            seam_carve(img, width, height);
        } else {
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME "
                 << "WIDTH [HEIGHT]\nWIDTH and HEIGHT must"
                 << " be less than or equal to original" << endl;
        }
    } else {
        cout << "Error opening file: " << input_filename << endl;
        return 1;
    }
    Image_print(img, output);
    myfile.close();
    output.close();
    delete img;
    return 0;
}
