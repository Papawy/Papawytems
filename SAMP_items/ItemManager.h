#ifndef ITEM_MANAGER_H_INCLUDED
#define ITEM_MANAGER_H_INCLUDED

#include <map>

#include "Item.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	int addItemSchema(ItemSchema& Schema);
	bool removeItemSchema(int id);

	int addItem(Item& item);
	bool removeItem(int id);

	ItemSchema& accessItemSchema(int id);

	Item& accessItem(int id);

	bool itemSchemaExist(int id);

	bool itemExist(int id);

private:
	std::map<int, ItemSchema> m_itemSchemaPool;
	std::map<int, Item>	m_itemPool;

};

#endif // ITEM_MANAGER_H_INCLUDED
