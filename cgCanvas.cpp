//
//  cgCanvas.cpp
//
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//

#include "cgCanvas.h"

/**
 * Simple wrapper class for midterm assignment
 *
 * Only methods in the implementation file whose bodies
 * contain the comment
 *
 *    // YOUR IMPLEMENTATION HERE
 *
 * are to be modified by students.
 */

/**
 * Constructor
 *
 * @param w - width of canvas
 * @param h - height of canvas
 */
cgCanvas::cgCanvas(int w, int h) : simpleCanvas (w,h)
{
    this->PolyGons = new vector<PolygonPointer*>();
    this->mat = new MidTerm::TransFormMatrix();
    this->Rast = new Rasterizer();

        // YOUR IMPLEMENTATION HERE if you need to modify the constructor
}

cgCanvas::~cgCanvas()
{
    delete this->mat;
    this->mat = NULL;

    for (int x = 0; x < this->PolyGons->size(); x++)
    {
        delete this->PolyGons->at(x);
        this->PolyGons->at(x) = NULL;
    }
    delete this->PolyGons;
    this->PolyGons = NULL;
    delete this->Rast;
    this->Rast = NULL;
    delete this->topLeft;
    delete this->topRight;
    delete this->bottomLeft;
    delete this->bottomRight;
}
/**
 * addPoly - Add a polygon to the canvas.  This method does not draw
 *           the polygon, but merely stores it for later drawing.
 *           Drawing is initiated by the drawPoly() method.
 *
 *           Returns a unique integer id for the polygon.
 *
 * @param x - Array of x coords of the vertices of the polygon to be added
 * @param y - Array of y coords of the vertices of the polygon to be added
 * @param n - Number of verticies in polygon
 *
 * @return a unique integer identifier for the polygon
 */
int cgCanvas::addPoly (const float x[], const float y[], int n)
{
    
    this->CurId++;
    PolygonPointer* p = new PolygonPointer();
    p->Polygon = new MidTerm::Polygon(x, y, n);
    p->ID = this->CurId;
    this->PolyGons->push_back(p);
    return CurId;


    // YOUR IMPLEMENTATION HERE
    // REMEMBER TO RETURN A UNIQUE ID FOR THE POLYGON
}

/**
 * drawPoly - Draw the polygon with the given id.  The polygon should
 *            be drawn after applying the current transformation to
 *            the vertices of the polygon.
 *
 * @param polyID - the ID of the polygon to be drawn
 */
void cgCanvas::drawPoly (int polyID)
{
    MidTerm::Polygon* pol = NULL;

    for (int x = 0; x < this->PolyGons->size(); x++)
    {
        if (this->PolyGons->at(x)->ID == polyID)
        {
            pol = this->PolyGons->at(x)->Polygon;

            pol->ResetTransforms();
            pol->Transform(*(this->mat));


           // Normalized coords
      //     MidTerm::TransFormMatrix* mat = new MidTerm::TransFormMatrix();
     //      mat->NormalizedTransform(this->bottomLeft->x, this->bottomRight->x, this->topLeft->y, this->bottomLeft->y);
     //      pol->Transform(*mat);


//            pol->Clip(this->topLeft, this->topRight, this->bottomLeft, this->bottomRight);








            this->Rast->drawPolygon(pol, *this,this->topLeft->y,this->bottomLeft->y,this->bottomLeft->x,this->bottomRight->x);
            break;
        }
    }
}

/**
 * clearTransform - Set the current transformation to the identity matrix.
 */
void cgCanvas::clearTransform()
{
    this->mat->Clear();
}

/**
 * translate - Add a translation to the current transformation by
 *             premultiplying the appropriate translation matrix to
 *             the current transformation matrix.
 *
 * @param x - Amount of translation in x
 * @param y - Amount of translation in y
 */
void cgCanvas::translate (float x, float y)
{
    this->mat->Translate(x, y);
    // YOUR IMPLEMENTATION HERE
}

/**
 * rotate - Add a rotation to the current transformation by premultiplying
 *          the appropriate rotation matrix to the current transformation
 *          matrix.
 *
 * @param degrees - Amount of rotation in degrees
 */
void cgCanvas::rotate (float degrees)
{
    this->mat->Rotate(degrees);
    // YOUR IMPLEMENTATION HERE
}

/**
 * scale - Add a scale to the current transformation by premultiplying
 *         the appropriate scaling matrix to the current transformation
 *         matrix.
 *
 * @param x - Amount of scaling in x
 * @param y - Amount of scaling in y
 */
void cgCanvas::scale (float x, float y)
{
    this->mat->Scale(x, y);
    // YOUR IMPLEMENTATION HERE
}

/**
 * setClipWindow - Define the clip window.
 *
 * @param bottom - y coord of bottom edge of clip window (in world coords)
 * @param top - y coord of top edge of clip window (in world coords)
 * @param left - x coord of left edge of clip window (in world coords)
 * @param right - x coord of right edge of clip window (in world coords)
 */
void cgCanvas::setClipWindow (float bottom, float top, float left, float right)
{
    this->topLeft = new MidTerm::Vertex(left,top);
    this->topRight = new MidTerm::Vertex(right,top);
    this->bottomLeft = new MidTerm::Vertex(left,bottom);
    this->bottomRight = new MidTerm::Vertex(right,bottom);
}

/**
 * setViewport - Define the viewport.
 *
 * @param xmin - x coord of lower left of view window (in screen coords)
 * @param ymin - y coord of lower left of view window (in screen coords)
 * @param width - width of view window (in world coords)
 * @param height - width of view window (in world coords)
 */
void cgCanvas::setViewport (int x, int y, int width, int height)
{
    // YOUR IMPLEMENTATION HERE
}
