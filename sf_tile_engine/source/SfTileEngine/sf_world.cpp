#include "..\..\include\SfTileEngine\sf_world.h"

#include "..\..\include\SfTileEngine\sf_tilemap.h"
#include "..\..\include\SfTileEngine\sf_tileset.h"
#include "..\..\include\SfTileEngine\sf_tilemap_loader.h"

/// Engine namespace
namespace sftile
{


////////////////////////////////////////////////////////////
SfWorld::SfWorld()
  : loader(new priv::SfTilemapLoader())
  , tilemaps()
  , current_id("null")
{
	cout << "World created" << endl;
}


////////////////////////////////////////////////////////////
SfWorld::SfWorld(const SfWorld& _copy)
  : current_id(_copy.current_id)
{
  loader.reset(_copy.loader.get());

  map<string, unique_ptr<SfTilemap> >::const_iterator iter;
  for (iter = _copy.tilemaps.begin(); iter != _copy.tilemaps.end(); ++iter)
    tilemaps.emplace(iter->first, unique_ptr<SfTilemap>(iter->second.get()));
}


////////////////////////////////////////////////////////////
SfWorld& SfWorld::operator=(const SfWorld& _copy)
{
  if (this != &_copy)
  {
    SfWorld temp(_copy);

    std::swap(loader, temp.loader);
    std::swap(tilemaps, temp.tilemaps);
    std::swap(current_id, temp.current_id);
  }

  return *this;
}


///////////////////////////////////////////////////////////
SfWorld::~SfWorld()
{}


////////////////////////////////////////////////////////////
// If an SfTilemap with the specifed ID already exists,
// we return a pointer to it. If it doesn't we attempt to
// load the new one. If the loading is successful we return
// the loaded map, if it's not we return nullptr.
////////////////////////////////////////////////////////////
SfTilemap* SfWorld::LoadTilemap(string _id, string _path)
{
  SfTilemap tilemap;
  
  // Check to make sure the SfTilemap doesn't already exists.
  // If not, then attempt to parse the data for it.
  if (!MapExists(_id) && !loader->LoadTilemap(_path, tilemap))
  {
    cout << "Failed to load SfTilemap from path: " << _path << endl;
    return nullptr;
  }
  
  tilemaps.emplace(_id, unique_ptr<SfTilemap>(new SfTilemap(tilemap)));

  cout << "Loaded SfTilemap from path: " << _path << endl;

  current_id = _id;
  return GetTilemap(_id);
}


////////////////////////////////////////////////////////////
SfTilemap* SfWorld::GetTilemap(string _id)
{
  // Check for existence of the SfTilemap
  if (tilemaps.find(_id) == tilemaps.end())
  {
    cout << "Failed to find SfTilemap with ID: " << _id << endl;
    return nullptr;
  }
  else
    return tilemaps.at(_id).get();
}


////////////////////////////////////////////////////////////
void SfWorld::HandleEvents(sf::Event _evt)
{
  GetTilemap(current_id)->HandleEvents(_evt);
}


////////////////////////////////////////////////////////////
void SfWorld::Update()
{
  GetTilemap(current_id)->Update();
}


////////////////////////////////////////////////////////////
void SfWorld::Render(sf::RenderWindow& _window)
{
  GetTilemap(current_id)->Render(_window);
}


////////////////////////////////////////////////////////////
bool SfWorld::MapExists(string _id)
{
  if (tilemaps.find(_id) == tilemaps.end())
    return false;
  else
    return true;
}

} //namespace sftile