////////////////////////////////////////////////////////////
/// SfTileEngine: C++/SFML Tile Engine
/// Copyright (C) 2013 Tyler Petresky
///
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////

#include "..\..\include\SfTileEngine\sf_layer.h"

#include "..\..\include\SfTileEngine\sf_tileset.h"

/// Library namespace
namespace sftile
{

/// Private library namespace
namespace priv
{

////////////////////////////////////////////////////////////
SfLayer::SfLayer()
  : tile_gids()
  , layer_dimensions(-1, -1)
  , tileset()
{}


////////////////////////////////////////////////////////////
SfLayer::SfLayer(const SfLayer& _copy)
  : tile_gids(_copy.tile_gids)
  , layer_dimensions(_copy.layer_dimensions)
  , tileset(_copy.tileset)
{}


////////////////////////////////////////////////////////////
SfLayer& SfLayer::operator=(const SfLayer& _copy)
{
  if (this != &_copy)
  {
    SfLayer temp(_copy);

    std::swap(tile_gids, temp.tile_gids);
    std::swap(layer_dimensions, temp.layer_dimensions);
    std::swap(tileset, temp.tileset);
  }

  return *this;
}


////////////////////////////////////////////////////////////
void SfLayer::Render(sf::RenderWindow& _window)
{
  for (int y = 0; y < layer_dimensions.y; ++y)
    for (int x = 0; x < layer_dimensions.x; ++x)
    {
      int gid = tile_gids.at(y).at(x) - 1;
      if (gid < 0)
        continue;

      tileset->RenderTile(_window,   // Window to render to
                          gid,       // GID of tile
                          x,         // X coordinate in tiles
                          y);        // Y coordinate in tiles
    }
}

}

}