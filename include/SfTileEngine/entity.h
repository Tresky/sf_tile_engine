////////////////////////////////////////////////////////////
/// SfTileEngine: C++/SFML Tile Engine
/// Copyright (C) 2014 Tyler Petresky
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

#ifndef SF_ENTITY_H
#define SF_ENTITY_H

#include <iostream>
  using std::cout;
  using std::endl;

#include <SFML\Graphics.hpp>

#include "dll_macro.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{
  class TilemapLoader;
}

class SF_TILE_API Entity
{
friend class priv::TilemapLoader;
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Constructs an empty entity.
  ///
  ////////////////////////////////////////////////////////////
  explicit Entity();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing tile map.
  ///
  ////////////////////////////////////////////////////////////
  explicit Entity(const Entity& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing tile map.
  ///
  ////////////////////////////////////////////////////////////
  Entity& operator=(const Entity& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Renders the entity.
  ///
  /// \param _window SFML window to render to
  ///
  ////////////////////////////////////////////////////////////
  void Render(sf::RenderWindow& _window);

private:
};

}

#endif