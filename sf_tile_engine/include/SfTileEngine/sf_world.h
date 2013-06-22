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

#ifndef SF_WORLD_H
#define SF_WORLD_H

#include <iostream>
  using std::cout;
  using std::endl;
#include <string>
  using std::string;
#include <map>
  using std::map;
#include <memory>
  using std::unique_ptr;

#include <SFML\Graphics.hpp>

/// Engine namespace
namespace sftile
{
class SfTilemap;

/// Private engine namespace
namespace priv
{
class SfTilemapLoader;
}

////////////////////////////////////////////////////////////
/// \class SfWorld
/// \brief Provides a class to load and interact with
///        your tilemaps.
///
/// "For God so loved the world that he gave his one
/// and only son, that whoever believes in him shall not
/// perish but have eternal life." -John 3:16 (NIV)
/// 
/// This class is the overhead manager for the tile engine.
/// It provides a place to store and access all of the 
/// tilemaps that are being used. This class also takes care
/// to keep track of which tilemap is currently in use and
/// automatically draws and updates only that tilemap when
/// you call the predefined HandleEvents(), Update(), and
/// Render() methods. 
///
/// You only need one of these objects for
/// the engine to work, but I don't see why you can't use
/// more (although I see no point).
///
/// Proper Usage
/// \code
/// // Create SfWorld object
/// SfWorld world;
///
/// // Load a tilemap and save it in the world.
/// // This also saves a pointer to that tilemap.
/// SfTilemap* tilemap = world.LoadTilemap("testmap", "res\\maps\\test_map.tmx");
/// if (!tilemap)
/// {
///   cout << "Failed to load tilemap" << endl;
///   return -1;
/// }
///
/// while (window.isOpen())
/// {
///   sf::Event evt;
///   while (window.pollEvent(evt))
///   {
///     // Handle any events passed into the engine.
///     world.HandleEvents(evt);
///   }
///   // Update the engine.
///   world.Update();
///
///   window.clear();
///
///   // Render the engine.
///   world.Render(&window);
///
///   window.display();
/// }
/// \endcode
////////////////////////////////////////////////////////////

class SfWorld
{
public:
	////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Creates an empty world object.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfWorld();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing world object.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfWorld(const SfWorld& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing world object.
  ///
  ////////////////////////////////////////////////////////////
  SfWorld& operator=(const SfWorld& _copy);


  ///////////////////////////////////////////////////////////
  /// \brief Destructor
  ///
  ///////////////////////////////////////////////////////////
  ~SfWorld();


  ////////////////////////////////////////////////////////////
  /// \brief Loads a tile map from a TMX file.
  ///
  /// The tile ap is stored as an instantiated object here
  /// in the world object. However, a pointer to that
  /// specific tile map is stored outside where the user
  /// can access it, so they can maintain control over 
  /// their tile map.
  ///
  /// \param _id Unique string ID of the tile map
  /// \param _path Filepath to the TMX file
  ///
  /// \return Pointer to the loaded tile map if successful
  ///
  ////////////////////////////////////////////////////////////
  SfTilemap* LoadTilemap(string _id, string _path);


  ////////////////////////////////////////////////////////////
  /// \brief Return a pointer to a previously loaded 
  ///        tile map.
  ///
  /// \param _id Unique string ID of the tile map
  /// \return Pointer to the tile map if successful
  ///
  ////////////////////////////////////////////////////////////
  SfTilemap* GetTilemap(string _id);


  ////////////////////////////////////////////////////////////
  /// \brief Handles any events referring to the tile engine.
  /// 
  /// \param _evt SFML event object
  ///
  ////////////////////////////////////////////////////////////
  void HandleEvents(sf::Event _evt);


  ////////////////////////////////////////////////////////////
  /// \brief Updates anything in the tile engine that needs
  ///        updating.
  ///
  ////////////////////////////////////////////////////////////
  void Update();


  ////////////////////////////////////////////////////////////
  /// \brief Renders the currently visible tile map.
  ///
  /// \param _window SFML window to render to
  ///
  ////////////////////////////////////////////////////////////
  void Render(sf::RenderWindow& _window);


private:
  ////////////////////////////////////////////////////////////
  /// \brief Loads a tile map from a TMX file.
  ///
  /// \param _path Filepath to the TMX file
  ///
  /// \return True if loading was successful
  ///
  ////////////////////////////////////////////////////////////
  bool LoadFromTMX(string _path);


  ////////////////////////////////////////////////////////////
  /// \brief Checks for the existence of a tile map with
  ///        a specific string ID.
  ///
  /// \param _id Unique string ID of the tile map
  ///
  /// \return True if tile map exists
  ///
  ////////////////////////////////////////////////////////////
  bool MapExists(string _id);


  /// Takes care of loading the tile maps
  unique_ptr<priv::SfTilemapLoader> loader;


  /// Tile maps
  map<string, unique_ptr<SfTilemap> > tilemaps;


  /// String ID of currently visible tile map
  string current_id;
};

}

#endif // SF_WORLD_H