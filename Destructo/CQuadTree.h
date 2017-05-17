#pragma once
#include <vector>

#include "CGameObject.h"
#include "SAABB.h"


class CQuadTree
{
public:
	CQuadTree(SAABB a_boundary);

	~CQuadTree();
	SAABB GetBoundary();
	bool Insert(CGameObject* a_object);
	void Subdivide();
	std::vector<CGameObject*> QueryRange(SAABB a_range);

private:
	//Elements-storage size indicator
	static const int m_nodeCapacity = 4;

	SAABB m_boundary;

	//Elements in this quad tree node
	std::vector<CGameObject*> m_elements;
	
	//Children
	CQuadTree* m_northWest;
	CQuadTree* m_northEast;
	CQuadTree* m_southWest;
	CQuadTree* m_southEast;
};

