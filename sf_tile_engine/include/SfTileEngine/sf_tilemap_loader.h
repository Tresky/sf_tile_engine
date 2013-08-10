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

#ifndef SF_TILEMAP_LOADER
#define SF_TILEMAP_LOADER

#include <iostream>
  using std::cout;
  using std::endl;
#include <string>
  using std::string;
#include <memory>
  using std::unique_ptr;

#include <SFML\Graphics.hpp>

#include "sf_dll_macro.h"

/// TinyXML namespace
namespace tinyxml2
{
  class XMLElement;
}

/// Engine namespace
namespace sftile
{
class SfTilemap;
class SfObject;

/// Private engine namespace
namespace priv
{
class SfTileset;
class SfTileLayer;
class SfObjectLayer;

////////////////////////////////////////////////////////////
/// \class: SfTilemapLoader
/// \brief Class for loading and saving tile maps.
///
/// This is a private class used to load all tile maps
/// into the engine. This loader class is a friend to the
/// SfTilemap, SfTileset, SfTileLayer, and SfProperties classes.
/// This allows the class to piece together a tile map bit
/// by bit.
///
////////////////////////////////////////////////////////////

class SF_TILE_API SfTilemapLoader
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Loads a tile map from a TMX file.
  ///
  /// By navigating to the path of the TMX file, we can load
  /// and parse the file. This function then calls the other
  /// necessary functions to parse any other appropriate data.
  /// 
  /// \param _path Path to the TMX file
  /// \param _tilemap Tile map to save data to
  ///
  /// \return True if successful
  ///
  ////////////////////////////////////////////////////////////
  bool LoadTilemap(const string _path, SfTilemap& _tilemap);

private:
  ////////////////////////////////////////////////////////////
  /// \brief Parses a tileset from TMX data.
  ///
  /// Parses any tileset data from the TMX file. This function
  /// is called by the LoadTilemap() method.
  ///
  /// \param _element XML element containing tileset data
  /// \param _tileset Tileset to save the data in
  ///
  /// \return True if successful
  ///
  ////////////////////////////////////////////////////////////
  bool ParseTileset(const tinyxml2::XMLElement* _element, SfTileset& _tileset);


  ////////////////////////////////////////////////////////////
  /// \brief Parses a layer from TMX data.
  ///
  /// Parses a TMX layer by deciding which type of layer it
  /// is and calling the correct parser function.
  ///
  /// \param _element XML element containing layer data
  ///
  /// \return True if successful
  ///
  ////////////////////////////////////////////////////////////
  bool ParseTileLayer(const tinyxml2::XMLElement* _element, SfTileLayer& _tile_layer);


  ////////////////////////////////////////////////////////////
  ///
  ///
  ///
  ///
  ////////////////////////////////////////////////////////////
  bool ParseXmlTileLayer(const tinyxml2::XMLElement* _element, SfTileLayer& _tile_layer);


  ////////////////////////////////////////////////////////////
  ///
  ///
  ///
  ///
  ////////////////////////////////////////////////////////////
  bool ParseBase64TileLayer(const tinyxml2::XMLElement* _element, SfTileLayer& _tile_layer);


  ////////////////////////////////////////////////////////////
  ///
  ///
  ///
  ///
  ////////////////////////////////////////////////////////////
  bool ParseCsvTileLayer(const tinyxml2::XMLElement* _element, SfTileLayer& _tile_layer);


  ////////////////////////////////////////////////////////////
  /// \brief Parses an object layer from TMX data.
  ///
  /// \param _element XML element containing object layer data
  ///
  /// \return True if successful
  ///
  ////////////////////////////////////////////////////////////
  bool ParseObjectLayer(const tinyxml2::XMLElement* _element, SfObjectLayer& _object_layer);


  ////////////////////////////////////////////////////////////
  /// \brief Parses an object from TMX data.
  ///
  /// \param _element XML element containing object data
  ///
  /// \return True if successful
  ///
  ////////////////////////////////////////////////////////////
  bool ParseObject(const tinyxml2::XMLElement* _element, SfObject& _object);

};

}

}

#endif // SF_TILEMAP_LOADER