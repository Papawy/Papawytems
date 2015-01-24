#include "ItemManager.h"

// -- Constructor

ItemManager::ItemManager() { }

// -- Destructor

ItemManager::~ItemManager() { }

// -- Methods

int ItemManager::addItemShema(ItemShema& shema)
{
	std::map<int, ItemShema>::iterator it = m_itemShemaPool.end();
	/*int previous_id = it->first;
	for (it = m_itemShemaPool.begin(); it != m_itemShemaPool.end(); ++it)
	{
		if (it->first != previous_id+1)
		{
			m_itemShemaPool[it->first + 1] = shema;
			return it->first + 1;
		}
		previous_id += 1;
	}*/
	if (m_itemShemaPool.empty())
	{
		m_itemShemaPool[0] = shema;
		return 0;
	}
	--it;
	m_itemShemaPool[it->first + 1] = shema;
	return it->first + 1;
}

bool ItemManager::removeItemShema(int id)
{
	std::map<int, ItemShema>::iterator it = m_itemShemaPool.find(id);
	if (it != m_itemShemaPool.end())
	{
		m_itemShemaPool.erase(id);
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
	/*int previous_id = 0;
	for (it = m_itemPool.begin(); it != m_itemPool.end(); ++it)
	{
		if (it->first != previous_id + 1)
		{
			m_itemPool[previous_id + 1] = item;
			return previous_id + 1;
		}
	}*/
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

ItemShema& ItemManager::accessItemShema(int id)
{
	std::map<int, ItemShema>::iterator it = m_itemShemaPool.find(id);
	if (it != m_itemShemaPool.end())
	{
		return m_itemShemaPool[id];
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

bool ItemManager::itemShemaExist(int id)
{
	if (m_itemShemaPool.find(id) != m_itemShemaPool.end())
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