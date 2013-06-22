#include "..\..\include\SfTileEngine\sf_tilemap.h"

#include "..\..\extlibs\TinyXML\tinyxml2.h"
  using namespace tinyxml2;

#include "..\..\include\SfTileEngine\sf_tileset.h"
#include "..\..\include\SfTileEngine\sf_layer.h"

namespace sftile
{

////////////////////////////////////////////////////////////
SfTilemap::SfTilemap()
  : camera(nullptr)
  , tileset(new priv::SfTileset())
  , layers()
  , map_dimensions(-1, -1)
  , tile_dimensions(32, 32)
  , version(1.0)
{}


////////////////////////////////////////////////////////////
SfTilemap::SfTilemap(const SfTilemap& _copy)
  : camera(_copy.camera)
  , tileset(new priv::SfTileset(*_copy.tileset))
  , map_dimensions(_copy.map_dimensions)
  , tile_dimensions(_copy.tile_dimensions)
  , version(_copy.version)
{
  for (unsigned int i = 0; i < _copy.layers.size(); ++i)
    layers.emplace_back( unique_ptr<priv::SfLayer>(new priv::SfLayer(*_copy.layers.at(i).get())) );
}


////////////////////////////////////////////////////////////
SfTilemap& SfTilemap::operator=(const SfTilemap& _copy)
{
  if (this != &_copy)
  {
    SfTilemap temp(_copy);

    std::swap(camera, temp.camera);
    std::swap(tileset, temp.tileset);
    std::swap(layers, temp.layers);
    std::swap(map_dimensions, temp.map_dimensions);
    std::swap(tile_dimensions, temp.tile_dimensions);
  }

  return *this;
}


////////////////////////////////////////////////////////////
SfTilemap::~SfTilemap()
{
  camera = nullptr;
}


////////////////////////////////////////////////////////////
void SfTilemap::RegisterCamera(SfCamera* _camera)
{
  camera = _camera;
}


////////////////////////////////////////////////////////////
void SfTilemap::HandleEvents(sf::Event _evt)
{

}


////////////////////////////////////////////////////////////
void SfTilemap::Update()
{

}


////////////////////////////////////////////////////////////
void SfTilemap::Render(sf::RenderWindow& _window)
{
  deque< unique_ptr<priv::SfLayer> >::iterator iter;
  for (iter = layers.begin(); iter != layers.end(); ++iter)
    iter->get()->Render(_window);
}

}