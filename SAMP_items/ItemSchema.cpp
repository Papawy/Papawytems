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

// Accessors

std::string ItemSchema::getItemName() { return m_itemName; }

int ItemSchema::getItemType() { return m_itemType; }

int ItemSchema::getItemModel() { return m_modelID; }

// -- Destructor

ItemSchema::~ItemSchema()
{

}