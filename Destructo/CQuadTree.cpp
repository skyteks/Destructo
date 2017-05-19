#include "CQuadTree.h"

CQuadTree::CQuadTree(SAABB a_boundary)
	: m_boundary(a_boundary)
	, m_northWest(nullptr)
	, m_northEast(nullptr)
	, m_southWest(nullptr)
	, m_southEast(nullptr)
{
	m_elements = std::vector<CGameObject*>();
}

CQuadTree::~CQuadTree()
{
	SafeDelete(m_northWest);
	SafeDelete(m_northEast);
	SafeDelete(m_southWest);
	SafeDelete(m_southEast);
}

SAABB CQuadTree::GetBoundary()
{
	return m_boundary;
}

bool CQuadTree::Insert(CGameObject* a_object)
{
	// Ignore objects that do not belong in this quad tree
	if (!m_boundary.ContainsPoint(a_object->GetPosition()))
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
	m_northWest = &CQuadTree(SAABB(m_boundary.GetCenter() + SVector3(-m_boundary.GetHalfWidths() * 0.5f, -m_boundary.GetHalfWidths() * 0.5f), m_boundary.GetHalfWidths() * 0.25f));
	m_northEast = &CQuadTree(SAABB(m_boundary.GetCenter() + SVector3(-m_boundary.GetHalfWidths() * 0.5f, m_boundary.GetHalfWidths() * 0.5f), m_boundary.GetHalfWidths() * 0.25f));
	m_southWest = &CQuadTree(SAABB(m_boundary.GetCenter() + SVector3(m_boundary.GetHalfWidths() * 0.5f, -m_boundary.GetHalfWidths() * 0.5f), m_boundary.GetHalfWidths() * 0.25f));
	m_southEast = &CQuadTree(SAABB(m_boundary.GetCenter() + SVector3(m_boundary.GetHalfWidths() * 0.5f, m_boundary.GetHalfWidths() * 0.5f), m_boundary.GetHalfWidths() * 0.25f));

	for (int i = m_elements.size(); i > 0; i--)
	{
		if (m_northWest->GetBoundary().ContainsPoint(m_elements.at(i)->GetPosition()))
		{
			m_northWest->Insert(m_elements.at(i));
			m_elements.pop_back();
		}

		if (m_northEast->GetBoundary().ContainsPoint(m_elements.at(i)->GetPosition()))
		{
			m_northEast->Insert(m_elements.at(i));
			m_elements.pop_back();
		}

		if (m_southWest->GetBoundary().ContainsPoint(m_elements.at(i)->GetPosition()))
		{
			m_northWest->Insert(m_elements.at(i));
			m_elements.pop_back();
		}

		if (m_southEast->GetBoundary().ContainsPoint(m_elements.at(i)->GetPosition()))
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
	if (m_boundary.intersectsAABB(a_range))
	{
		return elementsInRange;
	}

	// Check objects at this quad level
	for (int p = 0; p < m_elements.size(); p++)
	{
		if (a_range.ContainsPoint(m_elements.at(p)->GetPosition()))
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
	for (int i = 0; i < tmp.size(); i++)
	{
		elementsInRange.push_back(tmp.at(i));
	}
	tmp = m_northEast->QueryRange(a_range);
	for (int i = 0; i < tmp.size(); i++)
	{
		elementsInRange.push_back(tmp.at(i));
	}
	tmp = m_southWest->QueryRange(a_range);
	for (int i = 0; i < tmp.size(); i++)
	{
		elementsInRange.push_back(tmp.at(i));
	}
	tmp = m_southEast->QueryRange(a_range);
	for (int i = 0; i < tmp.size(); i++)
	{
		elementsInRange.push_back(tmp.at(i));
	}
	return elementsInRange;
}

void CQuadTree::Update()
{
	if (m_elements.size() > 0)
	{
		for (auto &element : m_elements)
		{
			for (auto &other : m_elements)
			{
				if (other != element)
				{
					if (element->GetCircleCollider() != nullptr && other->GetCircleCollider() != nullptr &&
						element->GetCircleCollider()->Intersects(*other->GetCircleCollider()))
					{
						int a = 1;
					}
				}
				if (element->GetRigidbody() != nullptr)
				{
					element->GetRigidbody()->Update(element);
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
