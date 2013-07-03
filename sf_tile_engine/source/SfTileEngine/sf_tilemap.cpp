#include "..\..\include\SfTileEngine\sf_tilemap.h"

#include "..\..\extlibs\TinyXML\tinyxml2.h"
  using namespace tinyxml2;

#include "..\..\include\SfTileEngine\sf_tileset.h"
#include "..\..\include\SfTileEngine\sf_layer.h"
#include "..\..\include\SfTileEngine\sf_camera.h"

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
    std::swap(layers, temp.layers);
    std::swap(map_dimensions, temp.map_dimensions);
    std::swap(tile_dimensions, temp.tile_dimensions);

    tileset.reset(new priv::SfTileset(*_copy.tileset));
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
  camera->HandleEvents(_evt);
}


////////////////////////////////////////////////////////////
void SfTilemap::Update()
{
  camera->Update();
}


////////////////////////////////////////////////////////////
void SfTilemap::Render(sf::RenderWindow& _window)
{
  sf::Vector2i offset = camera->GetTileOffset(tile_dimensions.x, tile_dimensions.y);
  sf::IntRect bounds = camera->GetBounds(tile_dimensions.x, tile_dimensions.y);

  for (int y = 0, tile_y = bounds.top; y < bounds.height; ++y, ++tile_y)
    for (int x = 0, tile_x = bounds.left; x < bounds.width; ++x, ++tile_x)
    {

      for (unsigned int l = 0; l < layers.size(); ++l)
      {
        if (tile_x < 0 || tile_y < 0)
          continue;
        if (tile_x >= map_dimensions.x || tile_y >= map_dimensions.y)
          continue;

        int gid = layers.at(l)->GetTileGID(tile_x, tile_y);

        if (gid == 0)
          continue;

        const float pos_x = static_cast<float>(x * tile_dimensions.x - offset.x);
        const float pos_y = static_cast<float>(y * tile_dimensions.y - offset.y);
        tileset->RenderTile(_window, gid, pos_x, pos_y);
      }
    }
}

}