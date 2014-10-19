#ifndef _STRUCT_TYPES_H
#define _STRUCT_TYPES_H
#include <iostream>
#include "TransFormMatrix.h"
namespace MidTerm
{
    /**
    *Vertex Struct
    */
    struct Vertex
    {
        float x, y;
        float origx, origy;

        Vertex(float x, float y) :origx(x), origy(y), x(x), y(y)
        {

        }

        //Apply a transform to this Vertex
        void Transform(TransFormMatrix matrix)
        {
            MidTerm::Vector temp_vec = MidTerm::Vector(3);
            temp_vec[0] = this->x;
            temp_vec[1] = this->y;
            temp_vec[2] = 1;

            temp_vec = (*matrix._Matrix) * temp_vec;

            this->x = temp_vec[0];
            this->y = temp_vec[1];
        }
        void Reset()
        {
            this->x = origx;
            this->y = origy;
        }
    };

    /*
    *Represents a boundry of a line
    */
    enum BoundryType
    {
	East,
	North,
	South,
	West
    };
    /*
    *A line
    */
    struct Line
    {

        bool IsEdge;
        BoundryType BType;
        Vertex* Start;
        Vertex* End;

        Line(Vertex * Start, Vertex* End, bool IsEdge) : IsEdge(IsEdge), Start(Start), End(End)
        {
            if (End->x > Start->x)
            {
	        BType = South;
            }
	    else if (End->x < Start->x)         //Changed from the example
	    {
	        BType = North;
	    }
	    else if (End->y > Start->y)
	    {
		BType = East;
	    }
	    else if (End->y < Start->y)
	    {
	        BType = West;
 	    }

 	}
      };
}
#endif
