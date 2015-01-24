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

// PAWN Native : native SetItemShemaName(itemShemaID, shemaName[]) | return false if item is not found, or inverse otherwise
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

// PAWN Native : native SetItemShemaType(itemShemaID, shemaType) | return false if item is not found, or inverse otherwise
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

// PAWN Native : native SetItemShemaModel(itemShemaID, shemaModel) | return false if item is not found, or inverse otherwise
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