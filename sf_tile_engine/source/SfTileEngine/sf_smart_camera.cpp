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
}


///////////////////////////////////////////////////////////
void SfSmartCamera::SetCenterPosition(const float _x, const float _y)
{
  float x = _x - size.x / 2.f;
  float y = _y - size.y / 2.f;

  position = sf::Vector2f(x, y);
}


///////////////////////////////////////////////////////////
void SfSmartCamera::MoveTo(const float _x, const float _y)
{
  target = sf::Vector2f(_x, _y);
}


///////////////////////////////////////////////////////////
void SfSmartCamera::MoveCenterTo(const float _x, const float _y)
{
  float x = _x - size.x / 2.f;
  float y = _y - size.y / 2.f;

  target = sf::Vector2f(x, y);
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
  {

  }

  CalculatePosition();
}


///////////////////////////////////////////////////////////
void SfSmartCamera::HandleEvents(sf::Event& _evt)
{

}


///////////////////////////////////////////////////////////
void SfSmartCamera::CalculatePosition()
{

}

}