#ifndef ITEM_MANAGER_H_INCLUDED
#define ITEM_MANAGER_H_INCLUDED

#include <map>

#include "Item.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	int addItemShema(ItemShema& shema);
	bool removeItemShema(int id);

	int addItem(Item& item);
	bool removeItem(int id);

	ItemShema& accessItemShema(int id);

	Item& accessItem(int id);

	bool itemShemaExist(int id);

	bool itemExist(int id);

private:
	std::map<int, ItemShema> m_itemShemaPool;
	std::map<int, Item>	m_itemPool;

};

#endif // ITEM_MANAGER_H_INCLUDED
