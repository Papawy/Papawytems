#include "ItemShema.h"

// -- Constructors

ItemShema::ItemShema()
{

}

ItemShema::ItemShema(std::string itemName, int itemType, int modelId) : m_itemName(itemName), m_itemType(itemType), m_modelID(modelId)
{

}

// -- Methods

// Setters

void ItemShema::setItemName(std::string name) { m_itemName = name; }

void ItemShema::setItemType(int type) { m_itemType = type; }

void ItemShema::setItemModel(int modelId) { m_modelID = modelId; }

// Accessors

std::string ItemShema::getItemName() { return m_itemName; }

int ItemShema::getItemType() { return m_itemType; }

int ItemShema::getItemModel() { return m_modelID; }

// -- Destructor

ItemShema::~ItemShema()
{

}