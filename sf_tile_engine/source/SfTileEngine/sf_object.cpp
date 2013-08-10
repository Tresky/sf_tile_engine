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

#include "..\..\include\SfTileEngine\sf_object.h"

namespace sftile
{

////////////////////////////////////////////////////////////
SfObject::SfObject()
  : object_type(SF_OBJECT_TYPE_UNKNOWN)
  , name("")
  , string_type("")
  , position(0, 0)
  , dimensions(0, 0)
  , rotation(0.f)
  , gid(-1)
  , visible(true)
{ }


////////////////////////////////////////////////////////////
SfObject::SfObject(const SfObject& _copy)
  : object_type(_copy.object_type)
  , name(_copy.name)
  , string_type(_copy.string_type)
  , position(_copy.position)
  , dimensions(_copy.dimensions)
  , rotation(_copy.rotation)
  , gid(_copy.gid)
  , visible(_copy.visible)
{ }


////////////////////////////////////////////////////////////
SfObject& SfObject::operator=(const SfObject& _copy)
{
  if (this != &_copy)
  {
    SfObject temp(_copy);

    std::swap(object_type, temp.object_type);
    std::swap(name, temp.name);
    std::swap(string_type, temp.string_type);
    std::swap(position, temp.position);
    std::swap(dimensions, temp.dimensions);
    std::swap(rotation, temp.rotation);
    std::swap(gid, temp.gid);
    std::swap(visible, temp.visible);
  }

  return *this;
}


////////////////////////////////////////////////////////////
string SfObject::GetName()
{
  return name;
}


////////////////////////////////////////////////////////////
string SfObject::GetStringType()
{
  return string_type;
}


////////////////////////////////////////////////////////////
sf::Vector2i SfObject::GetPosition()
{
  return position;
}


////////////////////////////////////////////////////////////
sf::Vector2i SfObject::GetDimensions()
{
  return dimensions;
}


////////////////////////////////////////////////////////////
float SfObject::GetRotation()
{
  return rotation;
}


////////////////////////////////////////////////////////////
int SfObject::GetGid()
{
  return gid;
}


////////////////////////////////////////////////////////////
bool SfObject::IsVisible()
{
  return visible;
}

}