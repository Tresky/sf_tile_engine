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
{}


////////////////////////////////////////////////////////////
SfLayer::SfLayer(const SfLayer& _copy)
  : tile_gids(_copy.tile_gids)
  , layer_dimensions(_copy.layer_dimensions)
{}


////////////////////////////////////////////////////////////
SfLayer& SfLayer::operator=(const SfLayer& _copy)
{
  if (this != &_copy)
  {
    SfLayer temp(_copy);

    std::swap(tile_gids, temp.tile_gids);
    std::swap(layer_dimensions, temp.layer_dimensions);
  }

  return *this;
}


////////////////////////////////////////////////////////////
int SfLayer::GetTileGID(const int _x, const int _y)
{
  /// The TMX tileset stores tiles startring from 1.
  /// Our vector stores them starting from 0.
  int gid = tile_gids.at(_y).at(_x);

  return gid;
}

}

}