#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <list>
#include <iomanip>
#include <vector>
#include <tuple>
#include "Triangle.h"
#include "Triangulation.h"
using namespace std;
using namespace triang;

	struct point
	{
		float x, y, z;
		int number;
	};

	struct edge
	{
		point p1, p2;
		float length;
	};

	//struct texcoord
	//{
	//	float x, y, z;
	//	int number;
	//};

	struct normal
	{
		float x, y, z;
		int number;
	};

	struct triangle
	{
		point p1, p2, p3;
		normal n1, n2, n3;
		//texcoord tc1, tc2, tc3;
	};

	struct Mesh
	{
		vector<triangle> triangles;
		vector<point> points;
		vector<normal> normals;
		//vector<texcoord> texcoords;
	};

	struct objFile
	{
		vector<Mesh> objects;
		vector <point> points;
		vector<normal> normals;
	};

	float distance(point p1, point p2)
	{
		float res;
		res = sqrtf(powf((p1.x - p2.x), 2) + powf((p1.y - p2.y), 2) + powf((p1.z - p2.z), 2));
		return res;
	}

	float square(triangle tr)
	{
		float res = 0, a, b, c, pp;
		a = distance(tr.p1, tr.p2);
		b = distance(tr.p1, tr.p3);
		c = distance(tr.p3, tr.p2);
		pp = (a + b + c) / 2;
		res = sqrtf(pp * (pp - a) * (pp - b) * (pp - c));
		return res;
	}

	float perimetr(triangle tr)
	{
		float res = 0, a, b, c;
		a = distance(tr.p1, tr.p2);
		b = distance(tr.p1, tr.p3);
		c = distance(tr.p3, tr.p2);
		res = a + b + c;
		return res;
	}

	bool equalpoint(point p1, point p2)
	{
		if ((p1.x == p2.x) && (p1.y == p2.y) && (p1.z == p2.z))
			return true;
		else
			return false;
	}

	point mid(point p1, point p2)
	{
		point res;
		res.x = (p1.x + p2.x) / 2;
		res.y = (p1.y + p2.y) / 2;
		res.z = (p1.z + p2.z) / 2;
		return res;
	}

	point findpoint(vector<point> points, point p)
	{
		bool f = false;
		auto pointit = points.begin();
		while (pointit != points.end())
		{
			if (equalpoint(*pointit, p))
			{
				f = true;
				p.number = pointit->number;
				break;
			}
			pointit++;
		}
		if (f == false)
		{
			p.number = 0;
		}
		return p;
	}

	Mesh addPoint(Mesh object, point p)
	{
		p = findpoint(object.points, p);
		if (p.number == 0)
		{
			p.number = object.points.size() + 1;
			object.points.push_back(p);
		}
		return object;
	}

	vector <Mesh> readobj(string path, vector <Mesh> objects)
	{
		string str;
		string line;
		Mesh object;
		float x, y, z;
		bool objbeg=false;
		int p1, p2, p3, n1, n2, n3, tc1, tc2, tc3, nump = 1, numn = 0, numt = 0, numo=0;
		point p;
		/*texcoord tc;*/
		normal n;
		triangle t;
		ifstream file(path);
		while (getline(file, line))
		{
			if ((line.find("o ")) != -1)
			{
				if (numo > 0)
				{
					objects.push_back(object);
				}
				numo++;
				object = {};
			}
			if ((line.find("v ")) != -1)
			{
				str = line.substr(1, line.size());
				std::istringstream ist(str);
				ist >> x >> y >> z;
				p.x = x;
				p.y = y;
				p.z = z;
				p.number = nump;
				object.points.push_back(p);
				line = "";
				nump++;
			}
			if ((line.find("v ")) != -1)
			{
				str = line.substr(1, line.size());
				std::istringstream ist(str);
				ist >> x >> y >> z;
				p.x = x;
				p.y = y;
				p.z = z;
				p.number = nump;
				object.points.push_back(p);
				line = "";
				nump++;
			}
			if ((line.find("vn ")) != -1)
			{
				str = line.substr(2, line.size());
				std::istringstream ist(str);
				ist >> x >> y >> z;
				n.x = x;
				n.y = y;
				n.z = z;
				n.number = numn + 1;
				object.normals.push_back(n);
				line = "";
				numn++;
			}
			if ((line.find("vt ")) != -1)
			{
				str = line.substr(2, line.size());
				std::istringstream ist(str);
				ist >> x >> y >> z;
				/*tc.x = x;
				tc.y = y;
				tc.z = z;
				tc.number = numt + 1;
				object.texcoords.push_back(tc);*/
				line = "";
				numt++;
			}
			if ((line.find("f ")) != -1)
			{
				str = line.substr(1, line.size());
				if (numn == 0)
				{
					std::istringstream ist(str);
					ist >> p1 >> p2 >> p3;
					t.p1 = object.points.at(p1 - 1);
					t.p2 = object.points.at(p2 - 1);
					t.p3 = object.points.at(p3 - 1);
					object.triangles.push_back(t);
				}
				else
				{
					if (numt == 0)
					{
						std::replace(str.begin(), str.end(), '/', ' ');
						std::istringstream ist(str);
						ist >> p1 >> n1 >> p2 >> n2 >> p3 >> n3;
						t.p1 = object.points.at(p1 - 1);
						t.p2 = object.points.at(p2 - 1);
						t.p3 = object.points.at(p3 - 1);
						t.n1 = object.normals.at(n1 - 1);
						t.n2 = object.normals.at(n2 - 1);
						t.n3 = object.normals.at(n3 - 1);
						object.triangles.push_back(t);
					}
					else
					{
						std::replace(str.begin(), str.end(), '/', ' ');
						std::istringstream ist(str);
						ist >> p1 >> tc1 >> n1 >> p2 >> tc2 >> n2 >> p3 >> tc3 >> n3;
						t.p1 = object.points.at(p1 - 1);
						t.p2 = object.points.at(p2 - 1);
						t.p3 = object.points.at(p3 - 1);
						t.n1 = object.normals.at(n1 - 1);
						t.n2 = object.normals.at(n2 - 1);
						t.n3 = object.normals.at(n3 - 1);/*
						t.tc1 = object.texcoords.at(tc1 - 1);
						t.tc2 = object.texcoords.at(tc2 - 1);
						t.tc3 = object.texcoords.at(tc3 - 1);*/
						object.triangles.push_back(t);
					}
				}
				line = "";
			}
		}
		objects.push_back(object);
		file.close();
		return objects;
	}

	Mesh bisect(Mesh object, float needs)
	{
		point p1m, p2m, p3m, p1, p2, p3;
		triangle t;
		int pos = 0;
		auto triit = object.triangles.begin();
		auto pointit = object.points.begin();
		while (triit != object.triangles.end())
		{
			if (square(*triit) > needs)
			{
				p1 = triit->p1;
				p2 = triit->p2;
				p3 = triit->p3;
				p1m = mid(p1, p2);
				p2m = mid(p3, p2);
				p3m = mid(p1, p3);
				object = addPoint(object, p1m);
				object = addPoint(object, p2m);
				object = addPoint(object, p3m);
				/*pointit = object.points.begin();
				f1=f2=f3 = false;
				while (pointit!=object.points.end())
				{
					if (equalpoint(*pointit,p1m))
					{
						f1 = true;
						p1m.number = pointit->number;
						break;
					}
					if (equalpoint(*pointit, p2m))
					{
						f2 = true;
						p2m.number = pointit->number;
						break;
					}
					if (equalpoint(*pointit, p3m))
					{
						f3 = true;
						p3m.number = pointit->number;
						break;
					}
					pointit++;
				}
				if (f1==false)
				{
					p1m.number = object.points.size()+1;
					object.points.push_back(p1m);
				}
				if (f2==false)
				{
					p2m.number = object.points.size()+1;
					object.points.push_back(p2m);
				}
				if (f3 == false)
				{
					p3m.number = object.points.size()+1;
					object.points.push_back(p3m);
				}*/
				triit->p2 = p1m;
				triit->p3 = p3m;
				t.p1 = p1m;
				t.p2 = p2;
				t.p3 = p2m;
				t.n1 = triit->n1;
				t.n2 = triit->n2;
				t.n3 = triit->n3;
				object.triangles.push_back(t);
				t.p1 = p1m;
				t.p2 = p2m;
				t.p3 = p3m;
				object.triangles.push_back(t);
				t.p1 = p3;
				t.p2 = p2m;
				t.p3 = p3m;
				object.triangles.push_back(t);
				triit = object.triangles.begin();
				triit += pos;
			}
			else
			{
				triit++;
				pos++;
			}
		}
		return object;
	}

	vector<point> triangtopoints(triangle t, float needs)
	{
		vector<point> adp;
		edge edges[3];
		int steps;
		point p, fp;
		float stepx, stepy, stepz, dist;
		edges[0].p1 = t.p1;
		edges[0].p2 = t.p2;
		edges[1].p1 = t.p2;
		edges[1].p2 = t.p3;
		edges[2].p1 = t.p3;
		edges[2].p2 = t.p1;
		for (int i = 0; i < 3; i++)
		{
			edges[i].length = distance(edges[i].p1, edges[i].p2);
			if (edges[i].length > 1.5 * needs)
			{
				steps = (int)edges[i].length / needs;
				stepx = (edges[i].p2.x - edges[i].p1.x) / steps;
				stepy = (edges[i].p2.y - edges[i].p1.y) / steps;
				stepz = (edges[i].p2.z - edges[i].p1.z) / steps;
				for (int j = 0; j <= steps; j++)
				{
					p.x = edges[i].p1.x + stepx * j;
					p.y = edges[i].p1.y + stepy * j;
					p.z = edges[i].p1.z + stepz * j;
					fp = findpoint(adp, p);
					if (fp.number == 0)
						adp.push_back(p);
				}
			}
		}
		return adp;
	}

	Mesh subdivide(Mesh object, float needs)
	{
		edge edges[3];
		point p;
		triangle newtr;
		double x = 0, y = 0, z = 0;
		int p1,p2,p3,n=0,tsize=object.triangles.size();
		auto triit = object.triangles.begin();
		vector<point> adp;
		vector<Point*> dots = vector<Point*>();
		auto pointit = adp.begin();
		while(n<tsize)
		{
			adp.clear();
			adp = triangtopoints(*triit, needs);
			pointit = adp.begin();
			while (pointit != adp.end())
			{
				object = addPoint(object, *pointit);
				p = findpoint(object.points, *pointit);
				pointit->number = p.number;
				pointit++;
			}
			if (adp.size() > 3)
			{
				pointit = adp.begin();
				x = pointit->x;
				y = pointit->y;
				z = pointit->z;
				Point* dot = new Point(x, y, z, 0);
				dots.push_back(dot);
				pointit++;
				while (pointit != adp.end())
				{
					x = pointit->x;
					y = pointit->y;
					z = pointit->z;
					Point* dot = new Point(x, y, z, 1);
					dots.push_back(dot);
					pointit++;
				}
				DelaunayTriangulation triangulation = DelaunayTriangulation();
				vector<tuple<int, int, int>*> mesh = triangulation.GetTriangulationResult(dots);
				dots.clear();
				triit = object.triangles.begin();
				triit += n;
				if (mesh.size() > 0)
				{
					tie(p1, p2, p3) = *mesh[0];
					triit->p1 = adp.at(p1);
					triit->p2 = adp.at(p2);
					triit->p3 = adp.at(p3);
					newtr.n1 = triit->n1;
					newtr.n2 = triit->n2;
					newtr.n3 = triit->n3;
					for (int i = 1; i < mesh.size(); i++)
					{
						tie(p1, p2, p3) = *mesh[i];
						newtr.p1 = adp.at(p1);
						newtr.p2 = adp.at(p2);
						newtr.p3 = adp.at(p3);
						object.triangles.push_back(newtr);
					}
					mesh.clear();
				}
			}
			triit = object.triangles.begin();
			triit += n+1;
			n++;
		}
		return object;
	}

	void outputobj(string path, vector <Mesh> objects)
	{
		path.insert(path.size() - 4, 1, '1');
		ofstream fout(path);
		int num = 1;
		auto object = objects.begin();
		while (object != objects.end())
		{
			fout << "o " <<"object"<<num<< endl;
			num++;
			auto pointit = object->points.begin();
			auto normit = object->normals.begin();
			/*auto texit = object->texcoords.begin();*/
			auto triit = object->triangles.begin();
			while (pointit != object->points.end())
			{
				fout << "v " << pointit->x << " " << pointit->y << " " << pointit->z << endl;
				pointit++;
			}/*
			while (texit != object->texcoords.end())
			{
				fout << "vt " << texit->x << " " << texit->y << " " << texit->z << endl;
				texit++;
			}*/
			while (normit != object->normals.end())
			{
				fout << "vn " << normit->x << " " << normit->y << " " << normit->z << endl;
				normit++;
			}
			while (triit != object->triangles.end())
			{
				if (object->normals.size() == 0)
					fout << "f " << triit->p1.number << " " << triit->p2.number << " " << triit->p3.number << endl;
				else
					fout << "f " << triit->p1.number << "//" << triit->n1.number << " " << triit->p2.number << "//" << triit->n2.number << " " << triit->p3.number << "//" << triit->n3.number << endl;
				triit++;
			}
			object++;
		}
		fout.close();
	}