#ifndef _VERTEX_MATRIX_H
#define _VERTEX_MATRIX_H
#include <cmatrix>
#include <vector>
#include <iostream>
namespace MidTerm
{
    //Define what a matrix is
    typedef techsoft::matrix<int> TMatrix;

    //Represents a point as a Homogenous Matrix
    class TransFormMatrix
    {
        private:
            //The Actual Transform Matrix
            TMatrix* _Matrix;

            //Apply the next transformation on the object
            void ApplyNextTransformation();
            

        public:

            TransFormMatrix();
	    //Returns the X and Y coordinates after performing all transformations
            //Index0 = X ; Index 1 = y
            std::vector<int> TransformPoly();
	    

	    void DisplayMatrix();
    };
}

#endif
