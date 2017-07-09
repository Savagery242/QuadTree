#pragma once

#include <vector>
#include "struct.h"
#include "entity.h"

#define NUM_NODES 4

typedef std::vector<const Entity*>::iterator entIt;

class Quadtree
{	

private:

	const int MAX_OBJECTS = 2;
	const int MAX_LEVELS = 5;

private:

	int level;
	std::vector<const Entity*> entities;
	RECT bounds;
	Quadtree* nodes[4];
	bool isSplit;

public:

	Quadtree(int level, RECT bounds);
	~Quadtree();

	void Clear();
	void Split();
	int GetIndex(const Entity &entity);
	void Insert(const Entity &entity);
	void GetLines(std::vector<LINE> &lines);

private:

	bool ContainsEntity(const Entity &entity);

};