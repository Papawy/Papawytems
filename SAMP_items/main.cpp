#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

#include "ItemManager.h"

typedef void(*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void *pAMXFunctions;

ItemManager itmManager;

cell AMX_NATIVE_CALL HelloWorld(AMX* amx, cell* params)
{
	logprintf("This was printed from the Test plugin! Yay!");
	return 1;
}

// ---- ITEM SHEMA ----

// PAWN Native : native CreateItemShema(shemaName[], typeID, modelID) | return : shemaID : /!\ Important 
cell AMX_NATIVE_CALL CreateItemShema(AMX* amx, cell* params)
{
	// Creating temporary shema
	ItemShema tmpShem;

	// Getting string param address
	cell *addr = NULL;
		// shemaName
	amx_GetAddr(amx, params[1], &addr);

	// First param
	int len = NULL;

	amx_StrLen(addr, &len);

	if (len)
	{
		len++;
		char* shemaName = new char[len];
		amx_GetString(shemaName, addr, 0, len);

		tmpShem.setItemName(shemaName);
		delete[] shemaName;
	}

	// Second param
	tmpShem.setItemType(params[2]);

	// Third param
	tmpShem.setItemModel(params[3]);

	// Pushing tmp shema into ItemManager
	return itmManager.addItemShema(tmpShem);
}


// PAWN Native : native SetItemShemaName(itemShemaID, shemaName[]) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemShemaName(AMX* amx, cell* params)
{
	if (itmManager.itemShemaExist(params[1]))
	{
		// Gettinf new shemaName str
		cell *addr = NULL;

		amx_GetAddr(amx, params[2], &addr);

		int len = NULL;

		amx_StrLen(addr, &len);

		if (len)
		{
			len++;

			char* newShemName = new char[len];
			amx_GetString(newShemName, addr, 0, len);

			itmManager.accessItemShema(params[1]).setItemName(newShemName);
			delete[] newShemName;
		}
		
		return 1;
	}
	else
		return 0;

}

// PAWN Native : native SetItemShemaType(itemShemaID, shemaType) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemShemaType(AMX* amx, cell* params)
{
	if (itmManager.itemShemaExist(params[1]))
	{
		itmManager.accessItemShema(params[1]).setItemType(params[2]);
		return 1;
	}
	else
		return 0;
}

// PAWN Native : native SetItemShemaModel(itemShemaID, shemaModel) | return 0 if item is not found, or 1 otherwise
cell AMX_NATIVE_CALL SetItemShemaModel(AMX* amx, cell* params)
{
	if (itmManager.itemShemaExist(params[1]))
	{
		itmManager.accessItemShema(params[1]).setItemModel(params[2]);
		return 1;
	}
	else
		return 0;
}

// ----- ITEMS --------

// PAWN Native : native CreateItem(shemaID) | return : itemID : /!\ Important 
cell AMX_NATIVE_CALL CreateItem(AMX* amx, cell* params)
{
	// Creating tempo item and assign ItemShema
	try
	{
		itmManager.accessItemShema(params[1]);
		Item tmpItem(itmManager.accessItemShema(params[1]));
		return itmManager.addItem(tmpItem);
	}
	catch (int e)
	{
		return e;
	}
}

// PAWN Native : native CreateItemEx(shemaID, Float:posx, Float:posy, Float:posz, Float:rotx, Float:roty, Float:rotz) | return : itemID : /!\ Important 
cell AMX_NATIVE_CALL CreateItemEx(AMX* amx, cell* params)
{
	try
	{
		itmManager.accessItemShema(params[1]);
		Item tmpItem(itmManager.accessItemShema(params[1]));

		ObjectPosition posRot;
		posRot.px = amx_ctof(params[2]);
		posRot.py = amx_ctof(params[3]);
		posRot.pz = amx_ctof(params[4]);

		posRot.rx = amx_ctof(params[5]);
		posRot.ry = amx_ctof(params[6]);
		posRot.rz = amx_ctof(params[7]);

		tmpItem.setPosition(posRot);

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
	}
	else
		return 0;
}

// PAWN Native : native GetItemVar(itemID, varID[]) | return 0 if item is not found or if variable doesn't exist, variable value if variable was found
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
				return itmManager.accessItem(params[1]).getVar(varName);
			}
			else
			{
				return 0;
			}
			delete[] varName;
		}
	}
	else
		return 0;
}




PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*******************************\r\n");
	logprintf(" Papawytems loaded !\r\n");
	logprintf("Compiled on "__DATE__" at "__TIME__"\r\n");
	logprintf("*******************************");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * Test plugin was unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "HelloWorld", HelloWorld },
	{ "CreateItemShema", CreateItemShema },
	{ "CreateItem", CreateItem },
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