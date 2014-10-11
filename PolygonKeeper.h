/*
*Emanuel Williams - CG Midterm
*Keeps track of polygons
*/

#ifndef _POLYGONKEEPER_H
#define _POLYGONKEEPER_H

#include"Polygon.h"
#include "Rasterizer.h"
#include <vector>


struct PolygonPointer
{
    int ID;
    MidTerm::Polygon* Polygon;
};

class PolyGonKeeper
{
    public:
        void DrawPolygon(int id, MidTerm::TransFormMatrix mat);
        int AddPolygon(MidTerm::Polygon* poly);
        PolyGonKeeper();
        ~PolyGonKeeper();
    private:
        Rasterizer* Rast;
        std::vector<PolygonPointer*> PolyGons;
        int CurId;
};
#endif