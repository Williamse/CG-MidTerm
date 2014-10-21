#include "TransFormMatrix.h"
#include <cmath>
#include "StructTypes.h"
using namespace MidTerm;

TransFormMatrix::TransFormMatrix()
{
   //Initially set the Transformation to the identity matrix
   this->_Matrix = new TMatrix(3,3);
   this->_Matrix[0][0][0] = 1.0f;
   this->_Matrix[0][0][1] = 0.0f;
   this->_Matrix[0][0][2] = 0.0f;

   this->_Matrix[0][1][0] = 0.0f;
   this->_Matrix[0][1][1] = 1.0f;
   this->_Matrix[0][1][2] = 0.0f;

   this->_Matrix[0][2][0] = 0.0f;
   this->_Matrix[0][2][1] = 0.0f;
   this->_Matrix[0][2][2] = 1.0f;
}
TransFormMatrix::~TransFormMatrix()
{
   delete this->_Matrix;
  this->_Matrix = NULL;
}
std::vector<int> TransFormMatrix::TransformPoly()
{
    return *(new std::vector<int>());
}
void TransFormMatrix::DisplayMatrix()
{
  std::cout << this->_Matrix[0] << std::endl;  
}

//Adds another transformation to this one (Destroys the previous one) 
void TransFormMatrix::AddTransForm(TransFormMatrix* OtherMatrix )
{

   this->AddTransForm(OtherMatrix->_Matrix);
   delete OtherMatrix;
     OtherMatrix = NULL;
}
//Set to the identity matrix
void TransFormMatrix::Clear()
{

    this->_Matrix[0][0][0] = 1.0f;
    this->_Matrix[0][0][1] = 0.0f;
    this->_Matrix[0][0][2] = 0.0f;

    this->_Matrix[0][1][0] = 0.0f;
    this->_Matrix[0][1][1] = 1.0f;
    this->_Matrix[0][1][2] = 0.0f;

    this->_Matrix[0][2][0] = 0.0f;
    this->_Matrix[0][2][1] = 0.0f;
    this->_Matrix[0][2][2] = 1.0f;

}
void TransFormMatrix::AddTransForm(TMatrix* OtherMatrix)
{  
  TMatrix  temp = this->_Matrix[0] * OtherMatrix[0];
  this->_Matrix[0] = temp;
    delete OtherMatrix;
    OtherMatrix = NULL;
}
void TransFormMatrix::Scale(float x, float y)
{
  TMatrix* scaled = new TMatrix(3,3);
  scaled[0][0][0] = x;
  scaled[0][0][1] = 0.0f;
  scaled[0][0][2] = 0.0f;

  scaled[0][1][0] = 0.0f;
  scaled[0][1][1] = y;
  scaled[0][1][2] = 0.0f;

  scaled[0][2][0] = 0.0f;
  scaled[0][2][1] = 0.0f;
  scaled[0][2][2] = 1.0f;



  this->AddTransForm(scaled);
  
}
void TransFormMatrix::NormalizedTransform(float left,float right, float top, float bottom,int width_world,int height_world,int xmin_screen,int ymin_screen)
{
    //Create normalizer matrix
    TMatrix* normalizer= new TMatrix(3, 3);



    //Row 0
    //normalizer[0][0][0] = width_world / (right - left);
    //normalizer[0][0][1] = 0;
    //normalizer[0][0][2] = ((-width_world * left) / (right - left)) - 1.0f;
   
    //Row 1
    //normalizer[0][1][0] = 0.0f;
    //normalizer[0][1][1] = (height_world) / (top - bottom);
    //normalizer[0][1][2] = ((-height_world * bottom) / (top - bottom)) - 1.0f;
    //   
    //Row 2
    //normalizer[0][2][0] = 0.0f;
    //normalizer[0][2][1] = 0.0f;
    //normalizer[0][2][2] = 1.0f;


    this->AddTransForm(normalizer);
}

void TransFormMatrix::NormalizeAndViewport(float left, float right, float top, float bottom, int width_world, int height_world, int xmin_screen, int ymin_screen)
{
    //Create normalizer matrix
    TMatrix* normalizer = new TMatrix(3, 3);

    float xmax = xmin_screen + width_world;
    float ymax = ymin_screen + height_world;


   // Row 0
    normalizer[0][0][0] = (xmax - xmin_screen) / (right - left);
    normalizer[0][0][1] = 0;
    normalizer[0][0][2] = ((right * xmin_screen) - (left * xmax)) / (right- left);

   // Row 1
    normalizer[0][1][0] = 0.0f;
    normalizer[0][1][1] = (ymax - ymin_screen) / (top - bottom);
    normalizer[0][1][2] = ((top * ymin_screen) - (bottom * ymax)) / (top - bottom);

   // Row 2
    normalizer[0][2][0] = 0.0f;
    normalizer[0][2][1] = 0.0f;
    normalizer[0][2][2] = 1.0f;


    this->AddTransForm(normalizer);
}
void TransFormMatrix::Translate(float x,float y)
{
  TMatrix* scaled = new TMatrix(3,3);
  //Row 1
  scaled[0][0][0] = 1.0f;
  scaled[0][0][1] = 0.0f;
  scaled[0][0][2] = x;  
  //Row 2
  scaled[0][1][0] = 0.0f;
  scaled[0][1][1] = 1.0f;
  scaled[0][1][2] = y;
  
  //Row 3
  scaled[0][2][0] = 0.0f;
  scaled[0][2][1] = 0.0f;
  scaled[0][2][2] = 1.0f;
  this->AddTransForm(scaled);
}
void TransFormMatrix::Rotate(float degrees)
{
  degrees = (degrees * 3.141592653589793f) / 180.0f;
  TMatrix* rotated = new TMatrix(3,3);

  //Row 1
  rotated[0][0][0] = cos(degrees);
  rotated[0][0][1] = -1.0f * sin(degrees);
  rotated[0][0][2] = 0.0f;
  //Row 2
  rotated[0][1][0] = 1 * sin(degrees);
  rotated[0][1][1] = cos(degrees);
  rotated[0][1][2] = 0.0f;
  //Row 3
  rotated[0][2][0] = 0.0f;
  rotated[0][2][1] = 0.0f;
  rotated[0][2][2] = 1.0f;
  this->AddTransForm(rotated); 
}
