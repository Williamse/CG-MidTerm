#ifndef _STRUCT_TYPES_H
#define _STRUCT_TYPES_H

namespace BaseTypes
{
    /**
    *Vertex Struct
    */
    struct Vertex
    {
        float x, y;
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
