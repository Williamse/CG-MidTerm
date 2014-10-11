#ifndef _VERTEX_MATRIX_H
#define _VERTEX_MATRIX_H
#include <cmatrix>
#include <vector>
#include <iostream>
namespace MidTerm
{
    //Define what a matrix is
    typedef techsoft::matrix<float> TMatrix;
    typedef std::valarray<float>    Vector;
    //Represents a point as a Homogenous Matrix
    class TransFormMatrix
    {
        private:


            //Apply the next transformation on the object
            void ApplyNextTransformation();
            

        public:
            //The Actual Transform Matrix
            TMatrix* _Matrix;
            TransFormMatrix();
	    //Returns the X and Y coordinates after performing all transformations
            //Index0 = X ; Index 1 = y
            std::vector<int> TransformPoly();
	    void DisplayMatrix();
	    void AddTransForm(TransFormMatrix* OtherMatrix);
	    void Scale(float x, float y);
	    void Translate(float x,float y);
	    void Rotate(float degrees);
        void TransFormMatrix::AddTransForm(TMatrix* OtherMatrix);
        void Clear();
    };
}

#endif
