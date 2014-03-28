////////////////////////////////////////////////////////////
/// SfTileEngine: C++/SFML Tile Engine
/// Copyright (C) 2014 Tyler Petresky
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

#include "..\..\include\SfTileEngine\tile_layer.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

////////////////////////////////////////////////////////////
TileLayer::TileLayer()
	: Layer()
	, name("")
	, tile_gids()
	, layer_dimensions(-1, -1)
{}


////////////////////////////////////////////////////////////
TileLayer::TileLayer(const TileLayer& _copy)
	: Layer(_copy)
	, name(_copy.name)
	, tile_gids(_copy.tile_gids)
	, layer_dimensions(_copy.layer_dimensions)
{}


////////////////////////////////////////////////////////////
TileLayer::TileLayer(TileLayer&& _copy)
	: Layer(std::move(_copy))
	, name(std::move(_copy.name))
	, tile_gids(std::move(_copy.tile_gids))
	, layer_dimensions(std::move(_copy.layer_dimensions))
{}


////////////////////////////////////////////////////////////
TileLayer& TileLayer::operator=(const TileLayer& _copy)
{
	if (this != &_copy)
	{
		Layer::operator=(_copy);

		TileLayer temp(_copy);

		std::swap(name, temp.name);
		std::swap(tile_gids, temp.tile_gids);
		std::swap(layer_dimensions, temp.layer_dimensions);
	}

	return *this;
}


////////////////////////////////////////////////////////////
TileLayer& TileLayer::operator=(TileLayer&& _copy)
{
	if (this != &_copy)
	{
		Layer::operator=(std::move(_copy));

		TileLayer temp(_copy);

		name = std::move(temp.name);
		tile_gids = std::move(temp.tile_gids);
		layer_dimensions = std::move(temp.layer_dimensions);
	}

	return *this;
}


////////////////////////////////////////////////////////////
int TileLayer::GetTileGID(const int _x, const int _y)
{
	/// The TMX tileset stores tiles startring from 1.
	/// Our vector stores them starting from 0.
	int gid = tile_gids.at(_y).at(_x);

	return gid;
}

////////////////////////////////////////////////////////////
string TileLayer::GetName()
{
	return name;
}


////////////////////////////////////////////////////////////
string TileLayer::GetType()
{
	return "tile";
}


////////////////////////////////////////////////////////////
sf::Vector2i TileLayer::GetDimensions()
{
	return layer_dimensions;
}

}

}

