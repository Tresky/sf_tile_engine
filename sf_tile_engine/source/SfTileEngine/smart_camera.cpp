#include "..\..\include\SfTileEngine\smart_camera.h"

namespace sftile
{
  
///////////////////////////////////////////////////////////
SmartCamera::SmartCamera(const float _width, const float _height)
  : Camera(_width, _height)
  , tracking_mode(SF_TRACK_OFF)
  , tracked_up(Key::S)
  , tracked_down(Key::W)
  , tracked_left(Key::D)
  , tracked_right(Key::A)
  , tracked_button(MButton::Left)
{}


///////////////////////////////////////////////////////////
SmartCamera::SmartCamera(const SmartCamera& _copy)
  : Camera(_copy)
  , tracking_mode(_copy.tracking_mode)
  , tracked_up(_copy.tracked_up)
  , tracked_down(_copy.tracked_down)
  , tracked_left(_copy.tracked_left)
  , tracked_right(_copy.tracked_right)
  , tracked_button(_copy.tracked_button)
{}


///////////////////////////////////////////////////////////
SmartCamera& SmartCamera::operator=(const SmartCamera& _copy)
{
  if (this != &_copy)
  {
    Camera::operator=(_copy);

    SmartCamera temp(_copy);

    std::swap(tracking_mode, temp.tracking_mode);
    std::swap(tracked_up, temp.tracked_up);
    std::swap(tracked_down, temp.tracked_down);
    std::swap(tracked_left, temp.tracked_left);
    std::swap(tracked_right, temp.tracked_right);
    std::swap(tracked_button, temp.tracked_button);
  }

  return *this;
}


///////////////////////////////////////////////////////////
void SmartCamera::SetPosition(const float _x, const float _y)
{
  position = sf::Vector2f(_x, _y);
  target = sf::Vector2f(_x, _y);

  need_update = true;
}


///////////////////////////////////////////////////////////
void SmartCamera::SetCenterPosition(const float _x, const float _y)
{
  float x = _x - size.x / 2.f;
  float y = _y - size.y / 2.f;

  position = sf::Vector2f(x, y);
  target = sf::Vector2f(x, y);

  need_update = true;
}


///////////////////////////////////////////////////////////
void SmartCamera::MoveTo(const float _x, const float _y)
{
  target = sf::Vector2f(_x, _y);

  need_update = true;
}


///////////////////////////////////////////////////////////
void SmartCamera::MoveCenterTo(const float _x, const float _y)
{
  float x = _x - size.x / 2.f;
  float y = _y - size.y / 2.f;

  target = sf::Vector2f(x, y);

  need_update = true;
}


///////////////////////////////////////////////////////////
const sf::Vector2f SmartCamera::GetPosition()
{
  return position;
}


///////////////////////////////////////////////////////////
const sf::Vector2f SmartCamera::GetCenterPosition()
{
  sf::Vector2f center(position.x + size.x / 2.f, position.y + size.y / 2.f);
  return center;
}


///////////////////////////////////////////////////////////
void SmartCamera::SetTrackMode(const TrackingMode _mode)
{
  tracking_mode = _mode;
  cout << "Tracking Mode: " << tracking_mode << endl;
}


///////////////////////////////////////////////////////////
void SmartCamera::SetTrackedKeys(const Key _up, const Key _down, const Key _left, const Key _right)
{
  tracked_up = _up;
  tracked_down = _down;
  tracked_left = _left;
  tracked_right = _right;
}


///////////////////////////////////////////////////////////
void SmartCamera::SetTrackedMouseButton(MButton _button)
{
  tracked_button = _button;
}


///////////////////////////////////////////////////////////
void SmartCamera::Update()
{
  if (tracking_mode == SF_TRACK_KEYS_PRESS)
    HandleTrackKeysPress();

  else if (tracking_mode == SF_TRACK_MOUSE_CLICKDRAG)
    click_drag_initial_position = sf::Vector2f(sf::Mouse::getPosition());

  if (need_update)
    CalculatePosition();
}


///////////////////////////////////////////////////////////
void SmartCamera::HandleEvents(sf::Event& _evt)
{
  if (tracking_mode == SF_TRACK_MOUSE_CLICK)
    HandleTrackMouseClick(_evt);

  else if (tracking_mode == SF_TRACK_MOUSE_CLICKDRAG)
    HandleTrackMouseClickDrag(_evt);
}


///////////////////////////////////////////////////////////
void SmartCamera::CalculatePosition()
{
  const float x_dist = static_cast<float>(target.x - position.x);
  const float y_dist = static_cast<float>(target.y - position.y);

  const float distance = sqrt(pow(x_dist, 2) + pow(y_dist, 2));

  /// A spin-off of Xeno's Paradox prohibits us from reaching the
  /// target, so we can counter that by giving up when we are within 1 pixel.
  if (distance <= 1.f)
  {
    position = target;
    need_update = false;
  }
  else
  {
    float velocity = distance / 60.f;

    /// If our velocity falls below 1.0, we will never enter
    /// Sovngarde!
    if (velocity < 1.f)
      velocity = 1.f;

    const float velocity_x = x_dist * (velocity / distance);
    const float velocity_y = y_dist * (velocity / distance);

    position.x += velocity_x;
    position.y += velocity_y;
  }
}


///////////////////////////////////////////////////////////
void SmartCamera::HandleTrackKeysPress()
{
  float x = GetPosition().x;
  float y = GetPosition().y;

  if (sf::Keyboard::isKeyPressed(tracked_up))
  {
    y += 2.f;
    SetPosition(x, y);
  }
  if (sf::Keyboard::isKeyPressed(tracked_down))
  {
    y -= 2.f;
    SetPosition(x, y);
  }
  if (sf::Keyboard::isKeyPressed(tracked_left))
  {
    x += 2.f;
    SetPosition(x, y);
  }
  if (sf::Keyboard::isKeyPressed(tracked_right))
  {
    x -= 2.f;
    SetPosition(x, y);
  }
}


///////////////////////////////////////////////////////////
void SmartCamera::HandleTrackMouseClick(sf::Event& _evt)
{
  if (_evt.type == sf::Event::MouseButtonPressed && _evt.mouseButton.button == tracked_button)
  {
    const sf::Vector2f mouse_position = GetPosition() + sf::Vector2f(static_cast<float>(_evt.mouseButton.x),
                                                                     static_cast<float>(_evt.mouseButton.y));

    MoveCenterTo(mouse_position.x, mouse_position.y);
  }
}


///////////////////////////////////////////////////////////
/// This can be viewed on a frame by frame basis. In our 
/// Update() method, we are grabbing the mouse position 
/// at the beginning of the frame.
///
///////////////////////////////////////////////////////////
void SmartCamera::HandleTrackMouseClickDrag(sf::Event& _evt)
{
  if (sf::Mouse::isButtonPressed(tracked_button) && _evt.type == sf::Event::MouseMoved)
  {
    /// This is the current position after moving for one frame.
    const sf::Vector2f current_position = sf::Vector2f(sf::Mouse::getPosition());

    /// Calculate the distance that was moved in our one frame.
    const sf::Vector2f distance = current_position - click_drag_initial_position;

    /// Calculate the new position.
    const sf::Vector2f new_position = GetPosition() - distance;

    /// Go-go gadget!
    SetPosition(new_position.x, new_position.y);
  }
}

}