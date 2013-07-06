#include "..\..\include\SfTileEngine\sf_smart_camera.h"

namespace sftile
{
  
///////////////////////////////////////////////////////////
SfSmartCamera::SfSmartCamera(const float _width, const float _height)
  : SfCamera(_width, _height)
  , tracking_mode(SF_TRACK_OFF)
  , tracked_up(Key::W)
  , tracked_down(Key::S)
  , tracked_left(Key::A)
  , tracked_right(Key::D)
  , tracked_button(MButton::Left)
{}


///////////////////////////////////////////////////////////
SfSmartCamera::SfSmartCamera(const SfSmartCamera& _copy)
  : SfCamera(_copy)
  , tracking_mode(_copy.tracking_mode)
  , tracked_up(_copy.tracked_up)
  , tracked_down(_copy.tracked_down)
  , tracked_left(_copy.tracked_left)
  , tracked_right(_copy.tracked_right)
  , tracked_button(_copy.tracked_button)
{}


///////////////////////////////////////////////////////////
SfSmartCamera& SfSmartCamera::operator=(const SfSmartCamera& _copy)
{
  if (this != &_copy)
  {
    SfCamera::operator=(_copy);

    SfSmartCamera temp(_copy);

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
void SfSmartCamera::SetPosition(const float _x, const float _y)
{
  position = sf::Vector2f(_x, _y);
  target = sf::Vector2f(_x, _y);

  need_update = true;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::SetCenterPosition(const float _x, const float _y)
{
  float x = _x - size.x / 2.f;
  float y = _y - size.y / 2.f;

  position = sf::Vector2f(x, y);
  target = sf::Vector2f(x, y);

  need_update = true;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::MoveTo(const float _x, const float _y)
{
  target = sf::Vector2f(_x, _y);

  need_update = true;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::MoveCenterTo(const float _x, const float _y)
{
  float x = _x - size.x / 2.f;
  float y = _y - size.y / 2.f;

  target = sf::Vector2f(x, y);

  need_update = true;
}


///////////////////////////////////////////////////////////
const sf::Vector2f SfSmartCamera::GetPosition()
{
  return position;
}


///////////////////////////////////////////////////////////
const sf::Vector2f SfSmartCamera::GetCenterPosition()
{
  sf::Vector2f center(position.x + size.x / 2.f, position.y + size.y / 2.f);
  return center;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::SetTrackMode(const SfTrackingMode _mode)
{
  tracking_mode = _mode;
  cout << "Tracking Mode: " << tracking_mode << endl;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::SetTrackedKeys(const Key _up, const Key _down, const Key _left, const Key _right)
{
  tracked_up = _up;
  tracked_down = _down;
  tracked_left = _left;
  tracked_right = _right;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::SetTrackedMouseButton(MButton _button)
{
  tracked_button = _button;
}


///////////////////////////////////////////////////////////
void SfSmartCamera::Update()
{
  if (tracking_mode == SF_TRACK_KEYS_PRESS)
    HandleTrackKeysPress();

  if (need_update)
    CalculatePosition();
}


///////////////////////////////////////////////////////////
void SfSmartCamera::HandleEvents(sf::Event& _evt)
{
  if (tracking_mode == SF_TRACK_MOUSE_CLICK)
    HandleTrackMouseClick(_evt);
}


///////////////////////////////////////////////////////////
void SfSmartCamera::CalculatePosition()
{
  const float x_dist = static_cast<float>(target.x - position.x);
  const float y_dist = static_cast<float>(target.y - position.y);

  const float distance = sqrt(pow(x_dist, 2) + pow(y_dist, 2));

  /// A spin-off of Xeno's Paradox prohibits us from reaching the
  /// target, so we can counter that by giving up when we are within 1 pixel. :)
  if (distance <= 1.f)
  {
    position = target;
    need_update = false;
  }
  else
  {
    float velocity = distance / 60.f;

    /// If the velocity falls below 1.0, we won't reach the North Pole
    if (velocity < 1.f)
      velocity = 1.f;

    const float velocity_x = x_dist * (velocity / distance);
    const float velocity_y = y_dist * (velocity / distance);

    position.x += velocity_x;
    position.y += velocity_y;
  }
}


///////////////////////////////////////////////////////////
void SfSmartCamera::HandleTrackKeysPress()
{
  float x = GetPosition().x;
  float y = GetPosition().y;

  if (sf::Keyboard::isKeyPressed(tracked_up))
  {
    y += 1.f;
    SetPosition(x, y);
  }
  if (sf::Keyboard::isKeyPressed(tracked_down))
  {
    y -= 1.f;
    SetPosition(x, y);
  }
  if (sf::Keyboard::isKeyPressed(tracked_left))
  {
    x += 1.f;
    SetPosition(x, y);
  }
  if (sf::Keyboard::isKeyPressed(tracked_right))
  {
    x -= 1.f;
    SetPosition(x, y);
  }
}


///////////////////////////////////////////////////////////
void SfSmartCamera::HandleTrackMouseClick(sf::Event& _evt)
{
  if (_evt.type == sf::Event::MouseButtonPressed)
  {
    const sf::Vector2f mouse_position = GetPosition() + sf::Vector2f(_evt.mouseButton.x, _evt.mouseButton.y);

    MoveCenterTo(mouse_position.x, mouse_position.y);
  }
}

}