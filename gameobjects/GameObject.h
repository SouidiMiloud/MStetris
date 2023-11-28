#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"../Global.h"
#include<vector>


class GameObject
{
public:
	GameObject();
	~GameObject();

	void setup();
	virtual void render();
	void fillIndices(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);
	void fillIndices(unsigned int v1, unsigned int v2, unsigned int v3);
	void addVertex(Position pos);
	int getVerticesSize();

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	std::vector<Position> vertices;
	std::vector<unsigned int> indices;
};

#endif // !GAMEOBJECT_H
