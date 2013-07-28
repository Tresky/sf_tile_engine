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

#ifndef SF_CAMERA_H
#define SF_CAMERA_H

#include <iostream>
  using std::cout;
  using std::endl;

#include <SFML\Graphics.hpp>

#include "sf_dll_macro.h"

/// Library namespace
namespace sftile
{


////////////////////////////////////////////////////////////
/// \class SfCamera
/// \brief Handles displaying a portion of the tile map.
///
/// This class serves a few purposes. 
///
///
///
///
////////////////////////////////////////////////////////////
class SF_TILE_API SfCamera
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructor
  ///
  /// Constructs a camera from the width and height. The
  /// dimensions of the current window are typically used.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfCamera(const float _width, const float _height);


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing camera.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfCamera(const SfCamera& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing camera.
  ///
  ////////////////////////////////////////////////////////////
  SfCamera& operator=(const SfCamera& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Jumps the top left of the camera to a specific
  ///        position.
  ///
  /// \param _x X coordinate of the new position
  /// \param _y Y coordinate of the new position
  ///
  ////////////////////////////////////////////////////////////
  virtual void SetPosition(const float _x, const float _y) = 0;


  ////////////////////////////////////////////////////////////
  /// \brief Jumps the center of the camera to a specific
  ///        position.
  ///
  /// \param _x X coordinate of the new position
  /// \param _y Y coordinate of the new position
  ///
  ////////////////////////////////////////////////////////////
  virtual void SetCenterPosition(const float _x, const float _y) = 0;


  ////////////////////////////////////////////////////////////
  /// \brief Set the target position of the top-left corner
  ///        of the camera.
  ///
  /// \param _x X coordinate of the target position
  /// \param _y Y coordinate of the target position
  ///
  ////////////////////////////////////////////////////////////
  virtual void MoveTo(const float _x, const float _y) = 0;


  ////////////////////////////////////////////////////////////
  /// \brief Set the target position of the center
  ///        of the camera.
  ///
  /// \param _x X coordinate of the target position
  /// \param _y Y coordinate of the target position
  ///
  ////////////////////////////////////////////////////////////
  virtual void MoveCenterTo(const float _x, const float _y) = 0;


  ///////////////////////////////////////////////////////////
  /// \brief Returns the current position of the top-left
  ///        corner of the camera.
  ///
  /// \return sf::Vector2f Position of the top-left corner
  ///                      of the camera
  ///
  ///////////////////////////////////////////////////////////
  virtual const sf::Vector2f GetPosition() = 0;


  ///////////////////////////////////////////////////////////
  /// \brief Returns the current position of the center of
  ///        the camera.
  ///
  /// \return sf::Vector2f Position of the center of the 
  ///                      camera
  ///
  ///////////////////////////////////////////////////////////
  virtual const sf::Vector2f GetCenterPosition() = 0;


  ///////////////////////////////////////////////////////////
  /// \brief Updates the attributes and the position of the 
  ///        camera. This method must be called once every
  ///        before rendering.
  ///
  ///////////////////////////////////////////////////////////
  virtual void Update() = 0;


  ///////////////////////////////////////////////////////////
  /// \brief Updates the camera if the current settings
  ///        require event handling. This method doesn't
  ///        need to be called unless events are needed.
  ///
  ///////////////////////////////////////////////////////////
  virtual void HandleEvents(sf::Event& _evt) = 0;


  ///////////////////////////////////////////////////////////
  ///
  ///
  ///
  ///
  ///////////////////////////////////////////////////////////
  const sf::Vector2i GetTileOffset(const int _tile_width, const int _tile_height);


  ///////////////////////////////////////////////////////////
  /// \brief Calculates the bounds around the current portion
  ///        of the map inside of the camera view.
  ///
  /// \return Bounds of the portion of the map in the camera
  ///
  ///////////////////////////////////////////////////////////
  const sf::IntRect GetBounds(const int _tile_width, const int _tile_height);

protected:
  /// Current position of the top-left corner of the camera
  sf::Vector2f position;

  /// Current target that the camera is heading towards
  sf::Vector2f target;

  /// Size of the camera in pixels (usually the size of the window)
  sf::Vector2f size;

  /// Bounds around the portion of the map that is currently in the camera
  sf::IntRect bounds;

  /// True if the position of the camera needs to be updated
  bool need_update;

private:
  ///////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// There is no need to construct an empty camera, so this
  /// will remain private.
  ///
  ///////////////////////////////////////////////////////////
  explicit SfCamera() {}
};

}

#endif // SF_CAMERA_H