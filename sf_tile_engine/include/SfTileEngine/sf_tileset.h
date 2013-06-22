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

 #ifndef SF_TILESET_H
 #define SF_TILESET_H

 #include <iostream>
  using std::cout;
  using std::endl;
 #include <vector>
  using std::vector;
#include <memory>
  using std::unique_ptr;

#include <SFML\Graphics.hpp>

/// Engine namespace
namespace sftile
{
class SfProperties;

/// Private engine namespace
namespace priv
{
class SfTile;
class SfTilemapLoader;

////////////////////////////////////////////////////////////
/// \class SfTileset
/// \brief Holds tileset data in the form of sf::Rect's
///
/// "Put your outdoor work in order and get your fields
/// ready; after that, build your house." -Proverbs 24:27
///
/// We store tileset data in this class. This allows us
/// to build layers out of the tiles in this class.
/// We store the tiles in the form of sf::Rect's and then
/// render each tile individual as a sub-rectangle of the
/// entire tileset image.
///
////////////////////////////////////////////////////////////
class SfTileset
{
friend class priv::SfTilemapLoader;
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Constructs an empty tileset.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfTileset();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing tileset.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfTileset(const SfTileset& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing tileset.
  ///
  ////////////////////////////////////////////////////////////
  SfTileset& operator=(const SfTileset& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Destructor
  ///
  ////////////////////////////////////////////////////////////
  ~SfTileset();


  ////////////////////////////////////////////////////////////
  /// \brief Returns a pointer to a tile with a specified
  ///        GID.
  ///
  /// \param _id GID of the desired tile
  /// \return Pointer to tile if tile exists with GID
  ///
  ////////////////////////////////////////////////////////////
  SfTile* GetTile(const unsigned int _id);


  ////////////////////////////////////////////////////////////
  /// \brief Returns the number of tiles in the tileset.
  ///
  /// \return Number of tiles in the tileset
  ///
  ////////////////////////////////////////////////////////////
  const int GetNumTiles();


  ////////////////////////////////////////////////////////////
  /// \brief Renders a specific tile in the tileset at a
  ///        specified position.
  ///
  /// \param _window SFML window to render to
  /// \param _id GID of tile to render
  /// \param _x X position to render tile at (in tiles)
  /// \param _y Y position to render tile at (in tiles)
  ///
  ////////////////////////////////////////////////////////////
  void RenderTile(sf::RenderWindow& _window, const unsigned int _id, const int _x, const int _y);

private:
  /// Dimensions of the tiles in pixels
  sf::Vector2i tile_dimensions;;


  /// Vector of tiles
  vector< unique_ptr<SfTile> > tiles;


  /// Texture of the entire tileset in full
  sf::Texture tileset_image;


  /// Properties of the tileset
  //unique_ptr<SfProperties> properties;
};

}

}

#endif // SF_TILESET_H