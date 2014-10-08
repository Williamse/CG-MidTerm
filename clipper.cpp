//
//  clipper.cpp
//
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//Modified By Emanuel Williams - For Computer graphics 

#include "clipper.h"

/**
 * Simple class that performs clipping
 *
 */

/**
 * Constructor
 */
clipper::clipper ()
{
	
}


/*
*Creates a Clipping window
*Input :
*	BottomLeft = Vertex of the bottom left part of the window
*	TopRight = Vertex of the top Right portion
*Outputs a vector where:
*	Index 0 = Left
*	Index 1 = Top
*	Index 2 = Right
*	Index 3 = Bottom
*/
std::vector<EnumTypes::Line*>* clipper::GenerateClipWindow(EnumTypes::Vertex* BottomLeft, EnumTypes::Vertex* TopRight)
{
	
	std::vector<EnumTypes::Line*>* ClipWindow = new std::vector<EnumTypes::Line*>();

	//Generate missing vertexes
	EnumTypes::Vertex* TopLeft = new EnumTypes::Vertex();
	TopLeft->x = BottomLeft->x;
	TopLeft->y = TopRight->y;

	EnumTypes::Vertex* BottomRight = new EnumTypes::Vertex();
	BottomRight->x = TopRight->x;
	BottomRight->y = BottomLeft->y;

	dynamicVertexes->push_back(TopLeft);
	dynamicVertexes->push_back(BottomRight);

	//Genereate Line
	EnumTypes::Line* LeftLine = new EnumTypes::Line(TopLeft, BottomLeft, true);
	EnumTypes::Line* RightLine = new EnumTypes::Line(BottomRight, TopRight, true);
	EnumTypes::Line* BottomLine = new EnumTypes::Line(BottomLeft, BottomRight, true);
	EnumTypes::Line* TopLine = new EnumTypes::Line(TopRight, TopLeft, true);

	//Add lines
	ClipWindow->push_back(LeftLine);
	ClipWindow->push_back(TopLine);
	ClipWindow->push_back(RightLine);
	ClipWindow->push_back(BottomLine);

	return ClipWindow;
}

/**
*
*
* @param testVertex The vertex being tested
* @param ClipBoundry - The line to use to determine if
*
* @return True If the test vertex is inside false otherwise
*
*/
bool clipper::Inside(EnumTypes::Vertex testVertex, EnumTypes::Line ClipBoundry)
{
	if (ClipBoundry.BType == EnumTypes::South)
	{
		if (testVertex.y >= ClipBoundry.Start->y) return true;
	}
	if (ClipBoundry.BType == EnumTypes::North)
	{
		if (testVertex.y <= ClipBoundry.Start->y) return true;
	}
	if (ClipBoundry.BType == EnumTypes::East)
	{
		if (testVertex.x <= ClipBoundry.End->x) return true;
	}
	if (ClipBoundry.BType == EnumTypes::West)
	{
		if (testVertex.x >= ClipBoundry.End->x) return true;
	}
	return false;
}

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
int clipper::clipPolygon(int in, const float inx[], const float iny[],
                float outx[], float outy[],
		float x0, float y0, float x1, float y1)
{
	//Holds all dynamic memory here
	this->dynamicVertexes = new std::vector<EnumTypes::Vertex*>();

	std::vector<EnumTypes::Line*>* ClippingWindow;
	std::vector<EnumTypes::Vertex> vertacies = std::vector<EnumTypes::Vertex>();
	std::vector<EnumTypes::Vertex> outputVertacies = std::vector<EnumTypes::Vertex>();

	//Generate bottmleft and topright vertacies
	EnumTypes::Vertex BottomLeft = EnumTypes::Vertex();
	EnumTypes::Vertex TopRight = EnumTypes::Vertex();

	BottomLeft.x = x0;
	BottomLeft.y = y0;
	TopRight.x = x1;
	TopRight.y = y1;

	//First lets construct the vertacies based on what we have been passed
	for (int c = 0; c < in; c++)
	{
		//Create the vertex
		EnumTypes::Vertex *temp = new EnumTypes::Vertex();
		temp->x = inx[c];
		temp->y = iny[c];
		
		//Push Vertex
		vertacies.push_back(*temp);
		dynamicVertexes->push_back(temp);

	}
	
	
	//Now lets generate all of the clipping window edges
	ClippingWindow = GenerateClipWindow(&BottomLeft, &TopRight);

	//Lets clip the polygon
	//Left
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(0));
	SwapOutputInput(&vertacies, &outputVertacies);
	outputVertacies.clear();
	//Top
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(1));
	SwapOutputInput(&vertacies, &outputVertacies);
	outputVertacies.clear();
	//Right
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(2));
	SwapOutputInput(&vertacies, &outputVertacies);
	outputVertacies.clear();
	//Bottom
	ClipSide(&outputVertacies, vertacies, ClippingWindow->at(3));

	//Add the elements to the output vertacies
	for (int z = 0; z < outputVertacies.size(); z++)
	{
		outx[z] = outputVertacies.at(z).x;
		outy[z] = outputVertacies.at(z).y;
	}

	//Take care of the crazy amount of dynamic memory I used
	for (int d = 0; d < dynamicVertexes->size(); d++)
	{
		delete dynamicVertexes->at(d);
		dynamicVertexes->at(d) = NULL;
	}
	delete dynamicVertexes;
	dynamicVertexes = NULL;
	for (int j = 0; j < ClippingWindow->size(); j++)
	{
		delete ClippingWindow->at(j);
		ClippingWindow->at(j) = NULL;
	}
	delete ClippingWindow;
	ClippingWindow = NULL;

	return outputVertacies.size();  // should return number of vertices in clipped poly.
}

/*
* Adds the given vertex to the given Vertex Array
*/
void clipper::addVertexOutput(EnumTypes::Vertex* newVertex, std::vector<EnumTypes::Vertex>* outVertexArr)
{
	outVertexArr->push_back(*newVertex);
}

/*
* Swap the input and output vectors unless we are dealing with a line
*/
void clipper::SwapOutputInput(std::vector<EnumTypes::Vertex>* input, std::vector<EnumTypes::Vertex>* output)
{
	int input_length = input->size();
	int output_length = output->size();

	//In case of a line
	if (input_length == 2 && output_length == 3)
	{

		input->at(0).x = output->at(0).x;
		input->at(0).y = output->at(0).y;
		if (output->at(0).x == output->at(1).x) 
		{
			input->at(1).x = output->at(2).x;
			input->at(1).y = output->at(2).y;
		}
		else                    
		{
			input->at(1).x = output->at(1).x;
			input->at(1).y = output->at(2).y;
		}
	}
	//Simply swap the vectors
	else
	{
		input->swap(*output);
	}
}

/*
* Returns the intersection point of a line 
* and another line.
* testLine - The line that intersects another
* ClipBoundry - The line that intersects the test line
  intersectPt - Pointer where the result of the intersection should go.
*/
void clipper::Intersect(EnumTypes::Line testLine, EnumTypes::Line ClipBoundry, EnumTypes::Vertex  *intersectPt)
{
	//Horizontal Edge
	if (ClipBoundry.Start->y == ClipBoundry.End->y)     
	{
		intersectPt->y = ClipBoundry.Start->y;
		intersectPt->x = testLine.Start->x + (ClipBoundry.Start->y - testLine.Start->y) *
			(testLine.End->x - testLine.Start->x)/(testLine.End->y -testLine.Start->y); // Vertical
	}
	//Vertical Edge
	else {
		intersectPt->x = ClipBoundry.Start->x;
		intersectPt->y = testLine.Start->y + (ClipBoundry.Start->x -testLine.Start->x)*
			(testLine.End->y - testLine.Start->y) / (testLine.End->x - testLine.Start->x);
	}
}



/*
* Implementation of the clipping algortihim
* outputVertexes - The vertexes that will be output
  inputVertacies - The vertacies passed into the algorithim
  Edge - The edge we are clipping on
*/
void clipper::ClipSide(std::vector<EnumTypes::Vertex>* outputVertexes, std::vector<EnumTypes::Vertex> inputVertacies, EnumTypes::Line* Edge)
{
	//Each interation update the start vertex, end, and intersection of the given bvetacie and the edge
	EnumTypes::Vertex start, end, intersection;

	//Get the last vertacie
	if (inputVertacies.size() != 0)
	{
		start = inputVertacies.at(inputVertacies.size() - 1);
	}

	//Loop through all of the input vertacies
	for (int x = 0; x < inputVertacies.size(); x++)
	{
		end = inputVertacies.at(x);

		//If the start point is inside
		if (Inside(end, *Edge))
		{
			if (Inside(start, *Edge))
			{
				addVertexOutput(&end, outputVertexes);
			}
			else
			{
				EnumTypes::Line *tLine = new EnumTypes::Line(&start, &end, true);
				Intersect(*tLine, *Edge, &intersection);
				delete tLine;
				addVertexOutput(&intersection, outputVertexes);
				addVertexOutput(&end, outputVertexes);
			}
		}
		else
		{
			if (Inside(start, *Edge))
			{
				EnumTypes::Line *tLine = new EnumTypes::Line(&start, &end, true);
				Intersect(*tLine, *Edge, &intersection);
				delete tLine;
				addVertexOutput(&intersection, outputVertexes);
			}
		}
		start = end;
	}
}