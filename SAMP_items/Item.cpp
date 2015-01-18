#include "Item.h"

// -- Constructors

Item::Item(ItemShema& shema)
{
	m_shema = &shema;

	m_vars.resize(m_shema->getItemNbrVars());
}

Item::Item(ItemShema& shema, ObjectPosition position)
{
	m_shema = &shema;
	m_position = position;

	m_vars.resize(m_shema->getItemNbrVars());
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

void Item::setVar(int varID, int value)
{
	if (!inRange(varID, 0, m_vars.size()))
		throw - 1;
	else
	{
		m_vars[varID] = value;
	}
}

// Accessors

ObjectPosition& Item::getPosition()
{
	return m_position;
}

int Item::getVar(int varID)
{
	if (!inRange(varID, 0, m_vars.size()))
		throw - 1;
	else
	{
		return m_vars[varID];
	}
}

ItemShema& Item::getShema()
{
	return *m_shema;
}

// -- Destructor

Item::~Item() { }