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

#ifndef SF_TILEMAP_H
#define SF_TILEMAP_H

#include <iostream>
  using std::cout;
  using std::endl;
#include <memory>
  using std::unique_ptr;
  using std::shared_ptr;
#include <string>
  using std::string;
#include <deque>
  using std::deque;

#include <SFML\Graphics.hpp>

/// Engine namespace
namespace sftile
{
class SfCamera;

/// Private engine namespace
namespace priv
{
class SfTileset;
class SfLayer;
class SfTilemapLoader;

/// Orientation of the tile map.
enum TilemapOrientation
{
  SFTILE_ORIENT_UNSUPPORTED = -1,
  SFTILE_ORIENT_ORTHOGONAL = 0,
};

/// Encoding of the tile map data.
enum TilemapEncoding
{
  SFTILE_ENCODING_UNSUPPORTED = -1,
  SFTILE_ENCODING_XML = 0,
  SFTILE_ENCODING_BASE64,
  SFTILE_ENCODING_CSV
};

/// Compression of the tile map data.
enum TilemapCompression
{
  SFTILE_COMPRESS_NONE = 0,
  SFTILE_COMPRESS_GZIP,
  SFTILE_COMPRESS_ZLIB
};

}

////////////////////////////////////////////////////////////
/// \class: SfTilemap
/// \brief Class for storing and interacting with tile maps
///
/// This class is used to store the data of a tile map.
/// Duh! However, you can't load it directly. You always
/// need to load the tile maps through your SfWorld object.
/// This is so that your world can know about this tile
/// map and make sure it gets rendered and updated.
///
/// While you are loading the tile map you can save a
/// pointer to the that tile map in one of these. This
/// will allow you to later use data from the to and add
/// objects to it, etc.
///
/// Proper Usage:
/// -- Loading Method --
/// SfTilemap* tilemap = world.LoadTilemap("testmap", "res\\maps\\test_map.tmx");
///
////////////////////////////////////////////////////////////

class SfTilemap
{
friend class priv::SfTilemapLoader;
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Constructs an empty tile map.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfTilemap();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing tile map.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfTilemap(const SfTilemap& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing tile map.
  ///
  ////////////////////////////////////////////////////////////
  SfTilemap& operator=(const SfTilemap& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Destructor
  ///
  /// Destroys the tile map.
  ///
  ////////////////////////////////////////////////////////////
  ~SfTilemap();


  ////////////////////////////////////////////////////////////
  /// \brief Registers a camera with the tile map by saving
  ///        a pointer to the camera object.
  ///
  /// \param _camera Pointer to the camera object
  ///
  ////////////////////////////////////////////////////////////
  void RegisterCamera(SfCamera* _camera);


  ////////////////////////////////////////////////////////////
  /// \brief Handles any events referring to the tile map.
  ///
  /// \param _evt SFML event object
  ///
  ////////////////////////////////////////////////////////////
  void HandleEvents(sf::Event _evt);


  ////////////////////////////////////////////////////////////
  /// \brief Updates anything in the tile map that needs
  ///        updating.
  ///
  ////////////////////////////////////////////////////////////
  void Update();


  ////////////////////////////////////////////////////////////
  /// \brief Renders the tile map.
  ///
  /// \param _window SFML window to render to
  ///
  ////////////////////////////////////////////////////////////
  void Render(sf::RenderWindow& _window);


private:
  /// Camera registered to the tile map
  sftile::SfCamera* camera;


  /// Tileset to hold all tilesets in this tile map
  shared_ptr<priv::SfTileset> tileset;


  /// FIFO deque holds all tile, image, and object layers
  deque< unique_ptr<priv::SfLayer> > layers;


  /// Dimensions of the tile map in tiles
  sf::Vector2i map_dimensions;


  /// Dimensions of the tiles in the map in pixels
  sf::Vector2i tile_dimensions;


  /// Version of TMX being used
  float version;


  /// Orientation of the tile map
  priv::TilemapOrientation orientation;


  /// Encoding of the tile map
  priv::TilemapEncoding encoding;


  /// Compression of the tile map
  priv::TilemapCompression compression;
};

}

#endif // SF_TILEMAP_H