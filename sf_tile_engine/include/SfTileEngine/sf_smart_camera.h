#ifndef SF_SMART_CAMERA_H
#define SF_SMART_CAMERA_H

#include <iostream>
  using std::cout;
  using std::endl;

#include "sf_camera.h"
#include "sf_dll_macro.h"

/// Library namespace
namespace sftile
{

/// These names are just too dadgum long to type all the time.
typedef sf::Keyboard::Key Key;
typedef sf::Mouse::Button MButton;

/// Represents the tracking mode that the smart camera
/// is currently in.
enum SfTrackingMode
{
  SF_TRACK_OFF = 0, // Supported
  SF_TRACK_KEYS_PRESS, // Supported
  SF_TRACK_MOUSE_CLICK, // Supported
  SF_TRACK_MOUSE_CLICKDRAG, // Supported
};
  
///////////////////////////////////////////////////////////
/// \class SfSmartCamera
/// \brief A pre-made camera that comes packed with useful
///        features that are ready-to-use out of the box.
///
/// This camera is derived from the abstract base class
/// SfCamera.
///
///////////////////////////////////////////////////////////
class SF_TILE_API SfSmartCamera : public SfCamera
{
public:
  ////////////////////////////////////////////////////////////
  /// \brief Constructor
  ///
  /// Constructs a smart camera from the width and height. The
  /// dimensions of the current window are typically used.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfSmartCamera(const float _width, const float _height);


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing smart camera.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfSmartCamera(const SfSmartCamera& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing camera.
  ///
  ////////////////////////////////////////////////////////////
  SfSmartCamera& operator=(const SfSmartCamera& _copy);
  

  ////////////////////////////////////////////////////////////
  /// \brief Jumps the top left of the camera to a specific
  ///        position.
  ///
  /// \param _x X coordinate of the new position
  /// \param _y Y coordinate of the new position
  ///
  ////////////////////////////////////////////////////////////
  void SetPosition(const float _x, const float _y);


  ////////////////////////////////////////////////////////////
  /// \brief Jumps the center of the camera to a specific
  ///        position.
  ///
  /// \param _x X coordinate of the new position
  /// \param _y Y coordinate of the new position
  ///
  ////////////////////////////////////////////////////////////
  void SetCenterPosition(const float _x, const float _y);
  

  ////////////////////////////////////////////////////////////
  /// \brief Set the target position of the top-left corner
  ///        of the camera.
  ///
  /// \param _x X coordinate of the target position
  /// \param _y Y coordinate of the target position
  ///
  ////////////////////////////////////////////////////////////
  void MoveTo(const float _x, const float _y);


  ////////////////////////////////////////////////////////////
  /// \brief Set the target position of the center
  ///        of the camera.
  ///
  /// \param _x X coordinate of the target position
  /// \param _y Y coordinate of the target position
  ///
  ////////////////////////////////////////////////////////////
  void MoveCenterTo(const float _x, const float _y);


  ///////////////////////////////////////////////////////////
  /// \brief Returns the current position of the top-left
  ///        corner of the camera.
  ///
  /// \return sf::Vector2f Position of the top-left corner
  ///                      of the camera
  ///
  ///////////////////////////////////////////////////////////
  const sf::Vector2f GetPosition();


  ///////////////////////////////////////////////////////////
  /// \brief Returns the current position of the center of
  ///        the camera.
  ///
  /// \return sf::Vector2f Position of the center of the 
  ///                      camera
  ///
  ///////////////////////////////////////////////////////////
  const sf::Vector2f GetCenterPosition();


  ///////////////////////////////////////////////////////////
  /// \brief Sets the tracking mode of the smart camera.
  ///        There are, altogether, 5 options.
  ///
  /// \param _mode Tracking mode to set to the smart camera
  ///
  ///
  ///////////////////////////////////////////////////////////
  void SetTrackMode(const SfTrackingMode _mode);


  ///////////////////////////////////////////////////////////
  /// \brief Sets the keys that will be tracked by the smart
  ///        camera when the tracking mode is:
  ///        - SF_TRACK_KEYS_PRESS
  ///
  /// \param _up Tracked up key
  /// \param _down Tracked down key
  /// \param _left Tracked left key
  /// \param _right Tracked right key
  ///
  ///////////////////////////////////////////////////////////
  void SetTrackedKeys(const Key _up, const Key _down, const Key _left, const Key _right);


  ///////////////////////////////////////////////////////////
  /// \brief Sets the mouse button that will be tracked by
  ///        the smart camera when the tracking mode is:
  ///        - SF_TRACK_MOUSE_CLICK
  ///        - SF_TRACK_MOUSE_CLICKDRAG
  ///
  /// \param _button Tracked mouse button
  ///
  ///////////////////////////////////////////////////////////
  void SetTrackedMouseButton(const MButton _button);


  ///////////////////////////////////////////////////////////
  /// \brief Updates the smart camera. This method must be
  ///        called every frame despite the tracking mode.
  ///        
  /// This method is used to update the position of
  /// the camera and also used to process data about
  /// updating.
  ///
  ///////////////////////////////////////////////////////////
  void Update();


  ///////////////////////////////////////////////////////////
  /// \brief Handles all events in the smart camera. This
  ///        method only needs to be called if the current
  ///        tracking mode requires event handling.
  ///        
  /// The tracking modes that require event handling include:
  /// - SF_
  ///
  ///////////////////////////////////////////////////////////
  void HandleEvents(sf::Event& _evt);

private:
  ///////////////////////////////////////////////////////////
  /// \brief Calculates the current position that the camera
  ///        is at based on current data of movement.
  ///
  ///////////////////////////////////////////////////////////
  void CalculatePosition();


  ///////////////////////////////////////////////////////////
  /// \brief Handles calling the appropriate commands to move
  ///        the map according the the tracked keys.
  ///
  ///////////////////////////////////////////////////////////
  void HandleTrackKeysPress();


  ///////////////////////////////////////////////////////////
  /// \brief Handles calling the appropriate commands to move
  ///        the map according the the tracked mouse click.
  ///
  ///////////////////////////////////////////////////////////
  void HandleTrackMouseClick(sf::Event& _evt);


  ///////////////////////////////////////////////////////////
  /// \brief Handles calling the appropriate commands to move
  ///        the map according the the tracked mouse click.
  ///        Also tracks how far the mouse moves when the
  ///        button is depressed.
  ///
  ///////////////////////////////////////////////////////////
  void HandleTrackMouseClickDrag(sf::Event& _evt);

  ///////////////////////////////////////////////////////////
  /// \brief Handles calling the appropriate commands to
  /// continuously center the camera of a specific entity.
  ///
  ///////////////////////////////////////////////////////////
  void HandleTrackObject();

  /// Tracking mode of the smart camera
  SfTrackingMode tracking_mode;

  /// Tracked keys for use in the SF_TRACK_KEYS_PRESS mode
  Key tracked_up, tracked_down, tracked_left, tracked_right;

  /// Tracked mouse button for use in the SF_TRACK_MOUSE_CLICK, SF_TRACK_MOUSE_CLICKDRAG, and SF_TRACK_MOUSE_POSITION modes.
  MButton tracked_button;

  /// Annoying variable that is used as the initial position for the click-drag track.
  /// I couldn't think of a better way to accomplish this. Curse Sheogorath...
  sf::Vector2f click_drag_initial_position;

};

}

#endif // SF_SMART_CAMERA_H