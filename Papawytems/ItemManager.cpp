#include "ItemManager.h"

// -- Constructor

ItemManager::ItemManager() { }

// -- Destructor

ItemManager::~ItemManager() { }

// -- Methods

int ItemManager::addItemSchema(ItemSchema& Schema)
{
	std::map<int, ItemSchema>::iterator it = m_itemSchemaPool.end();
	if (m_itemSchemaPool.empty())
	{
		m_itemSchemaPool[0] = Schema;
		return 0;
	}
	--it;
	m_itemSchemaPool[it->first + 1] = Schema;
	return it->first + 1;
}

bool ItemManager::removeItemSchema(int id)
{
	std::map<int, ItemSchema>::iterator it = m_itemSchemaPool.find(id);
	if (it != m_itemSchemaPool.end())
	{
		m_itemSchemaPool.erase(id);
		return true;
	}
	else
	{
		return false;
	}
}

// -

int ItemManager::addItem(Item& item)
{
	std::map<int, Item>::iterator it = m_itemPool.end();
	if (m_itemPool.empty())
	{
		m_itemPool[0] = item;
		return 0;
	}
	--it;
	m_itemPool[it->first + 1] = item;
	return it->first + 1;
}

bool ItemManager::removeItem(int id)
{
	std::map<int, Item>::iterator it = m_itemPool.find(id);
	if (it != m_itemPool.end())
	{
		m_itemPool.erase(id);
		return true;
	}
	else
	{
		return false;
	}
}

// -

ItemSchema& ItemManager::accessItemSchema(int id)
{
	std::map<int, ItemSchema>::iterator it = m_itemSchemaPool.find(id);
	if (it != m_itemSchemaPool.end())
	{
		return m_itemSchemaPool[id];
	}
	else
	{
		throw -1;
	}
}

Item& ItemManager::accessItem(int id)
{
	std::map<int, Item>::iterator it = m_itemPool.find(id);
	if (it != m_itemPool.end())
	{
		return m_itemPool[id];
	}
	else
	{
		throw - 1;
	}
}

bool ItemManager::itemSchemaExist(int id)
{
	if (m_itemSchemaPool.find(id) != m_itemSchemaPool.end())
		return true;
	else
		return false;
}

bool ItemManager::itemExist(int id)
{
	if (m_itemPool.find(id) != m_itemPool.end())
		return true;
	else
		return false;
}

int ItemManager::getMaxItems()
{
	return m_itemPool.size();
}
