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

  // Create a Smart Camera object and set the size of the camera to
  // the size of the window.
  sftile::SfSmartCamera camera(800.f, 600.f);
  // Register the camera to the tile map by passing a pointer.
  test_map->RegisterCamera(&camera);

  // Tracking mode is, by default, set to SF_TRACK_OFF, so
  // we set the current tracking mode to SF_TRACK_KEYS_PRESS.
  // This will track the W, A, S, and D keys for directional
  // movement of the tile map. You can, however, change the keys
  // with the function SfSmartCamera::SetTrackedKeys().
  camera.SetTrackMode(sftile::SfTrackingMode::SF_TRACK_KEYS_PRESS);

  // Here we create a clock for FPS management.
  sf::Clock clock;
  // I want my game to run at 60 frames per second, so
  // I calculate the amount of milliseconds one frame will
  // consume.
  sf::Time frame_time = sf::milliseconds(1000 / 60.f);
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

    // Using the calculated frame time, we subtract the amount
    // of time the previous frame took and have the thread sleep
    // the rest of the time.
    sf::Time delay = frame_time - clock.restart();
    sf::sleep(delay);
  }

  return 0;
}