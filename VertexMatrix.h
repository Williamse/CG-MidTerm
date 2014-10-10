#ifndef _VERTEX_MATRIX_H
#define _VERTEX_MATRIX_H
#include <cmatrix>
#include <vector>

namespace MidTerm
{
    //Define what a matrix is
    typedef techsoft::matrix<int> Matrix;

    //Represents a point as a Homogenous Matrix
    class VertexMatrix
    {
        private:
            //Returns the X and Y coordinates after performing all transformations
            //Index0 = X ; Index 1 = y
            std::vector<int> GetPoints();

            
        public:

    };
}

#endif
