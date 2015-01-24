#ifndef ITEM_SHEMA_H_INCLUDED
#define ITEM_SHEMA_H_INCLUDED

#include <string>

class ItemShema
{
public:
	ItemShema();
	ItemShema(std::string itemName, int itemType, int modelId);

	// Setters

	void setItemName(std::string itemName);

	void setItemType(int type);

	void setItemModel(int modelId);

	// Accessors

	std::string getItemName();

	int getItemType();

	int getItemModel();

	~ItemShema();

private:
	int m_itemType;

	int m_modelID;

	std::string m_itemName;
};

#endif // ITEM_SHEMA_H_INCLUDED