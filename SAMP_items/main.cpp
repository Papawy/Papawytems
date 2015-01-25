#include <sampgdk/a_objects.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

#include "ItemManager.h"
/*
typedef void(*logprintf_t)(char* format, ...);


logprintf_t logprintf;*/
extern void *pAMXFunctions;

using sampgdk::logprintf;

ItemManager itmManager;

float defaultDrawDist = 300.0;

// PAWN Native : native SetDefaultItemDrawDist(Float:distance) | return : nothing
cell AMX_NATIVE_CALL SetDefaultItemDrawDist(AMX* amx, cell* params)
{
	defaultDrawDist = amx_ctof(params[1]);
	return 1;
}

// --- ITEMS MANAGER ---

// ---- ITEM SCHEMA ----

// PAWN Native : native CreateItemSchema(SchemaName[], typeID, modelID) | return : SchemaID : /!\ Important 
cell AMX_NATIVE_CALL CreateItemSchema(AMX* amx, cell* params)
{
	// Creating temporary Schema
	ItemSchema tmpShem;

	// Getting string param address
	cell *addr = NULL;
		// SchemaName
	amx_GetAddr(amx, params[1], &addr);

	// First param
	int len = NULL;

	amx_StrLen(addr, &len);

	if (len)
	{
		len++;
		char* SchemaName = new char[len];
		amx_GetString(SchemaName, addr, 0, len);

		tmpShem.setItemName(SchemaName);
		delete[] SchemaName;
	}

	// Second param
	tmpShem.setItemType(params[2]);

	// Third param
	tmpShem.setItemModel(params[3]);

	// Pushing tmp Schema into ItemManager
	return itmManager.addItemSchema(tmpShem);
}


// PAWN Native : native SetItemSchemaName(itemSchemaID, SchemaName[]) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemSchemaName(AMX* amx, cell* params)
{
	if (itmManager.itemSchemaExist(params[1]))
	{
		// Gettinf new SchemaName str
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		int len = NULL;

		amx_StrLen(addr, &len);

		if (len)
		{
			len++;

			char* newShemName = new char[len];
			amx_GetString(newShemName, addr, 0, len);

			itmManager.accessItemSchema(params[1]).setItemName(newShemName);
			delete[] newShemName;
		}
		
		return 1;
	}
	else
		return 0;

}

// PAWN Native : native SetItemSchemaType(itemSchemaID, SchemaType) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemSchemaType(AMX* amx, cell* params)
{
	if (itmManager.itemSchemaExist(params[1]))
	{
		itmManager.accessItemSchema(params[1]).setItemType(params[2]);
		return 1;
	}
	else
		return 0;
}

// PAWN Native : native SetItemSchemaModel(itemSchemaID, SchemaModel) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemSchemaModel(AMX* amx, cell* params)
{
	if (itmManager.itemSchemaExist(params[1]))
	{
		itmManager.accessItemSchema(params[1]).setItemModel(params[2]);
		return 1;
	}
	else
		return 0;
}

// ----- ITEMS --------

// PAWN Native : native CreateItem(SchemaID) | return : itemID : /!\ Important 
cell AMX_NATIVE_CALL CreateItem(AMX* amx, cell* params)
{
	// Creating tempo item and assign ItemSchema
	try
	{
		itmManager.accessItemSchema(params[1]);
		Item tmpItem(itmManager.accessItemSchema(params[1]));
		tmpItem.setDrawDistance(defaultDrawDist);
		return itmManager.addItem(tmpItem);
	}
	catch (int e)
	{
		return e;
	}
}

// PAWN Native : native CreateItemEx(SchemaID, Float:posx, Float:posy, Float:posz, Float:rotx, Float:roty, Float:rotz) | return : itemID : /!\ Important 
cell AMX_NATIVE_CALL CreateItemEx(AMX* amx, cell* params)
{
	try
	{
		itmManager.accessItemSchema(params[1]);
		Item tmpItem(itmManager.accessItemSchema(params[1]));

		ObjectPosition posRot;
		posRot.px = amx_ctof(params[2]);
		posRot.py = amx_ctof(params[3]);
		posRot.pz = amx_ctof(params[4]);

		posRot.rx = amx_ctof(params[5]);
		posRot.ry = amx_ctof(params[6]);
		posRot.rz = amx_ctof(params[7]);

		tmpItem.setPosition(posRot);

		tmpItem.setDrawDistance(defaultDrawDist);

		return itmManager.addItem(tmpItem);
	}
	catch (int e)
	{
		return e;
	}
}


// PAWN Native : native SetItemPos(itemID, Float:posx, Float:posy, Float:posz) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemPos(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		ObjectPosition tmpPos(itmManager.accessItem(params[1]).getPosition());
		tmpPos.px = amx_ctof(params[2]);
		tmpPos.py = amx_ctof(params[3]);
		tmpPos.pz = amx_ctof(params[4]);

		itmManager.accessItem(params[1]).setPosition(tmpPos);
		return 1;
	}
	else
		return 0;
}

// PAWN Native : native GetItemPos(itemID, &Float:posx, &Float:posy, &Float:posz) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL GetItemPos(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		cell* addr[3] = { NULL, NULL, NULL };

		amx_GetAddr(amx, params[2], &addr[0]);
		amx_GetAddr(amx, params[3], &addr[1]);
		amx_GetAddr(amx, params[4], &addr[2]);

		*addr[0] = amx_ftoc(itmManager.accessItem(params[1]).getPosition().px);
		*addr[1] = amx_ftoc(itmManager.accessItem(params[1]).getPosition().py);
		*addr[2] = amx_ftoc(itmManager.accessItem(params[1]).getPosition().pz);

		return 1;
	}
	else
		return 0;
}


// PAWN Native : native SetItemRot(itemID, Float:rotx, Float:roty, Float:rotz) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemRot(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		ObjectPosition tmpPos(itmManager.accessItem(params[1]).getPosition());
		tmpPos.rx = amx_ctof(params[2]);
		tmpPos.ry = amx_ctof(params[3]);
		tmpPos.rz = amx_ctof(params[4]);

		itmManager.accessItem(params[1]).setPosition(tmpPos);
		return 1;
	}
	else
		return 0;
}

// PAWN Native : native GetItemRot(itemID, &Float:rotx, &Float:roty, &Float:rotz) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL GetItemRot(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		cell* addr[3] = { NULL, NULL, NULL };

		amx_GetAddr(amx, params[2], &addr[0]);
		amx_GetAddr(amx, params[3], &addr[1]);
		amx_GetAddr(amx, params[4], &addr[2]);

		*addr[0] = amx_ftoc(itmManager.accessItem(params[1]).getPosition().rx);
		*addr[1] = amx_ftoc(itmManager.accessItem(params[1]).getPosition().ry);
		*addr[2] = amx_ftoc(itmManager.accessItem(params[1]).getPosition().rz);

		return 1;
	}
	else
		return 0;
}


// PAWN Native : native SetItemName(itemID, itemName[]) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemName(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		// Gettinf new itemName str
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		int len = NULL;

		amx_StrLen(addr, &len);

		if (len)
		{
			len++;

			char* newItemName = new char[len];
			amx_GetString(newItemName, addr, 0, len);

			itmManager.accessItem(params[1]).setName(newItemName);
			delete[] newItemName;
		}

		return 1;
	}
	else
		return 0;
}

// PAWN Native : native SetItemDefaultName(itemID) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemDefaultName(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		itmManager.accessItem(params[1]).setDefaultName();
		return 1;
	}
	else
		return 0;
}

// PAWN Native : native GetItemName(itemID, itemName[], len = sizeof(itemName)) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL GetItemName(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, itmManager.accessItem(params[1]).getName().c_str(), 0, 0, params[3]);
		return 1;
	}
	else
		return 0;
}


// PAWN Native : native SetItemVar(itemID, varID[], value) | return 0 if item is not found, 1 if variable is created, 2 if variable is setted
cell AMX_NATIVE_CALL SetItemVar(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		// Gettinf varName str
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		int len = NULL;

		amx_StrLen(addr, &len);

		if (len)
		{
			len++;

			char* varName = new char[len];
			amx_GetString(varName, addr, 0, len);

			if (itmManager.accessItem(params[1]).isVariableExist(varName))
			{
				itmManager.accessItem(params[1]).setVar(varName, params[2]);
				return 2;
			}
			else
			{
				itmManager.accessItem(params[1]).createVar(varName, params[2]);
				return 1;
			}
			delete[] varName;
		}
		return 0;
	}
	else
		return 0;
}

// PAWN Native : native RemoveItemVar(itemID, varID[]) | return 0 if item is not found, 1 if variable was removed, 2 if variable was not found
cell AMX_NATIVE_CALL RemoveItemVar(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		// Gettinf varName str
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		int len = NULL;

		amx_StrLen(addr, &len);

		if (len)
		{
			len++;

			char* varName = new char[len];
			amx_GetString(varName, addr, 0, len);

			if (itmManager.accessItem(params[1]).isVariableExist(varName))
			{
				itmManager.accessItem(params[1]).removeVar(varName);
				return 1;
			}
			else
			{
				return 2;
			}
			delete[] varName;
		}
		return 2;
	}
	else
		return 0;
}

// PAWN Native : native GetItemVar(itemID, varID[]) | return 0 if item is not found or if variable doesn't exist, variable value if variable was found
cell AMX_NATIVE_CALL GetItemVar(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		// Gettinf varName str
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		int len = NULL;

		amx_StrLen(addr, &len);

		if (len)
		{
			len++;

			char* varName = new char[len];
			amx_GetString(varName, addr, 0, len);

			if (itmManager.accessItem(params[1]).isVariableExist(varName))
			{
				return itmManager.accessItem(params[1]).getVar(varName);
			}
			else
			{
				return 0;
			}
			delete[] varName;
		}
		return 0;
	}
	else
		return 0;
}


// PAWN Native : native GetItemType(itemID) | return 0 if item is not found, or type otherwise
cell AMX_NATIVE_CALL GetItemType(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		return itmManager.accessItem(params[1]).getSchema().getItemType();
	}
	else
		return 0;
}

// PAWN Native : native GetItemModel(itemID) | return 0 if item is not found, or model id otherwise
cell AMX_NATIVE_CALL GetItemModel(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		return itmManager.accessItem(params[1]).getSchema().getItemModel();
	}
	else
		return 0;
}

// PAWN Native : native GetItemObjectID(itemID) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL GetItemObjectID(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		return itmManager.accessItem(params[1]).getObjectID();
	}
	else
		return 0;
}

// PAWN Native : native ShowItem(itemID) | return 0 if item is not found, 2 if it's already shown or 1 otherwise
cell AMX_NATIVE_CALL ShowItem(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		if (itmManager.accessItem(params[1]).Show())
			return 1;
		else
			return 2;
	}
	else
		return 0;
}

// PAWN Native : native HideItem(itemID) | return 0 if item is not found, 2 if it's already hidden or 1 otherwise
cell AMX_NATIVE_CALL HideItem(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		if (itmManager.accessItem(params[1]).Hide())
			return 1;
		else
			return 2;
	}
	else
		return 0;
}

// PAWN Native : native IsItemShown(itemID) | return 0 is item is not found, 1 if it's shown, or 2 ir it's hidden
cell AMX_NATIVE_CALL IsItemShown(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		if (itmManager.accessItem(params[1]).isShown())
			return 1;
		else
			return 2;
	}
	else
		return 0;
}

// PAWN Native : native SetItemDrawDistance(itemID, Float:distance) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemDrawDistance(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		itmManager.accessItem(params[1]).setDrawDistance(amx_ctof(params[2]));
		return 1;
	}
	else
		return 0;
}

/*
------ NOT IMPLEMENTED YET --------------
// PAWN Native : native GetItemItemSchema(itemID) |return -1 if item is not found or itemSchema id if it was found
cell AMX_NATIVE_CALL GetItemItemSchema(AMX* amx, cell* params)
{
	if (itmManager.itemExist(params[1]))
	{
		return itmManager.accessItem(params[1]).getSchema()
	}
	else
		return -1;
}*/


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	//logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*******************************\r\n");
	logprintf(" Papawytems loaded !\r\n");
	logprintf("Compiled on "__DATE__" at "__TIME__"\r\n");
	logprintf("*******************************");
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("*******************************\r\n");
	logprintf(" Papawytems unloaded !\r\n");
	logprintf("Compiled on "__DATE__" at "__TIME__"\r\n");
	logprintf("*******************************");

	sampgdk::Unload();
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "SetDefaultItemDrawDist", SetDefaultItemDrawDist },
	// Item Schema
	//		Creation
	{ "CreateItemSchema", CreateItemSchema },
	//		Properties
	{ "SetItemSchemaName", SetItemSchemaName },
	{ "SetItemSchemaType", SetItemSchemaType },
	{ "SetItemSchemaModel", SetItemSchemaModel },
	// Items
	//		Creation
	{ "CreateItem", CreateItem },
	{ "CreateItemEx", CreateItemEx },
	//		Positions
	{ "SetItemPos", SetItemPos },
	{ "GetItemPos", GetItemPos },
	{ "SetItemRot", SetItemRot },
	{ "GetItemRot", GetItemRot },
	//		Name
	{ "SetItemName", SetItemName },
	{ "SetItemDefaultName", SetItemDefaultName },
	{ "GetItemName", GetItemName },
	//		Vars
	{ "SetItemVar", SetItemVar },
	{ "RemoveItemVar", RemoveItemVar },
	{ "GetItemVar", GetItemVar },
	//		Schema accessors
	{ "GetItemType", GetItemType },
	{ "GetItemModel", GetItemModel },
	//		Drawing
	{ "GetItemObjectID", GetItemObjectID },
	{ "ShowItem", ShowItem },
	{ "HideItem", HideItem },
	{ "IsItemShown", IsItemShown },
	//		Others
	{ "SetItemDefaultName", SetItemDefaultName },

	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}