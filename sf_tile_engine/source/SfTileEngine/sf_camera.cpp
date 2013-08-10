#include "..\..\include\SfTileEngine\sf_camera.h"

/// Library namespace
namespace sftile
{

///////////////////////////////////////////////////////////
SfCamera::SfCamera(const float _width, const float _height)
  : position(0.f, 0.f)
  , target(0.f, 0.f)
  , size(_width, _height)
  , bounds(0, 0, static_cast<int>(_width), static_cast<int>(_height))
  , need_update(false)
{}


///////////////////////////////////////////////////////////
SfCamera::SfCamera(const SfCamera& _copy)
  : position(_copy.position)
  , target(_copy.target)
  , size(_copy.size)
  , bounds(_copy.bounds)
  , need_update(_copy.need_update)
{}


///////////////////////////////////////////////////////////
SfCamera& SfCamera::operator=(const SfCamera& _copy)
{
  if (this != &_copy)
  {
    position = _copy.position;
    target = _copy.target;
    size = _copy.size;
    bounds = _copy.bounds;
    need_update = _copy.need_update;
  }

  return *this;
}


///////////////////////////////////////////////////////////
const sf::Vector2i SfCamera::GetTileOffset(const int _tile_width, const int _tile_height)
{
  sf::Vector2i temp;
  temp.x = static_cast<int>(position.x) % _tile_width;
  temp.y = static_cast<int>(position.y) % _tile_height;
  return temp;
}


///////////////////////////////////////////////////////////
const sf::IntRect SfCamera::GetBounds(const int _tile_width, const int _tile_height)
{
  int tile_x = 0;
  int tile_y = 0;
  int tiles_across = 0;
  int tiles_down = 0;

  sf::IntRect rect(0, 0, 0, 0);

  if (_tile_width != 0 && _tile_height != 0)
  {
    tile_x = static_cast<int>(position.x / _tile_width);
    tile_y = static_cast<int>(position.y / _tile_height);

    /// If the whole size of the camera is not divisible by the tile
    /// size, we need to add one more tile to the bounds.
    /// We also have to add one to the numbers to make the tile count
    /// begin at 1 as opposed to 0.
    tiles_across = static_cast<int>(size.x / _tile_width) + 2;
    tiles_down = static_cast<int>(size.y / _tile_height) + 2;

    /// If we are not perfectly positioned over the tiles, we need to
    /// add one more tile to the frame to make sure no black is shown.
    if (static_cast<int>(position.x) % _tile_width != 0)
      ++tiles_across;
    if (static_cast<int>(position.y) % _tile_height != 0)
      ++tiles_down;
  }

  rect = sf::IntRect(tile_x, tile_y, tiles_across, tiles_down);
  return rect;
}

}