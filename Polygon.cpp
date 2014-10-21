#include "Polygon.h"



using namespace MidTerm;

//Let the OS delete me
clipper* Polygon::Clipper = new clipper();

Polygon::Polygon(const float x[], const float y[], int vertCount)
{
    this->PolyGonVertexsClipped = NULL;
    this->PolyGonVertexes = new std::vector<Vertex*>();
    for (int count = 0; count < vertCount; count++)
    {
        Vertex* vert = new Vertex(x[count],y[count]);

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
    for(int x =0 ; x < this->PolyGonVertexsClipped->size();x++)
      {
	delete this->PolyGonVertexsClipped->at(x);
	this->PolyGonVertexsClipped->at(x) = NULL;
      }

    delete this->PolyGonVertexes;
    this->PolyGonVertexes = NULL;

}
//Apply this transformation to the polygon
void Polygon::Transform(MidTerm::TransFormMatrix* mat)
{
    for (int x = 0; this->PolyGonVertexsClipped != NULL && x < this->PolyGonVertexsClipped->size(); x++)
    {
        this->PolyGonVertexsClipped->at(x)->Transform(mat);
    }
    for (int x = 0; x < this->PolyGonVertexes->size(); x++)
    {
        this->PolyGonVertexes->at(x)->Transform(mat);
    }
}
void Polygon::ResetTransforms()
{
    for (int x = 0; this->PolyGonVertexes != NULL && x < this->PolyGonVertexes->size(); x++)
    {
        this->PolyGonVertexes->at(x)->Reset();
    }
    for (int x = 0;this->PolyGonVertexsClipped != NULL && x < this->PolyGonVertexsClipped->size(); x++)
    {
	
        this->PolyGonVertexsClipped->at(x)->Reset();
    }
}
int Polygon::GetVertexCount()
{
    int return_val = this->HasClipped() ? this->PolyGonVertexsClipped->size() : this->PolyGonVertexes->size();

    return return_val;
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

int * Polygon::GetXClipped()
{
    int  * returnval = new int[this->PolyGonVertexsClipped->size()];
    for (int x = 0; x < this->PolyGonVertexsClipped->size(); x++)
    {
        returnval[x] = this->PolyGonVertexsClipped->at(x)->x;
    }
    return returnval;
}
int *Polygon::GetYClipped()
{
    int * returnval = new int[this->PolyGonVertexsClipped->size()];
    for (int x = 0; x < this->PolyGonVertexsClipped->size(); x++)
    {
        returnval[x] = this->PolyGonVertexsClipped->at(x)->y;
    }
    return returnval;
}

bool Polygon::HasClipped()
{
    if (this->PolyGonVertexsClipped != NULL && this->PolyGonVertexsClipped->size() > 0)
    {
        return true;
    }
    return false;
}
void Polygon::Clip(Vertex* topLeft, Vertex* TopRight, Vertex* bottomLeft, Vertex* BottomRight)
{
    int inSize = this->PolyGonVertexes->size();
    int * outX = new int[inSize + 1];
    int * outY = new int[inSize + 1];
    int * inx  = this->GetX();
    int * iny = this->GetY();


    int outSize = this->Clipper->clipPolygon(inSize, inx, iny, outX, outY, bottomLeft->x, bottomLeft->y, TopRight->x, TopRight->y);

    for (int x = 0; this->PolyGonVertexsClipped != NULL && x < this->PolyGonVertexsClipped->size(); x++)
    {
        delete this->PolyGonVertexsClipped->at(x);
        this->PolyGonVertexsClipped->at(x) = NULL;
    }
    if (this->PolyGonVertexsClipped != NULL) { this->PolyGonVertexsClipped->clear(); };
    for (int x = 0; x < outSize; x++)
    {
        Vertex* ver = new Vertex(outX[x],outY[x]);

        if (this->PolyGonVertexsClipped == NULL){ this->PolyGonVertexsClipped = new vector<MidTerm::Vertex*>(); }
        this->PolyGonVertexsClipped->push_back(ver);
    }
    delete[] outX;
    outX = NULL;
    delete[] outY; 
    outY = NULL;
    delete[] inx;
    inx = NULL;
    delete[] iny; 
    iny = NULL;
}
