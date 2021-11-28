// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_innit_basic) {
    Matrix *mat = new Matrix;
    const int width = 4;
    const int height = 7;
    Matrix_init(mat, 4, 7);
    ASSERT_EQUAL(Matrix_width(mat), width);
    ASSERT_EQUAL(Matrix_height(mat), height);
    delete mat;
}

TEST(test_print_basic)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 3);
    *Matrix_at(mat, 0, 0) = 31;
    *Matrix_at(mat, 0, 1) = 13;
    *Matrix_at(mat, 1, 0) = 50;
    *Matrix_at(mat, 1, 1) = 20;
    *Matrix_at(mat, 2, 0) = 10;
    *Matrix_at(mat, 2, 1) = 50;
    
    ostringstream expected;
    expected << "2 3\n"
             << "31 13 \n"
             << "50 20 \n"
             << "10 50 \n";
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;
    
}

TEST(test_width)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 6, 5);
    ASSERT_EQUAL(Matrix_width(mat), 6);
    
    delete mat;
    
}

TEST(test_height)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 7);
    ASSERT_EQUAL(Matrix_height(mat), 7);
    
    delete mat;
    
}

TEST(test_row_basic)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 3);
    *Matrix_at(mat, 0, 0) = 6;
    *Matrix_at(mat, 0, 1) = 99;
    *Matrix_at(mat, 1, 0) = 2;
    *Matrix_at(mat, 1, 1) = 52;
    *Matrix_at(mat, 2, 0) = 0;
    *Matrix_at(mat, 2, 1) = 1;
    
    int row1 = Matrix_row(mat, Matrix_at(mat, 1, 1));
    ASSERT_EQUAL(1 , row1);
    
    int row2 = Matrix_row(mat, Matrix_at(mat, 0, 2));
    ASSERT_EQUAL(0 , row2);
    
    int row3 = Matrix_row(mat, Matrix_at(mat, 0, 0));
    ASSERT_EQUAL(0 , row3);
    
    int row4 = Matrix_row(mat, Matrix_at(mat, 2, 1));
    ASSERT_EQUAL(2 , row4);
    
    delete mat;
}

TEST(test_row_more)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 5, 4);
    
    int *ptr = Matrix_at(mat, 3, 2);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 3);
    delete mat;
}



TEST(test_column_basic)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 2);
    *Matrix_at(mat, 0, 0) = 99;
    *Matrix_at(mat, 0, 1) = 0;
    *Matrix_at(mat, 0, 2) = 1;
    *Matrix_at(mat, 1, 0) = 21;
    *Matrix_at(mat, 1, 1) = 2;
    *Matrix_at(mat, 1, 2) = 0;
    
    int column1 =Matrix_column(mat, Matrix_at(mat, 0, 1));
    ASSERT_EQUAL(1 , column1);
    int column2 =Matrix_column(mat, Matrix_at(mat, 1, 2));
    ASSERT_EQUAL(2 , column2);
    int column3 =Matrix_column(mat, Matrix_at(mat, 1, 0));
    ASSERT_EQUAL(0 , column3);
    int column4 =Matrix_column(mat, Matrix_at(mat, 0, 0));
    ASSERT_EQUAL(0 , column4);
    
    delete mat;
    
}

TEST(test_fill_border)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    *Matrix_at(mat, 0, 0) = 0;
    *Matrix_at(mat, 0, 1) = 99;
    *Matrix_at(mat, 0, 2) = 7;
    *Matrix_at(mat, 1, 0) = 22;
    *Matrix_at(mat, 1, 1) = 2;
    *Matrix_at(mat, 1, 2) = 0;
    *Matrix_at(mat, 2, 0) = 80;
    *Matrix_at(mat, 2, 1) = 51;
    *Matrix_at(mat, 2, 2) = 1;
    const int width = 3;
    const int height = 3;
    const int value = 1;
    
    Matrix_fill_border(mat, value);

    for(int row = 0; row < height; ++row){
      for(int col = 0; col < width; ++col){
        //ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
          if (row == 0)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
          }
          
          if (row == Matrix_height(mat) - 1)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
              
          }
          
          if (col == 0)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
              
          }
          
          if (col == Matrix_width(mat) - 1)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
          }
      }
    }

    delete mat;
    
}

TEST(test_fill_border_more)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 1);
    *Matrix_at(mat, 0, 0) = 9;
    *Matrix_at(mat, 0, 1) = 0;
    *Matrix_at(mat, 0, 2) = 31;
    *Matrix_at(mat, 0, 3) = 80;
   
    const int width = 4;
    const int height = 1;
    const int value = 1;
    
    Matrix_fill_border(mat, value);

    for(int row = 0; row < height; ++row){
      for(int col = 0; col < width; ++col){
        //ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
          if (row == 0)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
          }
          
          if (row == Matrix_height(mat) - 1)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
              
          }
          
          if (col == 0)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
              
          }
          
          if (col == Matrix_width(mat) - 1)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
          }
      }
    }

    delete mat;
    
}


TEST(test_fill_border_more2)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
    *Matrix_at(mat, 0, 0) = 77;
    *Matrix_at(mat, 0, 1) = 3;
    *Matrix_at(mat, 1, 0) = 41;
    *Matrix_at(mat, 1, 1) = 0;
   
    const int width = 2;
    const int height = 2;
    const int value = 1;
    
    Matrix_fill_border(mat, value);

    for(int row = 0; row < height; ++row){
      for(int col = 0; col < width; ++col){
        //ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
          if (row == 0)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
          }
          
          if (row == Matrix_height(mat) - 1)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
              
          }
          
          if (col == 0)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
              
          }
          
          if (col == Matrix_width(mat) - 1)
          {
              ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
          }
      }
    }

    delete mat;
    
}
TEST(test_max)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);
    *Matrix_at(mat, 0, 0) = 32;
    *Matrix_at(mat, 0, 1) = 2;
    *Matrix_at(mat, 1, 0) = 32;
    *Matrix_at(mat, 1, 1) = 0;
    
    ASSERT_EQUAL(32, Matrix_max(mat));
    
    delete mat;
}

TEST(test_max_more)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 3);
    *Matrix_at(mat, 0, 0) = 32;
    *Matrix_at(mat, 0, 1) = 32;
    *Matrix_at(mat, 1, 0) = 0;
    *Matrix_at(mat, 1, 1) = 1;
    *Matrix_at(mat, 2, 0) = 20;
    *Matrix_at(mat, 2, 1) = 20;
    
    
    ASSERT_EQUAL(32, Matrix_max(mat));
    
    delete mat;
}

TEST(test_column_of_min_value)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 6, 6);
    Matrix_fill(mat, 2);

    *Matrix_at(mat, 3, 0) = 64;
    *Matrix_at(mat, 3, 1) = 2;
    *Matrix_at(mat, 3, 2) = 1;
    *Matrix_at(mat, 3, 3) = 64;
    *Matrix_at(mat, 3, 4) = 1;

    int column = Matrix_column_of_min_value_in_row(mat, 3, 0, 5);
    ASSERT_EQUAL(1, column);

    delete mat;

}

TEST(test_column_of_min_value_more)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 6, 6);
    Matrix_fill(mat, 2);

    *Matrix_at(mat, 3, 0) = 0;
    *Matrix_at(mat, 3, 1) = 2;
    *Matrix_at(mat, 3, 2) = 52;
    *Matrix_at(mat, 3, 3) = 0;
    *Matrix_at(mat, 3, 4) = 2;

    int column = Matrix_column_of_min_value_in_row(mat, 3, 1, 3);
    ASSERT_EQUAL(2, column);

    delete mat;

}

TEST(test_min_value_in_row)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 6, 6);
    Matrix_fill(mat, 2);

    *Matrix_at(mat, 3, 0) = 4;
    *Matrix_at(mat, 3, 1) = 34;
    *Matrix_at(mat, 3, 2) = 20;
    *Matrix_at(mat, 3, 3) = 34;
    *Matrix_at(mat, 3, 4) = 4;

   
    ASSERT_EQUAL(4, Matrix_min_value_in_row(mat, 3, 0, 5));

    delete mat;
    
}

TEST(test_min_value_in_row_more)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 6, 6);
    Matrix_fill(mat, 2);

    *Matrix_at(mat, 3, 0) = 32;
    *Matrix_at(mat, 3, 1) = 77;
    *Matrix_at(mat, 3, 2) = 2;
    *Matrix_at(mat, 3, 3) = 1;
    *Matrix_at(mat, 3, 4) = 2;

   
    ASSERT_EQUAL(1, Matrix_min_value_in_row(mat, 3, 1, 4));

    delete mat;
    
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
