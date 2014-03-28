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

////////////////////////////////////////////////////////////
/// \class Entity
/// \brief An abstract class that provides the basis for an
///				 entity system in the engine. 
///
/// To successfully use this class, you need to create your
/// own class. Your class should inherit this class as a
/// base and redefine all of the functions provided in this
/// class.
/// You should then create a point of your custom-type and
/// call the tilemap object to create your entity as shown:
///
/// Character character = tilemap->AddEntity("file.ent");
///
////////////////////////////////////////////////////////////
class SF_TILE_API Entity
{
friend class priv::TilemapLoader;
public:
	////////////////////////////////////////////////////////////
	/// \brief Set the position of the entity in tiles
	///
	/// \param _window SFML window to render to
	///
	////////////////////////////////////////////////////////////
	virtual void SetPosition(const float _x, const float _y) = 0;

	////////////////////////////////////////////////////////////
	/// \brief Returns the entity's current position in tiles.
	///
	/// \return Current position of the entity in tiles.
	///
	////////////////////////////////////////////////////////////
	virtual sf::Vector2i GetPosition() = 0;


	////////////////////////////////////////////////////////////
	/// \brief Moves the entity in the x-y plane with respect to
	///				 the current position of the entity.
	///
	/// \param _x Distance to move in the X direction
	/// \param _y Distance to move in the Y direction
	///
	////////////////////////////////////////////////////////////
	virtual void Move(const float _x, const float _y) = 0;

protected:
	////////////////////////////////////////////////////////////
	/// \brief Updates the entity.
	///
	////////////////////////////////////////////////////////////
	virtual void Update() = 0;


	////////////////////////////////////////////////////////////
	/// \brief Renders the entity.
	///
	/// \param _window SFML window to render to
	///
	////////////////////////////////////////////////////////////
	virtual void Render(sf::RenderWindow& _window) = 0;
};

}

#endif