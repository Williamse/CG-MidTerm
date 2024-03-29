#ifndef _VERTEX_MATRIX_H
#define _VERTEX_MATRIX_H
#include <cmatrix>
#include <vector>
#include <iostream>
namespace MidTerm
{
    //Define what a matrix is
    typedef techsoft::matrix<float> TMatrix;
    typedef std::valarray<float> Vector;
    //Represents a point as a Homogenous Matrix
    class TransFormMatrix
    {
        private:


            //Apply the next transformation on the object
            void ApplyNextTransformation();
        public:
        TMatrix* _Matrix;
	    ~TransFormMatrix();
        TransFormMatrix();
        std::vector<int> TransformPoly();
	    void DisplayMatrix();
	    void AddTransForm(TransFormMatrix* OtherMatrix);
	    void Scale(float x, float y);
	    void Translate(float x,float y);
	    void Rotate(float degrees);
        void AddTransForm(TMatrix* OtherMatrix);
        void Clear();
        void NormalizedTransform(float left, float right, float top, float bottom, int width_world, int height_world, int xmin_screen, int ymin_screen);
        void NormalizeAndViewport(float left, float right, float top, float bottom, int width_world, int height_world, int xmin_screen, int ymin_screen);
    };
}

#endif
