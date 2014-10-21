

#ifndef _POLYGON_H
#define _POLYGON_H
#include "StructTypes.h"
#include <vector>
#include "clipper.h"
#include "TransFormMatrix.h"
namespace MidTerm
{

    class Polygon
    {

    public:
        static clipper* Clipper;

        Polygon(const float x[], const float y[],int vertCount);
        ~Polygon();
        void Transform(MidTerm::TransFormMatrix* mat);
        //All Vertexes of the polygon
        int* GetX();
        int* GetY();

        int* GetXClipped();
        int* GetYClipped();

        int GetVertexCount();
        void Clip(Vertex* topLeft, Vertex* TopRight, Vertex* bottomLeft, Vertex* BottomRight);
        bool HasClipped();
        void ResetTransforms();
    private:
       
        std::vector<Vertex*>* PolyGonVertexes;
        std::vector<Vertex*>* PolyGonVertexsClipped;

    };
}

#endif