#include "TransFormMatrix.h"
#include <cmath>
#include "StructTypes.h"
using namespace MidTerm;

TransFormMatrix::TransFormMatrix()
{
   //Initially set the Transformation to the identity matrix
   this->_Matrix = new TMatrix(3,3);
   this->_Matrix[0][0][0] = 1.0f;
   this->_Matrix[0][1][1] = 1.0f;
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
    this->_Matrix[0][0][0] = 1;
    this->_Matrix[0][0][1] = 0;
    this->_Matrix[0][0][2] = 0;

    this->_Matrix[0][1][0] = 0;
    this->_Matrix[0][1][1] = 1;
    this->_Matrix[0][1][2] = 0;

    this->_Matrix[0][2][0] = 0;
    this->_Matrix[0][2][1] = 0;
    this->_Matrix[0][2][2] = 1;

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
  scaled[0][1][1] = y;
  scaled[0][2][2] = 1;
  
  this->AddTransForm(scaled);
  
}
void TransFormMatrix::Translate(float x,float y)
{
  TMatrix* scaled = new TMatrix(3,3);
  //Row 1
  scaled[0][0][0] = 1;
  scaled[0][0][2] = x;  
  //Row 2
  scaled[0][1][1] = 1;
  scaled[0][1][2] = y;
  
  //Row 3
  scaled[0][2][2] = 1;
  this->AddTransForm(scaled);
}
void TransFormMatrix::Rotate(float degrees)
{

  TMatrix* rotated = new TMatrix(3,3);




  //Row 1
  rotated[0][0][0] = cos(degrees);
  rotated[0][0][1] = sin(degrees);  
  //Row 2
  rotated[0][1][0] = -1 * sin(degrees);
  rotated[0][1][1] = cos(degrees);
  
  //Row 3
  rotated[0][2][2] = 1;
  this->AddTransForm(rotated); 
}
