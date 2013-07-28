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

#ifndef SF_LAYER_H
#define SF_LAYER_H

#include <iostream>
  using std::cout;
  using std::endl;
#include <string>
  using std::string;
#include <vector>
  using std::vector;
#include <memory>
  using std::shared_ptr;

#include <SFML\Graphics.hpp>

#include "sf_dll_macro.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{
class SfTilemapLoader;

////////////////////////////////////////////////////////////
/// \class SfLayer
/// \brief Stores the GID's of the tiles in the layer
///        and renders them.
/// 
/// This class holds all of the layer data of the tile map.
/// This include tile GID's, a pointer to the tileset, and
/// any other necessary data for rendering the layers.
///
////////////////////////////////////////////////////////////

class SF_TILE_API SfLayer
{
friend class priv::SfTilemapLoader;
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Creates an empty layer object.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfLayer();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing layer.
  ///
  ////////////////////////////////////////////////////////////
  SfLayer(const SfLayer& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing layer.
  ///
  ////////////////////////////////////////////////////////////
  SfLayer& operator=(const SfLayer& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Gets the tile GID at a specific location in the
  ///        layer.
  ///
  /// \param _x X coordinate of the tile
  /// \param _y Y coordinate of the tile
  /// \return GID of the tile in question
  ///
  ////////////////////////////////////////////////////////////
  int GetTileGID(const int _x, const int _y);

private:
  /// Vector of the tile GIDs in the layer
  vector< vector<int> > tile_gids;


  /// Tile dimensions in pixels
  sf::Vector2i layer_dimensions;
};

}

}

#endif // SF_LAYER_H