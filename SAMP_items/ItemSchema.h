#ifndef ITEM_Schema_H_INCLUDED
#define ITEM_Schema_H_INCLUDED

#include <string>

class ItemSchema
{
public:
	ItemSchema();
	ItemSchema(std::string itemName, int itemType, int modelId);

	// Setters

	void setItemName(std::string itemName);

	void setItemType(int type);

	void setItemModel(int modelId);

	// Accessors

	std::string getItemName();

	int getItemType();

	int getItemModel();

	~ItemSchema();

private:
	int m_itemType;

	int m_modelID;

	std::string m_itemName;
};

#endif // ITEM_Schema_H_INCLUDED