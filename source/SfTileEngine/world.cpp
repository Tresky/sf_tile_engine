#include "..\..\include\SfTileEngine\world.h"

#include "..\..\include\SfTileEngine\tilemap.h"
#include "..\..\include\SfTileEngine\tileset.h"
#include "..\..\include\SfTileEngine\tilemap_loader.h"

/// Engine namespace
namespace sftile
{


////////////////////////////////////////////////////////////
World::World()
	: loader()
	, tilemaps()
	, current_id("null")
{
	cout << "World created" << endl;
}


////////////////////////////////////////////////////////////
World::World(const World& _copy)
	: loader(_copy.loader)
	, tilemaps(_copy.tilemaps)
	, current_id(_copy.current_id)
{}


////////////////////////////////////////////////////////////
World& World::operator=(const World& _copy)
{
	if (this != &_copy)
	{
		World temp(_copy);

		std::swap(loader, temp.loader);
		std::swap(tilemaps, temp.tilemaps);
		std::swap(current_id, temp.current_id);
	}

	return *this;
}


////////////////////////////////////////////////////////////
// If an SfTilemap with the specifed ID already exists,
// we return a pointer to it. If it doesn't we attempt to
// load the new one. If the loading is successful we return
// the loaded map, if it's not we return nullptr.
////////////////////////////////////////////////////////////
Tilemap* World::LoadTilemap(string _id, string _path)
{
	Tilemap tilemap;
  
	// Check to make sure the SfTilemap doesn't already exists.
	// If not, then attempt to parse the data for it.
	if (!MapExists(_id) && !loader.LoadTilemap(_path, tilemap))
	{
		cout << "Failed to load SfTilemap from path: " << _path << endl;
		return nullptr;
	}
  
	tilemaps.emplace(_id, std::move(tilemap));
	cout << "Loaded SfTilemap from path: " << _path << endl;

	current_id = _id;
	
	return GetTilemap(_id);
}


////////////////////////////////////////////////////////////
Tilemap* World::GetTilemap(string _id)
{
	// Check for existence of the SfTilemap
	if (tilemaps.find(_id) == tilemaps.end())
	{
		cout << "Failed to find SfTilemap with ID: " << _id << endl;
		return nullptr;
	}
	else
	{
		return &tilemaps.at(_id);
	}
}


////////////////////////////////////////////////////////////
void World::HandleEvents(sf::Event _evt)
{
  GetTilemap(current_id)->HandleEvents(_evt);
}


////////////////////////////////////////////////////////////
void World::Update()
{
  GetTilemap(current_id)->Update();
}


////////////////////////////////////////////////////////////
void World::Render(sf::RenderWindow& _window)
{
  GetTilemap(current_id)->Render(_window);
}


////////////////////////////////////////////////////////////
bool World::MapExists(string _id)
{
  if (tilemaps.find(_id) == tilemaps.end())
    return false;
  else
    return true;
}

} //namespace sftile