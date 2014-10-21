//
//  clipper.h
//
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//Modified by Emanuel williams for CG

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "simpleCanvas.h"
#include <vector>
namespace EnumTypes
{

	enum BoundryType
	{
		East,
		North,
		South,
		West
	};

	/**
	*Vertex Struct
	*/
	struct Vertex
	{
		float x, y;
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
/**
 * Simple class that performs clipping
 *
 */
class clipper {

private:
	void ClipSide(std::vector<EnumTypes::Vertex>* outputVertexes, std::vector<EnumTypes::Vertex> inputVertacies, EnumTypes::Line* Edge);
	/*
	*Creates a Clipping window
	*Index 0 = Left
	*Index 1 = Top
	*Index 2 = Right
	*Index 3 = Bottom
	*/
	std::vector<EnumTypes::Line*>* GenerateClipWindow(EnumTypes::Vertex* BottomLeft, EnumTypes::Vertex* TopRight);


	/**
	* Determines If a given vertex is inside of the given clipboundry
	*/
	bool Inside(EnumTypes::Vertex testVertex, EnumTypes::Line ClipBoundry);

	//Intersection point is outptu tointersectPt
	void Intersect(EnumTypes::Line testLine, EnumTypes::Line ClipBoundry, EnumTypes::Vertex  *intersectPt);


	void SwapOutputInput(std::vector<EnumTypes::Vertex>* input, std::vector<EnumTypes::Vertex>* output);

	void addVertexOutput(EnumTypes::Vertex* newVertex, std::vector<EnumTypes::Vertex>* outVertexArr);

	//Keeps tracks of pointers to any Vertexes
	std::vector<EnumTypes::Vertex*>* dynamicVertexes;
public:


    /**
     * Constructor
     */
    clipper ();

    /**
     * clipPolygon
     *
     * Clip the polygon with vertex count in and vertices inx/iny
     * against the rectangular clipping region specified by lower-left corner
     * (x0,y0) and upper-right corner (x1,y1). The resulting vertices are
     * placed in outx/outy.
     *
     * The routine should return the vertex count of the polygon
     * resulting from the clipping.
     *
     * @param in the number of vertices in the polygon to be clipped
     * @param inx - x coords of vertices of polygon to be clipped.
     * @param iny - y coords of vertices of polygon to be clipped.
     * @param outx - x coords of vertices of polygon resulting after clipping.
     * @param outy - y coords of vertices of polygon resulting after clipping.
     * @param x0 - x coord of lower left of clipping rectangle.
     * @param y0 - y coord of lower left of clipping rectangle.
     * @param x1 - x coord of upper right of clipping rectangle.
     * @param y1 - y coord of upper right of clipping rectangle.
     *
     * @return number of vertices in the polygon resulting after clipping
     *
     */
    int clipPolygon(int in, const int inx[], const int iny[],
        int outx[], int outy[],
        int x0, int y0, int x1, int y1);

};

#endif
