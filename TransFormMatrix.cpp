#include "TransFormMatrix.h"

using namespace MidTerm;



TransFormMatrix::TransFormMatrix()
{
   //Initially set the Transformation to the identity matrix
   this->_Matrix = new TMatrix(3,3);
   this->_Matrix[0][0][0] = 1;
   this->_Matrix[0][1][1] = 1;
   this->_Matrix[0][2][2] = 1;
}
std::vector<int> TransFormMatrix::TransformPoly()
{
    return *(new std::vector<int>());
}
void TransFormMatrix::DisplayMatrix()
{
  this->_Matrix[0][0][0] = 1;
  std::cout << this->_Matrix[0] << std::endl;   
}
