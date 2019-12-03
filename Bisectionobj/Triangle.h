#ifndef TRIANGLE_H
#define TRIANGLE_H

namespace triang
{
	class Point
	{
	private:
		int GenerateRunningId(int nul);
	public:
		int Id = 0;

		// coordinate
		double X, Y, Z;

		bool IsVisited = false;
		bool IsAuxiliaryDot = false;
		Point(double x, double y, double z,int nul );
		Point(double x, double y, double z, bool isAuxiliaryDot);
		Point(Point* dot, double lengthAfterProjection);
		~Point();

		bool IsCoincidentWith(Point* dot);
	};

	class Triangle
	{
	private:
		int GenerateRunningId();
	public:
		int Id = 0;

		// pointers pointing to 3 vertices
		Point* Vertex[3];

		// pointers pointing to 3 neighbors
		Triangle* Neighbor[3];

		Triangle(Point* v0, Point* v1, Point* v2);
		~Triangle();

		bool HasVertexCoincidentWith(Point* dot);
		void AssignNeighbors(Triangle* n0, Triangle* n1, Triangle* n2);
	};

}
#endif