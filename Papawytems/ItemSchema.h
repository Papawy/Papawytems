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

	std::string getItemName() const { return m_itemName; };

	int getItemType() const { return m_itemType; };

	int getItemModel() const { return m_modelID; };

	~ItemSchema();

private:
	int m_itemType;

	int m_modelID;

	std::string m_itemName;
};

bool operator==(const ItemSchema& right, const ItemSchema& left);

#endif // ITEM_Schema_H_INCLUDED