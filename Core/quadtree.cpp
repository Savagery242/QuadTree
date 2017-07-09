#include "quadtree.h"
#include "struct.h"
#include <iostream>

// QUADRANTS::
// 0 == top right
// 1 == top left
// 2 == bottom left
// 3 == bottom right

Quadtree::Quadtree(int level, RECT bounds)
{
	this->level = level;
	this->bounds = bounds;
	this->isSplit = false;
}

Quadtree::~Quadtree()
{
}

void Quadtree::GetLines(std::vector<LINE> &lines)
{
	LINE v(POINT(bounds.x + bounds.width / 2, bounds.y),  POINT(bounds.x + bounds.width / 2, bounds.y + bounds.height));
	LINE h(POINT(bounds.x, bounds.y + bounds.height / 2), POINT(bounds.x + bounds.width, bounds.y + bounds.height / 2));

	lines.push_back(v);
	lines.push_back(h);

	if (isSplit)
	{
		for (int i = 0; i < NUM_NODES; ++i)		
			nodes[i]->GetLines(lines);
	}
}

void Quadtree::Clear()
{
	entities.clear();

	if (!isSplit)
		return;

	for (int i = 0; i < NUM_NODES; ++i)
	{
		if (nodes[i])
		{
			nodes[i]->Clear();
			delete(nodes[i]);
		}
	}
}

void Quadtree::Split()
{
	double subWidth = bounds.width / 2;
	double subHeight = bounds.height / 2;
	double x = bounds.x;
	double y = bounds.y;

	nodes[0] = new Quadtree(level + 1, RECT(x + subWidth, y + subHeight, subWidth, subHeight));
	nodes[1] = new Quadtree(level + 1, RECT(x, y + subHeight, subWidth, subHeight));
	nodes[2] = new Quadtree(level + 1, RECT(x, y, subWidth, subHeight));
	nodes[3] = new Quadtree(level + 1, RECT(x + subWidth, y, subWidth, subHeight));

	isSplit = true;

	std::cout << "Splitting" << std::endl;
}


int Quadtree::GetIndex(const Entity &entity)
{
	POINT location = entity.location;

	if ((location.x >= bounds.x + bounds.width  / 2) &&
		(location.y >= bounds.y + bounds.height / 2))
		return 0;
	if ((location.x <  bounds.x + bounds.width  / 2) &&
		(location.y >= bounds.y + bounds.height / 2))
		return 1;
	if ((location.x <  bounds.x + bounds.width  / 2) &&
		(location.y <  bounds.y + bounds.height / 2))
		return 2;
	if ((location.x >= bounds.x + bounds.width  / 2) &&
		(location.y <  bounds.y + bounds.height / 2))
		return 3;

	return -1;
}

void Quadtree::Insert(const Entity &entity)
{
	// If split, find correct quadrant and insert there
	if (isSplit)
	{
		int index = GetIndex(entity);		
		if (index < 0 || index > NUM_NODES - 1)
		{
			std::cout << "Invalid Index: " << index << std::endl;
			return;
		}

		nodes[index]->Insert(entity);
		return;
	}

	if (ContainsEntity(entity))
		return;	

	// Insert into Entities list
	entities.push_back(&entity);

	// If Entities list is full, split and re-insert
	if (level < MAX_LEVELS && entities.size() > MAX_OBJECTS)
	{
		Split();
		typedef std::vector<const Entity*>::iterator iterator;
		for (iterator it = entities.begin(); it != entities.end(); ++it)			
			Insert(**it);			
		entities.clear();
		return;
	}		
}

// Does the entity list already contain this entity
bool Quadtree::ContainsEntity(const Entity &entity)
{
	for (entIt it = entities.begin(); it != entities.end(); ++it)
	{
		if (*it == &entity)
			return true;
	}

	return false;
}