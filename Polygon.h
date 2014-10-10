

#ifndef _POLYGON_H
#define _POLYGON_H
#include "StructTypes.h"
#include <vector>
namespace MidTerm
{

    class Polygon
    {

    public:
        Polygon(const float x[], const float y[],int vertCount);

    private:
        //All Vertexes of the polygon
        std::vector<Vertex> PolyGonVertexes;

    };
}

#endif