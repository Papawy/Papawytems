#include "ItemSchema.h"

// -- Constructors

ItemSchema::ItemSchema()
{

}

ItemSchema::ItemSchema(std::string itemName, int itemType, int modelId) : m_itemName(itemName), m_itemType(itemType), m_modelID(modelId)
{

}

// -- Methods

// Setters

void ItemSchema::setItemName(std::string name) { m_itemName = name; }

void ItemSchema::setItemType(int type) { m_itemType = type; }

void ItemSchema::setItemModel(int modelId) { m_modelID = modelId; }


// -- Destructor

ItemSchema::~ItemSchema()
{

}

// -- Operator Overloading

bool operator==(const ItemSchema& right, const ItemSchema& left)
{
	if (
		right.getItemModel() == left.getItemModel() &&
		right.getItemName() == left.getItemName() &&
		right.getItemType() == left.getItemType()
		)
	{
		return true;
	}
	else
		return false;
}
