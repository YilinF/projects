// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
    Image *img = new Image;
    Image *img2 = new Image;// create an Image in dynamic memory
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};

    Image_init(img, 5, 4);
    Image_set_pixel(img, 0, 0, green);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 0, 2, green);
    Image_set_pixel(img, 0, 3, green);
    Image_set_pixel(img, 0, 4, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, blue);
    Image_set_pixel(img, 1, 2, blue);
    Image_set_pixel(img, 1, 3, blue);
    Image_set_pixel(img, 1, 4, blue);
    Image_set_pixel(img, 2, 0, red);
    Image_set_pixel(img, 2, 1, red);
    Image_set_pixel(img, 2, 2, red);
    Image_set_pixel(img, 2, 3, red);
    Image_set_pixel(img, 2, 4, red);
    Image_set_pixel(img, 3, 0, white);
    Image_set_pixel(img, 3, 1, white);
    Image_set_pixel(img, 3, 2, white);
    Image_set_pixel(img, 3, 3, white);
    Image_set_pixel(img, 3, 4, white);

    Image_init(img2, 2, 2);
    Image_set_pixel(img2, 0, 0, red);
    Image_set_pixel(img2, 0, 1, green);
    Image_set_pixel(img2, 1, 0, blue);
    Image_set_pixel(img2, 1, 1, white);
  // Capture our output
    ostringstream s;
    Image_print(img2, s);

  // Correct output
    ostringstream correct1;
    correct1 << "P3\n2 2\n255\n";
    correct1 << "255 0 0 0 255 0 \n";
    correct1 << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s.str(), correct1.str());
    
    ostringstream s2;
    Image_print(img, s2);
    
// Correct output
    ostringstream correct2;
    correct2 << "P3\n5 4\n255\n";
    correct2 << "0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 \n";
    correct2 << "0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 \n";
    correct2 << "255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 \n";
    correct2 << "255 255 255 255 255 255 255 255 255 255 255 "
             << "255 255 255 255 \n";
    ASSERT_EQUAL(s2.str(), correct2.str());


    delete img; // delete the Image
    delete img2;
}
TEST(test_image_init) {
    Image *img = new Image;

    Image_init(img, 4, 5);
    ASSERT_EQUAL(4, Image_width(img));
    ASSERT_EQUAL(5, Image_height(img));
    Image_init(img, 1, 10);
    ASSERT_EQUAL(1, Image_width(img));
    ASSERT_EQUAL(10, Image_height(img));
    
    delete img;
}
TEST(test_init_whitespace) {
    Image *img = new Image;
    string output_correct = "P3\n2 2\n255\n"
                            "255 0 0 0 255 0 \n"
                            "0 0 255 255 255 255 \n";
    ostringstream no_extra_whitespace(output_correct);
    string no_whitespace = no_extra_whitespace.str();
    string whitespace = "P3 \t2 2 \t 255 \t255 0 0   0 255\n0 0 0 255\n";
    whitespace += " 255  255 \n255 \n";
    istringstream whitespace_istream(whitespace);
    Image_init(img, whitespace_istream);
    ostringstream corrected_ppm;
    Image_print(img, corrected_ppm);
    string fixed = corrected_ppm.str();

    ASSERT_EQUAL(no_whitespace, fixed);

    delete img;
}
TEST(test_image_get_pixel){
    Image *img = new Image;
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};
    Image_init(img, 4, 4);
    
    Image_fill(img, red);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 3), red));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), red));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), red));
    Image_fill(img, green);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 3), green));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), green));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), green));
    Image_fill(img, blue);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 3), blue));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), blue));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), blue));
    Image_fill(img, white);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 3), white));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), white));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), white));
    
    delete img;
}
TEST(test_image_set_pixel){
    Image *img = new Image;
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};
    Image_init(img, 4, 4);
    
    Image_set_pixel(img, 0, 0, red);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
    Image_set_pixel(img, 3, 3, red);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), red));
    Image_set_pixel(img, 3, 0, red);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), red));
    Image_set_pixel(img, 2, 3, green);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 3), green));
    Image_set_pixel(img, 1, 3, green);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 3), green));
    Image_set_pixel(img, 2, 0, green);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), green));
    Image_set_pixel(img, 0, 0, blue);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), blue));
    Image_set_pixel(img, 3, 3, blue);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), blue));
    Image_set_pixel(img, 3, 0, blue);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), blue));
    Image_set_pixel(img, 2, 3, white);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 3), white));
    Image_set_pixel(img, 1, 3, white);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 3), white));
    Image_set_pixel(img, 2, 0, white);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), white));
}
TEST(test_image_fill) {
    Image *img = new Image;
    const Pixel red = {255, 0, 0};

    Image_init(img, 4, 4);
    Image_fill(img, red);
    
    for (int i = 0; i < Image_height(img); i++) {
        for (int j = 0; j < Image_width(img); j++) {
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, i, j), red));
        }
    }
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
