#include "CQuadTree.h"
#include "GlobalFunctions.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CRigidbody.h"
#include "CColliderTypeCollisions.h"

CQuadTree::CQuadTree(const SAABB& a_boundary)
    : m_boundary(a_boundary)
    , m_northWest(nullptr)
    , m_northEast(nullptr)
    , m_southWest(nullptr)
    , m_southEast(nullptr)
{
}

CQuadTree::~CQuadTree()
{
    SafeDelete(m_northWest);
    SafeDelete(m_northEast);
    SafeDelete(m_southWest);
    SafeDelete(m_southEast);
}

void CQuadTree::SetBoundary(const SAABB& a_boundary)
{
    m_boundary = a_boundary;
}

const SAABB& CQuadTree::GetBoundary() const
{
    return m_boundary;
}

bool CQuadTree::Insert(CGameObject* a_object)
{
    if (a_object == nullptr)
    {
        return false;
    }

    // Ignore objects that do not belong in this quad tree
    if (!m_boundary.ContainsPoint(a_object->GetComponent<CTransform>()->GetPosition()))
    {
        return false;
    }

    // If there is space in this quad tree, add the object here
    if (m_elements.size() < m_nodeCapacity)
    {
        m_elements.push_back(a_object);
        return true;
    }

    // Otherwise, subdivide and then add the point to whichever node will accept it
    if (m_northWest == nullptr)
    {
        Subdivide();
    }

    if (m_northWest->Insert(a_object))
    {
        return true;
    }
    if (m_northEast->Insert(a_object))
    {
        return true;
    }
    if (m_southWest->Insert(a_object))
    {
        return true;
    }
    if (m_southEast->Insert(a_object))
    {
        return true;
    }

    // Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
    return false;
}

void CQuadTree::Subdivide()
{
    m_northWest = &CQuadTree(SAABB(m_boundary.m_center + SVector3(-m_boundary.m_halfWidths * 0.5f, -m_boundary.m_halfWidths * 0.5f), m_boundary.m_halfWidths * 0.25f));
    m_northEast = &CQuadTree(SAABB(m_boundary.m_center + SVector3(-m_boundary.m_halfWidths * 0.5f, m_boundary.m_halfWidths * 0.5f), m_boundary.m_halfWidths * 0.25f));
    m_southWest = &CQuadTree(SAABB(m_boundary.m_center + SVector3(m_boundary.m_halfWidths * 0.5f, -m_boundary.m_halfWidths * 0.5f), m_boundary.m_halfWidths * 0.25f));
    m_southEast = &CQuadTree(SAABB(m_boundary.m_center + SVector3(m_boundary.m_halfWidths * 0.5f, m_boundary.m_halfWidths * 0.5f), m_boundary.m_halfWidths * 0.25f));

    for (int i = m_elements.size(); i > 0; i--)
    {
        if (m_northWest->GetBoundary().ContainsPoint(m_elements.at(i)->GetComponent<CTransform>()->GetPosition()))
        {
            m_northWest->Insert(m_elements.at(i));
            m_elements.pop_back();
        }

        if (m_northEast->GetBoundary().ContainsPoint(m_elements.at(i)->GetComponent<CTransform>()->GetPosition()))
        {
            m_northEast->Insert(m_elements.at(i));
            m_elements.pop_back();
        }

        if (m_southWest->GetBoundary().ContainsPoint(m_elements.at(i)->GetComponent<CTransform>()->GetPosition()))
        {
            m_northWest->Insert(m_elements.at(i));
            m_elements.pop_back();
        }

        if (m_southEast->GetBoundary().ContainsPoint(m_elements.at(i)->GetComponent<CTransform>()->GetPosition()))
        {
            m_northWest->Insert(m_elements.at(i));
            m_elements.pop_back();
        }
    }
}

// Find all points that appear within a range
std::vector<CGameObject*> CQuadTree::QueryRange(SAABB a_range)
{
    // Prepare an array of results
    std::vector<CGameObject*> elementsInRange;

    // Automatically abort if the range does not intersect this quad
    if (m_boundary.Intersects(a_range))
    {
        return elementsInRange;
    }

    // Check objects at this quad level
    for (int p = 0; p < m_elements.size(); p++)
    {
        if (a_range.ContainsPoint(m_elements.at(p)->GetComponent<CTransform>()->GetPosition()))
        {
            elementsInRange.push_back(m_elements.at(p));
            break;
        }
    }

    // Terminate here, if there are no children
    if (m_northWest == nullptr)
    {
        return elementsInRange;
    }

    // Otherwise, add the points from the children
    std::vector<CGameObject*> tmp;
    tmp = m_northWest->QueryRange(a_range);
    for (size_t i = 0; i < tmp.size(); i++)
    {
        elementsInRange.push_back(tmp.at(i));
    }
    tmp = m_northEast->QueryRange(a_range);
    for (size_t i = 0; i < tmp.size(); i++)
    {
        elementsInRange.push_back(tmp.at(i));
    }
    tmp = m_southWest->QueryRange(a_range);
    for (size_t i = 0; i < tmp.size(); i++)
    {
        elementsInRange.push_back(tmp.at(i));
    }
    tmp = m_southEast->QueryRange(a_range);
    for (size_t i = 0; i < tmp.size(); i++)
    {
        elementsInRange.push_back(tmp.at(i));
    }
    return elementsInRange;
}

void CQuadTree::Update()
{
    if (m_elements.size() > 0)
    {
        for (auto *element : m_elements)
        {
            for (auto *other : m_elements)
            {
                if (other != element)
                {
                    CCollider* collider1 = element->GetComponent<CCollider>();
                    CCollider* collider2 = other->GetComponent<CCollider>();
                    if (collider1 != nullptr && collider2 != nullptr)
                    {
                        switch (collider1->GetType())
                        {
                        case EColliderType::AABB:
                            switch (collider1->GetType())
                            {
                            case EColliderType::AABB:
                                if (CColliderTypeCollisions::IntersectBoxBox(collider1->GetAABB(), collider2->GetAABB()))
                                {
                                    _beep(1000, 300);
                                }
                                break;
                            case EColliderType::BCirle:
                                if (CColliderTypeCollisions::IntersectBoxCircle(collider1->GetAABB(), collider2->GetBCircle()))
                                {
                                    _beep(2000, 300);
                                }
                                break;
                            default:
                                break;
                            }
                            break;
                        case EColliderType::BCirle:
                            switch (collider1->GetType())
                            {
                            case EColliderType::AABB:
                                if (CColliderTypeCollisions::IntersectCircleBox(collider1->GetBCircle(), collider2->GetAABB()))
                                {
                                    _beep(3000, 300);
                                }
                                break;
                            case EColliderType::BCirle:
                                if (CColliderTypeCollisions::IntersectCircleCircle(collider1->GetBCircle(), collider2->GetBCircle()))
                                {
                                    _beep(4000, 300);
                                }
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            element->Update();
        }
    }
    if (m_northWest != nullptr)
    {
        m_northWest->Update();
    }
    if (m_northEast != nullptr)
    {
        m_northEast->Update();
    }
    if (m_southWest != nullptr)
    {
        m_southWest->Update();
    }
    if (m_southEast != nullptr)
    {
        m_southEast->Update();
    }
}
