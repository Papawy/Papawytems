#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <map>

#include <sampgdk/a_objects.h>

#include "Utils.h"

#include "ItemSchema.h"

class Item
{
public:
	Item();
	Item(ItemSchema& Schema);
	Item(ItemSchema& Schema, ObjectPosition position);

	Item(const Item& other);
	// I add it if it's requested
	/*Item(ItemSchema& Schema,
	float posX,
	float posY,
	float posZ,

	float rotX,
	float rotY,
	float rotZ);*/

	// Setters

	void setPosition(float posX, float posY, float posZ);
	void setPosition(ObjectPosition position);

	void setRotation(float rotX, float rotY, float rotZ);

	void setName(std::string name);

	bool setVar(std::string varName, int value);

	void setDefaultName();

	void setDrawDistance(float dist);

	// Accessors

	ObjectPosition& getPosition();

	int getVar(std::string varName);

	std::string getName();

	ItemSchema& getSchema();

	int getObjectID();

	// --

	bool Show();
	bool Hide();

	bool createVar(std::string varName, int value = 0);
	bool removeVar(std::string varName);
	bool isVariableExist(std::string varName);

	bool isShown();

	~Item();

private:
	ItemSchema *m_schema;

	std::string m_name;

	std::map<std::string, int> m_vars;
	
	ObjectPosition m_position;

	bool m_shown;

	int m_gtaObjectId;

	float m_drawDist;
};
#endif // ITEM_H_INCLUDED