#include "..\..\include\SfTileEngine\sf_camera.h"

/// Library namespace
namespace sftile
{

///////////////////////////////////////////////////////////
SfCamera::SfCamera(const float _width, const float _height)
  : position(0.f, 0.f)
  , target(0.f, 0.f)
  , size(_width, _height)
  , need_update(false)
{}


///////////////////////////////////////////////////////////
SfCamera::SfCamera(const SfCamera& _copy)
  : position(_copy.position)
  , target(_copy.target)
  , size(_copy.size)
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
    need_update = _copy.need_update;
  }

  return *this;
}

}