#include "Polygon.h"



using namespace MidTerm;



Polygon::Polygon(const float x[], const float y[], int vertCount)
{
    this->PolyGonVertexes = new std::vector<Vertex*>();
    for (int count = 0; count < vertCount; count++)
    {
        Vertex* vert = new Vertex();
        vert->x = x[count];
        vert->y = y[count];

        this->PolyGonVertexes->push_back(vert);
    }
}
Polygon::~Polygon()
{
    for (int x = 0; x < this->PolyGonVertexes->size(); x++)
    {
        delete this->PolyGonVertexes->at(x);
        this->PolyGonVertexes->at(x) = NULL;
    }
    delete this->PolyGonVertexes;
    this->PolyGonVertexes = NULL;

}
//Apply this transformation to the polygon
void Polygon::Transform(MidTerm::TransFormMatrix mat)
{
    for (int x = 0; x < this->PolyGonVertexes->size(); x++)
    {
        this->PolyGonVertexes->at(x)->Transform(mat);
    }
}
int Polygon::GetVertexCount()
{
    return this->PolyGonVertexes->size();
}
int * Polygon::GetX()
{
    int  * returnval = new int[this->PolyGonVertexes->size()];
    for (int x = 0; x < this->PolyGonVertexes->size(); x++)
    {
        returnval[x] = this->PolyGonVertexes->at(x)->x;
    }
    return returnval;
}
int * Polygon::GetY()
{
    int * returnval = new int[this->PolyGonVertexes->size()];
    for (int x = 0; x < this->PolyGonVertexes->size(); x++)
    {
        returnval[x] = this->PolyGonVertexes->at(x)->y;
    }
    return returnval;
}