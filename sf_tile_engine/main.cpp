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

#include <iostream>

#include <SFML\Graphics.hpp>

// Include the entire engine
#include "include\sf_tile_engine.h"

using namespace std;

int main()
{
  cout << "Program started" << endl;

  // Create the SFML window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SfTileEngine Test");
  cout << "Window created" << endl;

  // Create the SfWorld object
  sftile::SfWorld world;

  // Create a pointer to an SfTilemap and set it
  // to point to a map being loaded into the SfWorld
  sftile::SfTilemap* test_map = world.LoadTilemap("test", "test.tmx");
  if (!test_map)
  {
	  cout << "Failed to load map: test_map" << endl;
	  cin.get();
	  return EXIT_FAILURE;
  }

  sftile::SfSmartCamera camera(800.f, 600.f);
  test_map->RegisterCamera(&camera);

  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt))
    {
      if (evt.type == sf::Event::Closed)
        window.close();

      // Call the event handler
      world.HandleEvents(evt);
    }

    // Update the world
    world.Update();

    window.clear();
    // Render the world
    world.Render(window);
    window.display();
  }

  return 0;
}