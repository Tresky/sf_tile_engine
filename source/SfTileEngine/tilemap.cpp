#include "..\..\include\SfTileEngine\tilemap.h"

#include "..\..\extlibs\TinyXML\tinyxml2.h"
  using namespace tinyxml2;

#include "..\..\include\SfTileEngine\camera.h"

namespace sftile
{

////////////////////////////////////////////////////////////
Tilemap::Tilemap()
	: camera(nullptr)
	, tileset()
	, layers()
	, map_dimensions(-1, -1)
	, tile_dimensions(32, 32)
	, version(1.0)
{}


////////////////////////////////////////////////////////////
Tilemap::Tilemap(const Tilemap& _copy)
	: camera(_copy.camera)
	, tileset(_copy.tileset)
	, map_dimensions(_copy.map_dimensions)
	, tile_dimensions(_copy.tile_dimensions)
	, version(_copy.version)
{
	for (unsigned int i = 0; i < _copy.layers.size(); ++i)
		layers.push_back(unique_ptr<priv::Layer>(new priv::Layer(*_copy.layers[i])));
}


Tilemap::Tilemap(Tilemap&& _copy)
	: camera(std::move(_copy.camera))
	, tileset(std::move(_copy.tileset))
	, map_dimensions(std::move(_copy.map_dimensions))
	, tile_dimensions(std::move(_copy.tile_dimensions))
	, version(std::move(_copy.version))
{
	for (unsigned int i = 0; i < _copy.layers.size(); ++i)
		layers.push_back(std::move(_copy.layers[i]));
}


////////////////////////////////////////////////////////////
Tilemap& Tilemap::operator=(const Tilemap& _copy)
{
	if (this != &_copy)
	{
		Tilemap temp(_copy);

		std::swap(camera, temp.camera);
		std::swap(tileset, temp.tileset);
		std::swap(map_dimensions, temp.map_dimensions);
		std::swap(tile_dimensions, temp.tile_dimensions);
		std::swap(version, temp.version);

		for (unsigned int i = 0; i < temp.layers.size(); ++i)
			layers.push_back(unique_ptr<priv::Layer>(new priv::Layer(*_copy.layers[i])));
	}

	return *this;
}


////////////////////////////////////////////////////////////
Tilemap& Tilemap::operator=(Tilemap&& _copy)
{
	if (this != &_copy)
	{
		camera = std::move(_copy.camera);
		tileset = std::move(_copy.tileset);
		map_dimensions = std::move(_copy.map_dimensions);
		tile_dimensions = std::move(_copy.tile_dimensions);
		version = std::move(_copy.version);

		for (unsigned int i = 0; i < _copy.layers.size(); ++i)
			layers.push_back(std::move(_copy.layers[i]));
	}

	return *this;
}

////////////////////////////////////////////////////////////
Tilemap::~Tilemap()
{
	camera = nullptr;
}


////////////////////////////////////////////////////////////
void Tilemap::RegisterCamera(Camera* _camera)
{
	camera = _camera;
}


////////////////////////////////////////////////////////////
void Tilemap::HandleEvents(sf::Event _evt)
{
	camera->HandleEvents(_evt);
}


////////////////////////////////////////////////////////////
void Tilemap::Update()
{
	camera->Update();
}


////////////////////////////////////////////////////////////
void Tilemap::Render(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < layers.size(); ++i)
	{
		if (layers[i]->GetType() == "tile")
			RenderTileLayer(_window, *layers[i].get());
		else if (layers[i]->GetType() == "object")
			RenderObjectLayer(_window, *layers[i].get());
		else if (layers[i]->GetType() == "image")
			RenderImageLayer(_window, *layers[i].get());
	}
}


////////////////////////////////////////////////////////////
void Tilemap::RenderTileLayer(sf::RenderWindow& _window, priv::Layer& _layer)
{
	sf::Vector2i offset = camera->GetTileOffset(tile_dimensions.x, tile_dimensions.y);
	sf::IntRect bounds = camera->GetBounds(tile_dimensions.x, tile_dimensions.y);

	// These for loops ensure that we don't render anything
	// outside of the camera's view. That would be a waste of
	// the processor's power.
	for (int y = 0, tile_y = bounds.top; y < bounds.height; ++y, ++tile_y)
	{
		for (int x = 0, tile_x = bounds.left; x < bounds.width; ++x, ++tile_x)
		{
			// Guard against trying to render outside of
			// the map. There lie dragons.
			if (tile_x < 0 || tile_y < 0)
				continue;
			if (tile_x >= map_dimensions.x || tile_y >= map_dimensions.y)
				continue;

			// Downcast the layer from Layer to TileLayer
			priv::TileLayer* tile_layer = dynamic_cast<priv::TileLayer*>(&_layer);
			int gid = tile_layer->GetTileGID(tile_x, tile_y);

			// GID 0 is a blank tile, so don't render
			if (gid == 0)
				continue;

			// Adjust the tile coordinates by the size of the tiles
			// and by substracting how much the camera is offset from the
			// tile grid.
			const float pos_x = static_cast<float>(x * tile_dimensions.x - offset.x);
			const float pos_y = static_cast<float>(y * tile_dimensions.y - offset.y);
			tileset.RenderTile(_window, gid, pos_x, pos_y);
		}
	}
}


void Tilemap::RenderObjectLayer(sf::RenderWindow& _window, priv::Layer& _layer)
{
	sf::Vector2i offset = camera->GetTileOffset(tile_dimensions.x, tile_dimensions.y);
	sf::IntRect bounds = camera->GetBounds(tile_dimensions.x, tile_dimensions.y);

	// Downcast the layer from Layer to ObjectLayer
	priv::ObjectLayer* object_layer = dynamic_cast<priv::ObjectLayer*>(&_layer);
	for (int i = 0; i < object_layer->GetNumObjects(); ++i)
	{
		Object* object = object_layer->GetObject(i);

		sf::Vector2i position = object->GetPosition();

		// The camera bounds is given to us in tiles, so we
		// need to convert it to pixels because the objects
		// in Tiled use pixels as their positional unit. This is
		// because they can exist between tiles.
		sf::IntRect bounds_px(bounds.left, bounds.top, bounds.width * tile_dimensions.x, bounds.height * tile_dimensions.y);

		if (bounds_px.contains(position))
		{
			string type = object->GetType();
			if (type == "tile")
			{
				int gid = object->GetGid();

				// The origin of the objects in Tiled is in the bottom left corner
				// for some odd reason, so we have to adjust for that here.
				const float pos_x = (const float)object->GetPosition().x - camera->GetPosition().x;
				const float pos_y = (const float)object->GetPosition().y - camera->GetPosition().y - tile_dimensions.y;

				tileset.RenderTile(_window, gid, pos_x, pos_y);
			}
		}
	}
}


void Tilemap::RenderImageLayer(sf::RenderWindow& _window, priv::Layer& _layer)
{

}

}