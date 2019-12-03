#include <cmath>
#include <string>
#include <vector>
#include "Triangle.h"

using namespace std;
using namespace triang;

Point::Point(double x, double y, double z, int nul)
{
	Id = GenerateRunningId(nul);

	X = x;
	Y = y;
	Z = z;
}

Point::Point(double x, double y, double z, bool isAuxiliaryDot)
{
	Id = GenerateRunningId(1);

	IsAuxiliaryDot = isAuxiliaryDot;

	X = x;
	Y = y;
	Z = z;
}

Point::Point(Point* dot, double lengthAfterProjection)
{
	Id = dot->Id;
	IsVisited = dot->IsVisited;
	IsAuxiliaryDot = dot->IsAuxiliaryDot;

	double length = sqrt(pow(dot->X, 2) + pow(dot->Y, 2) + pow(dot->Z, 2));
	double scaleFactor = lengthAfterProjection / length;

	X = scaleFactor * dot->X;
	Y = scaleFactor * dot->Y;
	Z = scaleFactor * dot->Z;
}

Point::~Point()
{
}

int Point::GenerateRunningId(int nul)
{
	static int id = 0;
	if(nul==0)
		id = 0;
	return id++;
}

bool Point::IsCoincidentWith(Point* dot)
{
	return (X == dot->X && Y == dot->Y && Z == dot->Z);
}

Triangle::Triangle(Point* v0, Point* v1, Point* v2)
{
	Id = GenerateRunningId();
	Vertex[0] = v0;
	Vertex[1] = v1;
	Vertex[2] = v2;
}

Triangle::~Triangle()
{
}

int Triangle::GenerateRunningId()
{
	static int id = 0;
	return id++;
}

bool Triangle::HasVertexCoincidentWith(Point* dot)
{
	return Vertex[0]->IsCoincidentWith(dot)
		|| Vertex[1]->IsCoincidentWith(dot)
		|| Vertex[2]->IsCoincidentWith(dot);
}

void Triangle::AssignNeighbors(Triangle* n0, Triangle* n1, Triangle* n2)
{
	Neighbor[0] = n0;
	Neighbor[1] = n1;
	Neighbor[2] = n2;
}

