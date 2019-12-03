#include <iostream>
#include"Mesh.h"
using namespace std;
int main()
{
	std::string path;
	cout << "You can input your file"<<endl;
	cin >> path;
	ifstream file(path);
	float needs=0.5;
	vector<Mesh> objects;
	objects = readobj(path, objects);
	auto object = objects.begin();
	while (object != objects.end())
	{
		*object = subdivide(*object, needs);
		object++;
	}
	outputobj(path,objects);
}

