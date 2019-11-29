#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <list>
#include <iomanip>
#include <vector>
using namespace std;

struct point
{
	float x, y, z;
	int number;
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

float square(triangle tr)
{
	float res=0,a,b,c,pp;
	a = sqrtf(powf((tr.p1.x - tr.p2.x),2)+ powf((tr.p1.y - tr.p2.y), 2)+ powf((tr.p1.z - tr.p2.z), 2));
	b = sqrtf(powf((tr.p1.x - tr.p3.x), 2) + powf((tr.p1.y - tr.p3.y), 2) + powf((tr.p1.z - tr.p3.z), 2));
	c = sqrtf(powf((tr.p3.x - tr.p2.x), 2) + powf((tr.p3.y - tr.p2.y), 2) + powf((tr.p3.z - tr.p2.z), 2));
	pp = (a+b+c) / 2;
	res= sqrtf(pp * (pp - a) * (pp - b) * (pp - c));
	return res;
}

float perimetr(triangle tr)
{
	float res = 0, a, b, c;
	a = sqrtf(powf((tr.p1.x - tr.p2.x), 2) + powf((tr.p1.y - tr.p2.y), 2) + powf((tr.p1.z - tr.p2.z), 2));
	b = sqrtf(powf((tr.p1.x - tr.p3.x), 2) + powf((tr.p1.y - tr.p3.y), 2) + powf((tr.p1.z - tr.p3.z), 2));
	c = sqrtf(powf((tr.p3.x - tr.p2.x), 2) + powf((tr.p3.y - tr.p2.y), 2) + powf((tr.p3.z - tr.p2.z), 2));
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

Mesh readobj(string path, Mesh object)
{
	string str;
	string line;
	float x, y, z;
	int p1, p2, p3, n1, n2, n3, tc1, tc2, tc3, nump=1,numn=0, numt=0;
	point p;
	/*texcoord tc;*/
	normal n;
	triangle t;
	ifstream file(path);
	while (getline(file, line))
	{
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
			n.number = numn+1;
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
				if (numt==0)
				{
					std::replace(str.begin(), str.end(), '/', ' ');
					std::istringstream ist(str);
					ist >> p1 >> n1 >> p2 >> n2 >> p3 >>n3;
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
	file.close();
	return object;
}

Mesh bisect(Mesh object, float needs)
{
	point p1m, p2m, p3m,p1,p2,p3;
	triangle t;
	bool f1,f2,f3;
	int pos=0;
	auto triit = object.triangles.begin();
	auto pointit = object.points.begin();
	while (triit!= object.triangles.end())
	{
		if (square(*triit) > needs)
		{
			p1 = triit->p1;
			p2 = triit->p2;
			p3 = triit->p3;
			p1m = mid(p1, p2);
			p2m = mid(p3, p2);
			p3m = mid(p1, p3);
			pointit = object.points.begin();
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
			}
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
			triit= object.triangles.begin();
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

void outputobj(string path, Mesh object)
{
	path.insert(path.size()-4,1,'1');
	ofstream fout(path);
	auto pointit = object.points.begin();
	auto normit = object.normals.begin();
	/*auto texit = object.texcoords.begin();*/
	auto triit = object.triangles.begin();
	while (pointit != object.points.end())
	{
		fout << "v " << pointit->x << " " << pointit->y << " " << pointit->z << endl;
		pointit++;
	}/*
	while (texit != object.texcoords.end())
	{
		fout << "vt " << texit->x << " " << texit->y << " " << texit->z << endl;
		texit++;
	}*/
	while (normit != object.normals.end())
	{
		fout << "vn " << normit->x << " " << normit->y << " " << normit->z << endl;
		normit++;
	}
	while (triit != object.triangles.end())
	{
		if(object.normals.size()==0)
			fout << "f " << triit->p1.number << " " << triit->p2.number << " " << triit->p3.number << endl;
		else
			fout << "f " << triit->p1.number <<"//"<<triit->n1.number<< " " << triit->p2.number << "//" << triit->n2.number << " " << triit->p3.number << "//" << triit->n3.number << endl;
		triit++;
	}
	fout.close();
}

int main()
{
	std::string path;
	cout << "You can input your file"<<endl;
	cin >> path;
	ifstream file(path);
	float needs=1;
	Mesh object;
	object = readobj(path, object);
	object = bisect(object,needs);
	outputobj(path,object);
}
