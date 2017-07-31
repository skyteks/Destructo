#pragma once
#include <vector>

#include "CGameObject.h"
#include "SAABB.h"


class CQuadTree
{
public:

    CQuadTree(const SAABB& a_boundary);

    ~CQuadTree();

    void SetBoundary(const SAABB& a_boundary);
    const SAABB& GetBoundary() const;
    bool Insert(CGameObject* a_object);
    void Subdivide();
    std::vector<CGameObject*> QueryRange(SAABB a_range);

    void Update();

private:
    //Elements-storage size indicator
    static const size_t m_nodeCapacity = 4;

    SAABB m_boundary;

    //Elements in this quad tree node
    std::vector<CGameObject*> m_elements;

    //Children
    CQuadTree* m_northWest;
    CQuadTree* m_northEast;
    CQuadTree* m_southWest;
    CQuadTree* m_southEast;
};

