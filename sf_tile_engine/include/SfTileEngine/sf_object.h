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

#ifndef SF_OBJECT_H
#define SF_OBJECT_H

#include <iostream>
  using std::cout;
  using std::endl;
#include <string>
  using std::string;

#include <SFML\Graphics.hpp>

#include "sf_dll_macro.h"

/// Engine namespace
namespace sftile
{

enum ObjectType
{
  SF_OBJECT_TYPE_UNKNOWN = 0,
  SF_OBJECT_TYPE_TILE,
  SF_OBJECT_TYPE_ELLIPSE,
  SF_OBJECT_TYPE_POLYGON,
  SF_OBJECT_TYPE_POLYLINE,
  SF_OBJECT_TYPE_IMAGE
};

/// Private engine namespace
namespace priv
{
class SfTilemapLoader;
}

class SF_TILE_API SfObject
{
friend class priv::SfTilemapLoader;
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Creates an empty object.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfObject();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing object.
  ///
  ////////////////////////////////////////////////////////////
  SfObject(const SfObject& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing object.
  ///
  ////////////////////////////////////////////////////////////
  SfObject& operator=(const SfObject& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Returns the name of the object
  ///
  /// \return String of the name of the object
  ///
  ////////////////////////////////////////////////////////////
  string GetName();


  ////////////////////////////////////////////////////////////
  /// \brief Returns the string type of the object
  ///
  /// \return String type of the object
  ///
  ////////////////////////////////////////////////////////////
  string GetStringType();


  ////////////////////////////////////////////////////////////
  /// \brief Returns the position of the object
  ///
  /// \return Position of the object in pixels
  ///
  ////////////////////////////////////////////////////////////
  sf::Vector2i GetPosition();


  ////////////////////////////////////////////////////////////
  /// \brief Returns the dimensions of the object
  ///
  /// \return Dimensions of the object in pixels
  ///
  ////////////////////////////////////////////////////////////
  sf::Vector2i GetDimensions();


  ////////////////////////////////////////////////////////////
  /// \brief Returns the rotation angle of the object
  ///
  /// \return Rotation angle in degrees
  ///
  ////////////////////////////////////////////////////////////
  float GetRotation();


  ////////////////////////////////////////////////////////////
  /// \brief Returns the GID of the tile being used (if any)
  ///
  /// \return GID of the tile being used (if any)
  ///
  ////////////////////////////////////////////////////////////
  int GetGid();


  ////////////////////////////////////////////////////////////
  /// \brief Returns whether the object is visible or not
  ///
  /// \return True if the object is visible
  ///
  ////////////////////////////////////////////////////////////
  bool IsVisible();


  ////////////////////////////////////////////////////////////
  /// \brief Renders the object to the window
  ///
  /// \param _window Window to render to
  ///
  ////////////////////////////////////////////////////////////
  void Render(sf::RenderWindow& _window);

private:
  /// Type of the object
  ObjectType object_type;


  /// Name of the object
  string name;


  /// Custom string literal type - arbitrary string for end-user use
  string string_type;


  /// Position of the object (in pixels)
  sf::Vector2i position;


  /// Dimensions of the object(in pixels)
  sf::Vector2i dimensions;


  /// Rotation in degrees
  float rotation;


  /// GID of the tile being used (if any)
  int gid;
  

  /// Visibility
  bool visible;
};

}

#endif /// SF_OBJECT_H