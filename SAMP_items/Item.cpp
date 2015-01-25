#include "Item.h"

// -- Constructors

Item::Item()
{
	m_schema = nullptr;
}

Item::Item(ItemSchema& Schema)
{
	m_schema = &Schema;

	m_name = m_schema->getItemName();
}

Item::Item(ItemSchema& Schema, ObjectPosition position)
{
	m_schema = &Schema;
	m_position = position;

	m_name = m_schema->getItemName();

}

Item::Item(const Item& other)
{
	m_schema = other.m_schema;
}

// -- Methods

// Setters

void Item::setPosition(float posx, float posy, float posz)
{
	m_position.px = posx;
	m_position.py = posy;
	m_position.pz = posz;
}

void Item::setPosition(ObjectPosition position)
{
	m_position = position;
}

void Item::setRotation(float rotx, float roty, float rotz)
{
	m_position.rx = rotx;
	m_position.ry = roty;
	m_position.rz = rotz;
}

void Item::setName(std::string name)
{
	m_name = name;
}

bool Item::setVar(std::string varName, int value)
{
	std::map<std::string, int>::iterator it = m_vars.find(varName);
	if (it != m_vars.end())
	{
		m_vars[varName] = value;
		return true;
	}
	else
	{
		return false;
	}
}

void Item::setDefaultName()
{
	m_name = m_schema->getItemName();
}

void Item::setDrawDistance(float dist)
{
	m_drawDist = dist;
}

// Accessors

ObjectPosition& Item::getPosition()
{
	return m_position;
}

int Item::getVar(std::string varName)
{
	std::map<std::string, int>::iterator it = m_vars.find(varName);
	if (it != m_vars.end())
	{
		return m_vars[varName];
	}
	else
	{
		throw - 1;
	}
}

std::string Item::getName()
{
	if (m_name.size() < 0)
		return m_schema->getItemName();
	else
		return m_name;
}

ItemSchema& Item::getSchema()
{
	return *m_schema;
}

int Item::getObjectID()
{
	return m_gtaObjectId;
}

// --

bool Item::Show()
{
	if (m_shown != true)
	{
		m_gtaObjectId = CreateObject(m_schema->getItemModel(), m_position.px, m_position.py, m_position.pz, m_position.rx, m_position.ry, m_position.rz, m_drawDist);
		m_shown = true;
		return true;
	}
	else
		return false;

}

bool Item::Hide()
{
	if (m_shown != false)
	{
		DestroyObject(m_gtaObjectId);
		m_gtaObjectId = -1;
		m_shown = false;
		return true;
	}
	else
		return true;

}

bool Item::createVar(std::string varName, int value)
{
	std::map<std::string, int>::iterator it = m_vars.find(varName);
	if (it == m_vars.end())
	{
		m_vars[varName] = value;
		return true;
	}
	else
	{
		return false;
	}
}

bool Item::removeVar(std::string varName)
{
	std::map<std::string, int>::iterator it = m_vars.find(varName);
	if (it != m_vars.end())
	{
		m_vars.erase(varName);
		return true;
	}
	else
	{
		return false;
	}
}

bool Item::isVariableExist(std::string varName)
{
	std::map<std::string, int>::iterator it = m_vars.find(varName);
	if (it != m_vars.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Item::isShown()
{
	return m_shown;
}

// -- Destructor

Item::~Item() { }