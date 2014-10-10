#include "Polygon.h"



using namespace MidTerm;



Polygon::Polygon(const float x[], const float y[], int vertCount)
{
    for (int count = 0; count < vertCount; count++)
    {
        Vertex vert = Vertex();
        vert.x = x[count];
        vert.y = y[count];

        this->PolyGonVertexes.push_back(vert);
    }
}