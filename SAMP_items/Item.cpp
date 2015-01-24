#include "Item.h"

// -- Constructors

Item::Item()
{
	m_shema = nullptr;
}

Item::Item(ItemShema& shema)
{
	m_shema = &shema;

	m_name = m_shema->getItemName();
}

Item::Item(ItemShema& shema, ObjectPosition position)
{
	m_shema = &shema;
	m_position = position;

	m_name = m_shema->getItemName();

}

Item::Item(const Item& other)
{
	m_shema = other.m_shema;
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
		return m_shema->getItemName();
	else
		return m_name;
}

ItemShema& Item::getShema()
{
	return *m_shema;
}

// --

void Item::Show()
{

}

void Item::Hide()
{

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

void Item::setDefaultName()
{
	m_name = m_shema->getItemName();
}

// -- Destructor

Item::~Item() { }