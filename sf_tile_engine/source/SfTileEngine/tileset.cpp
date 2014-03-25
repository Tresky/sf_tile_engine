#include "..\..\include\SfTileEngine\tileset.h"

#include "..\..\extlibs\TinyXML\tinyxml2.h"
  using namespace tinyxml2;

#include "..\..\include\SfTileEngine\tile.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

////////////////////////////////////////////////////////////
Tileset::Tileset()
  : tile_dimensions(32, 32)
  , tiles()
  , tileset_image()
{}

////////////////////////////////////////////////////////////
Tileset::Tileset(const Tileset& _copy)
  : tile_dimensions(_copy.tile_dimensions)
  , tiles(_copy.tiles)
  , tileset_image(_copy.tileset_image)
{}

////////////////////////////////////////////////////////////
Tileset& Tileset::operator=(const Tileset& _copy)
{
  if (this != &_copy)
  {
    Tileset temp(_copy);

    std::swap(tile_dimensions, temp.tile_dimensions);
    std::swap(tiles, temp.tiles);
    std::swap(tileset_image, temp.tileset_image);
  }

  return *this;
}


////////////////////////////////////////////////////////////
Tileset::~Tileset()
{}


////////////////////////////////////////////////////////////
Tile Tileset::GetTile(const unsigned int _id)
{
  return tiles.at(_id - 1);
}

////////////////////////////////////////////////////////////
const int Tileset::GetNumTiles()
{
  return tiles.size();
}

////////////////////////////////////////////////////////////
void Tileset::RenderTile(sf::RenderWindow& _window, const unsigned int _id, const float _x, const float _y)
{
  Tile tile = GetTile(_id);
  sf::Sprite sprite(tileset_image, tile.GetRect());
  sprite.setPosition(_x, _y);

  _window.draw(sprite);
}

}

}