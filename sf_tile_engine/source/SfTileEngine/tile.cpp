#include "..\..\include\SfTileEngine\tile.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

////////////////////////////////////////////////////////////
Tile::Tile(int _gid, sf::IntRect _rect)
  : gid(_gid)
  , rect(_rect)
{}


////////////////////////////////////////////////////////////
Tile::Tile(const Tile& _copy)
  : gid(_copy.gid)
  , rect(_copy.rect)
{}


////////////////////////////////////////////////////////////
Tile& Tile::operator=(const Tile& _copy)
{
  if (this != &_copy)
  {
    Tile temp(_copy);

    std::swap(gid, temp.gid);
    std::swap(rect, temp.rect);
  }

  return *this;
}


////////////////////////////////////////////////////////////
sf::IntRect Tile::GetRect()
{
  return rect;
}

}

}