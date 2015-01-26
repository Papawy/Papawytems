# SAMP_items
Plugin that manages items (creation is included)

# Short explanation

In your script, you must first create a ItemSchema to be a model for all items you want to create.
You must set a name, a modelID, and a type (it's a simple number).

After, you can create items. Set item positions and rotations, and show it !

# Build
SAMPGDK4 in a static version is required (there's one in the source folder, ready to use).

Next, you should launch CMake and try to generate sources. After that, compile the plugin with generated files !

# Documentation

## Global natives

#### SetDefaultItemDrawDist(Float:distance)
Set the default draw distance for all items's object.

return :
  Nothing

## Items Manager

#### IsItemExist(itemID)
Check if a specified item is stored.

return :
  0 if item is not found, or 1 otherwise.
  
#### IsItemSchemaExist(itemID)
Check if a specified itemSchema is stored.

return :
  0 if itemSchema is not found, or 1 otherwise.
  
#### GetMaxItems()
Get number of items stored.

return :
  Number of items stored.
  
## Item Schema

#### CreateItemSchema(schemaName[], typeID, modelID)
Create an item schema.

return :
  ID of the new created item schema.
  
#### SetItemSchemaName(itemSchemaID, schemaName[])
Set a new name for an item schema.

return :
  0 if itemSchema is not found, or 1 otherwise
  
#### SetItemSchemaType(itemSchemaID, typeID)
Set a new type for an item schema.

return :
  0 if itemSchema is not found, or 1 otherwise
  
#### SetItemSchemaModel(itemSchemaID, modelID)
Set a new 3d model for an item schema.

return :
  0 if itemSchema is not found, or 1 otherwise
  
## Items

