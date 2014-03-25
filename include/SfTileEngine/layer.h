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

#ifndef SF_LAYER_H
#define SF_LAYER_H

#include <string>
	using std::string;

#include "dll_macro.h"

/// Library namespace
namespace sftile
{

/// Private library namespace
namespace priv
{

class SF_TILE_API Layer
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// Constructs an empty Layer object.
	///
	////////////////////////////////////////////////////////////
	explicit Layer();


	////////////////////////////////////////////////////////////
	 /// \brief Copy constructor
	  ///
	/// Copies an existing layer.
	///
	 ////////////////////////////////////////////////////////////
	Layer(const Layer& _copy);


	////////////////////////////////////////////////////////////
	/// \brief Assignment operator
	///
	/// Copies an existing layer.
	///
	////////////////////////////////////////////////////////////
	Layer& operator=(const Layer& _copy);

	////////////////////////////////////////////////////////////
	/// \brief Returns the name of the layer
	///
	/// \return String name of the layer
	///
	////////////////////////////////////////////////////////////
	virtual string GetName() = 0;
};

}

}

#endif // SF_LAYER_H