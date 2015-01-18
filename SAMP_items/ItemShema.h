#ifndef ITEM_SHEMA_H_INCLUDED
#define ITEM_SHEMA_H_INCLUDED

#include <string>

class ItemShema
{
public:
	ItemShema();
	ItemShema(std::string itemName, int itemType, int modelId, int nbrVars);

	// Setters

	void setItemName(std::string itemName);

	void setItemType(int type);

	void setItemModel(int modelId);

	// Accessors

	std::string getItemName();

	int getItemType();

	int getItemModel();

	int getItemNbrVars();

	~ItemShema();

private:
	int m_itemType;

	int m_modelID;

	int m_nbrVars;

	std::string m_itemName;
};

#endif // ITEM_SHEMA_H_INCLUDED