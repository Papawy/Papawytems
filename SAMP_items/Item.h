#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <vector>

#include "Utils.h"

#include "ItemShema.h"

class Item
{
public:
	Item(ItemShema& shema);
	Item(ItemShema& shema, ObjectPosition position);
	// I add it if it's requested
	/*Item(ItemShema& shema,
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

	void setVar(int varID, int value);

	// Accessors

	ObjectPosition& getPosition();

	int getVar(int varID);

	ItemShema& getShema();

	// --

	void Show();
	void Hide();

	~Item();

private:
	ItemShema *m_shema;

	std::vector<int> m_vars;
	
	ObjectPosition m_position;

	bool m_showed;
};
#endif // ITEM_H_INCLUDED