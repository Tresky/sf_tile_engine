#include "..\..\include\SfTileEngine\sf_tileset.h"

#include "..\..\extlibs\TinyXML\tinyxml2.h"
  using namespace tinyxml2;

#include "..\..\include\SfTileEngine\sf_tile.h"
#include "..\..\include\SfTileEngine\sf_properties.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

// Default constructor
SfTileset::SfTileset()
  : tile_dimensions(32, 32)
  , tiles()
  , tileset_image()
  //, properties(new SfProperties())
{}

// Copy constructor
SfTileset::SfTileset(const SfTileset& _copy)
  : tile_dimensions(_copy.tile_dimensions)
  , tileset_image(_copy.tileset_image)
{
  //properties.reset(_copy.properties.get());

  for (unsigned int i = 0; i < tiles.size(); ++i)
    tiles.emplace_back( unique_ptr<SfTile>(new SfTile(*_copy.tiles.at(i).get())));
}

// Assignment operator
SfTileset& SfTileset::operator=(const SfTileset& _copy)
{
  if (this != &_copy)
  {
    SfTileset temp(_copy);

    std::swap(tile_dimensions, temp.tile_dimensions);
    std::swap(tiles, temp.tiles);
    std::swap(tileset_image, temp.tileset_image);
    //std::swap(properties, temp.properties);
  }

  return *this;
}


////////////////////////////////////////////////////////////
SfTileset::~SfTileset()
{}


///
priv::SfTile* SfTileset::GetTile(const unsigned int _id)
{
  return tiles.at(_id).get();
}

///
const int SfTileset::GetNumTiles()
{
  return tiles.size();
}

///
void SfTileset::RenderTile(sf::RenderWindow& _window, const unsigned int _id, const int _x, const int _y)
{
  sf::Vector2f pos(static_cast<float>(_x * tile_dimensions.x), static_cast<float>(_y * tile_dimensions.y));
  
  SfTile* tile = GetTile(_id);
  sf::Sprite sprite(tileset_image, tile->GetRect());
  sprite.setPosition(pos);

  _window.draw(sprite);
}

}

}