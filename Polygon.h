

#ifndef _POLYGON_H
#define _POLYGON_H
#include "StructTypes.h"
#include <vector>
#include "TransFormMatrix.h"
namespace MidTerm
{

    class Polygon
    {

    public:
        Polygon(const float x[], const float y[],int vertCount);
        ~Polygon();
        void Transform(MidTerm::TransFormMatrix mat);
        //All Vertexes of the polygon
        int* GetX();
        int* GetY();
        int GetVertexCount();
    private:
        std::vector<Vertex*>* PolyGonVertexes;

    };
}

#endif