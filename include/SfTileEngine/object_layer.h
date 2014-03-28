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

#ifndef SF_OBJECT_LAYER_H
#define SF_OBJECT_LAYER_H

#include <iostream>
	using std::cout;
	using std::endl;
#include <string>
	using std::string;
#include <vector>
	using std::vector;

#include <SFML\Graphics.hpp>

#include "layer.h"
#include "object.h"
#include "dll_macro.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{
class TilemapLoader;

////////////////////////////////////////////////////////////
/// \class ObjectLayer
/// \brief Stores the GID's of the tiles in the layer
///        and renders them.
/// 
/// This class holds all of the layer data of the tile map.
/// This include tile GID's, a pointer to the tileset, and
/// any other necessary data for rendering the layers.
///
////////////////////////////////////////////////////////////

class SF_TILE_API ObjectLayer : public Layer
{
friend class TilemapLoader;
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates an empty ObjectLayer object.
	///
	////////////////////////////////////////////////////////////
	explicit ObjectLayer();


	////////////////////////////////////////////////////////////
	/// \brief Copy constructor
	///
	/// Copies an existing layer.
	///
	////////////////////////////////////////////////////////////
	ObjectLayer(const ObjectLayer& _copy);


	////////////////////////////////////////////////////////////
	/// \brief Assignment operator
	///
	/// Copies an existing layer.
	///
	////////////////////////////////////////////////////////////
	ObjectLayer& operator=(const ObjectLayer& _copy);


	////////////////////////////////////////////////////////////
	/// \brief Returns a pointer to an object in the layer
	///
	/// \param _index Index of the object to return
	///
	/// \return Pointer to the indexed object
	///
	////////////////////////////////////////////////////////////
	Object* GetObject(unsigned int _index);


	int GetNumObjects();


	////////////////////////////////////////////////////////////
	/// \brief Returns the name of the layer.
	///
	/// \return String name of the layer
	///
	////////////////////////////////////////////////////////////
	string GetName();


	////////////////////////////////////////////////////////////
	/// \brief Returns the type of the layer.
	///
	/// \return String type of the layer
	///
	////////////////////////////////////////////////////////////
	string GetType();


	////////////////////////////////////////////////////////////
	/// \brief Returns the size of the layer.
	///
	/// \return Dimensions of the layer.
	///
	////////////////////////////////////////////////////////////
	sf::Vector2i GetDimensions();

private:
	/// Vector of the objects in the layer
	vector<Object> objects;


	/// Tile dimensions in pixels
	sf::Vector2i layer_dimensions;


	/// Name of the object layer
	string name;


	/// Opacity of the object layer
	float opacity;


	/// Visibility
	bool visible;
};

}

}

#endif // SF_OBJECT_LAYER_H