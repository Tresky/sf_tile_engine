#include "..\..\include\SfTileEngine\sf_tile.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

////////////////////////////////////////////////////////////
SfTile::SfTile(int _gid, sf::IntRect _rect)
  : gid(_gid)
  , rect(_rect)
{}


////////////////////////////////////////////////////////////
SfTile::SfTile(const SfTile& _copy)
  : gid(_copy.gid)
  , rect(_copy.rect)
{}


////////////////////////////////////////////////////////////
SfTile& SfTile::operator=(const SfTile& _copy)
{
  if (this != &_copy)
  {
    SfTile temp(_copy);

    std::swap(gid, temp.gid);
    std::swap(rect, temp.rect);
  }

  return *this;
}


////////////////////////////////////////////////////////////
sf::IntRect SfTile::GetRect()
{
  return rect;
}

}

}