#include "TransFormMatrix.h"
#include <cmath>
#include "StructTypes.h"
using namespace MidTerm;

TransFormMatrix::TransFormMatrix()
{
   //Initially set the Transformation to the identity matrix
   this->_Matrix = new TMatrix(3,3);
   this->_Matrix[0][0][0] = 1.0f;
   this->_Matrix[0][0][1] = 0;
   this->_Matrix[0][0][2] = 0;

   this->_Matrix[0][1][0] = 0;
   this->_Matrix[0][1][1] = 1.0f;
   this->_Matrix[0][1][2] = 0;

   this->_Matrix[0][2][0] = 0;
   this->_Matrix[0][2][1] = 0;
   this->_Matrix[0][2][2] = 1.0f;
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

}
//Set to the identity matrix
void TransFormMatrix::Clear()
{

    this->_Matrix[0][0][0] = 1.0f;
    this->_Matrix[0][0][1] = 1.0f;
    this->_Matrix[0][0][2] = 1.0f;

    this->_Matrix[0][1][0] = 1.0f;
    this->_Matrix[0][1][1] = 1.0f;
    this->_Matrix[0][1][2] = 1.0f;

    this->_Matrix[0][2][0] = 1.0f;
    this->_Matrix[0][2][1] = 1.0f;
    this->_Matrix[0][2][2] = 1.0f;
    this->DisplayMatrix();

}
void TransFormMatrix::AddTransForm(TMatrix* OtherMatrix)
{
    this->_Matrix[0] = this->_Matrix[0] * OtherMatrix[0];
    delete OtherMatrix;
}
void TransFormMatrix::Scale(float x, float y)
{
  TMatrix* scaled = new TMatrix(3,3);
  scaled[0][0][0] = x;
  scaled[0][0][1] = 0;
  scaled[0][0][2] = 0;

  scaled[0][1][0] = 0;
  scaled[0][1][1] = y;
  scaled[0][1][2] = 0;

  scaled[0][2][0] = 0;
  scaled[0][2][1] = 0;
  scaled[0][2][2] = 1.0f;



  this->AddTransForm(scaled);
  
}
void TransFormMatrix::NormalizedTransform(float left,float right, float top, float bottom)
{
    //Create normalizer matrix
    TMatrix* normalizer= new TMatrix(3, 3);

    //Row 0
    normalizer[0][0][0] = 2.0f/(right - left);
    normalizer[0][0][1] = 0;
    normalizer[0][0][2] = ((-2 * left) / ((right - left))) - 1.0f ;
   
    //Row 1
    normalizer[0][1][0] = 0;
    normalizer[0][1][1] = 2.0f /(top - bottom);
    normalizer[0][1][2] = (((-2.0f * bottom) / ((top- bottom)))- 1.0f);
       
    //Row 2
    normalizer[0][2][0] = 0;
    normalizer[0][2][1] = 0;
    normalizer[0][2][2] = 1.0f;


    this->AddTransForm(normalizer);
}
void TransFormMatrix::Translate(float x,float y)
{
  TMatrix* scaled = new TMatrix(3,3);
  //Row 1
  scaled[0][0][0] = 1.0f;
  scaled[0][0][1] = 0;
  scaled[0][0][2] = x;  
  //Row 2
  scaled[0][1][0] = 0;
  scaled[0][1][1] = 1.0f;
  scaled[0][1][2] = y;
  
  //Row 3
  scaled[0][2][0] = 0;
  scaled[0][2][1] = 0;
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
  rotated[0][0][2] = 0;
  //Row 2
  rotated[0][1][0] = 1 * sin(degrees);
  rotated[0][1][1] = cos(degrees);
  rotated[0][1][2] = 0;
  //Row 3
  rotated[0][2][0] = 0;
  rotated[0][2][1] = 0;
  rotated[0][2][2] = 1.0f;
  this->AddTransForm(rotated); 
}
