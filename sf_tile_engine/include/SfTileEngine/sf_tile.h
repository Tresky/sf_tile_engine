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

#ifndef SF_TILE_H
#define SF_TILE_H

#include <iostream>
  using std::cout;
  using std::endl;

#include <SFML\Graphics.hpp>

#include "sf_dll_macro.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

////////////////////////////////////////////////////////////
/// \class SfTile
/// \brief Standard tile class
///
/// This class stores tile data as a GID and an sf::Rect.
/// Storing tile data like this allows us to load tiles
/// much quicker, but it'll take a little longer to render.
/// I figured this trade-off would be worth it, but I might
/// change it in the future.
///
////////////////////////////////////////////////////////////

class SF_TILE_API SfTile
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Constructs a tile.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfTile(int _gid, sf::IntRect _rect);


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing tile.
  ///
  ////////////////////////////////////////////////////////////
  SfTile(const SfTile& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing tile.
  ///
  ////////////////////////////////////////////////////////////
  SfTile& operator=(const SfTile& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Returns the rectangle of the tile.
  ///
  /// \return Rectangle of the tile
  ///
  ////////////////////////////////////////////////////////////
  sf::IntRect GetRect();

private:
  /// Global ID of the tile
  int gid;


  /// Rectangle of the tile
  sf::IntRect rect;
};

}

}

#endif // SF_TILE_H