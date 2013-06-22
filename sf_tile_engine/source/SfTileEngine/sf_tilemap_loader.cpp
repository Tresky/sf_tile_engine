#include "..\..\include\SfTileEngine\sf_tilemap_loader.h"

#include "..\..\extlibs\TinyXML\tinyxml2.h"
  using namespace tinyxml2;

#include "..\..\include\SfTileEngine\sf_tilemap.h"
#include "..\..\include\SfTileEngine\sf_tileset.h"
#include "..\..\include\SfTileEngine\sf_layer.h"
#include "..\..\include\SfTileEngine\sf_tile.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{


bool CheckPointer(const void* _ptr, string _error)
{
  if (!_ptr)
  {
    cout << _error << endl;
    return false;
  }
  return true;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::LoadTilemap(const string _path, SfTilemap& _tilemap)
{
  // Temporary map object
  SfTilemap temp_map;

  // Load TMX file in TinyXML
  XMLDocument doc;
  doc.LoadFile(_path.c_str());

  // Check for error in parsing
  if (doc.Error())
  {
    cout << "XML Parsing Error: " << doc.ErrorID() << endl;
    return false;
  }

  // Find the map element
  const XMLElement* map_element = doc.FirstChildElement("map");
  if (!CheckPointer(map_element, "Couldn't locate map element in map file"))
    return false;

  // Load all of the basic map data
  map_element->QueryFloatAttribute("version", &temp_map.version);
  map_element->QueryIntAttribute("width", &temp_map.map_dimensions.x);
  map_element->QueryIntAttribute("height", &temp_map.map_dimensions.y);
  map_element->QueryIntAttribute("tilewidth", &temp_map.tile_dimensions.x);
  map_element->QueryIntAttribute("tileheight", &temp_map.tile_dimensions.y);

  // Load the orientation of the tile map. Only orthogonal
  // is supported currently.
  string orient_str = map_element->Attribute("orientation");
  if (orient_str == "orthogonal")
    temp_map.orientation = SFTILE_ORIENT_ORTHOGONAL;
  else
  {
    cout << "SfTileEngine currently only supports orthogonal tile maps." << endl;
    temp_map.orientation = SFTILE_ORIENT_UNSUPPORTED;
    return false;
  }

  // Parse the tilesets in the tile map.
  const XMLElement* tileset_element = map_element->FirstChildElement("tileset");
  while (tileset_element)
  {
    if (!ParseTileset(tileset_element, *temp_map.tileset))
    {
      cout << "Failed to parse tileset" << endl;
      return false;
    }
    tileset_element = tileset_element->NextSiblingElement("tileset");
  }
  // Don't let your pointer dangle... That's gross.
  tileset_element = nullptr;

  // Parse the tile layers
  const XMLElement* layer_element = map_element->FirstChildElement("layer");
  while (layer_element)
  {
    SfLayer temp_layer;
    if (!ParseLayer(layer_element, temp_layer))
    {
      cout << "Failed to parse tile layer" << endl;
      return false;
    }
    else
    {
      temp_layer.tileset = temp_map.tileset;
      temp_map.layers.push_back(unique_ptr<SfLayer>(new SfLayer(temp_layer)));
    }
    layer_element = layer_element->NextSiblingElement("layer");
  }
  layer_element = nullptr;

  _tilemap = temp_map;

  return true;
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseTileset(const XMLElement* _element, SfTileset& _tileset)
{
  // First GID of the currently parsing tileset
  int first_gid = 0; _element->QueryIntAttribute("firstgid", &first_gid);
  _element->QueryIntAttribute("tilewidth", &_tileset.tile_dimensions.x);
  _element->QueryIntAttribute("tileheight", &_tileset.tile_dimensions.y);
  // Space around the tileset image
  int margin = 0; _element->QueryIntAttribute("margin", &margin);
  // Space in between each tile in the tileset
  int spacing = 0; _element->QueryIntAttribute("spacing", &spacing);

  // Load the image of the tileset and store
  // it in the SfTileset.
  const XMLElement* image_element = _element->FirstChildElement("image");
  if (!CheckPointer(image_element, "Couldn't locate image element in map file"))
    return false;

  // Load the tileset image
  string source = image_element->Attribute("source");
  if (!_tileset.tileset_image.loadFromFile(source))
  {
    cout << "Failed to load tileset image" << endl;
    return false;
  }

  int width = 0; image_element->QueryIntAttribute("width", &width);
  int height = 0; image_element->QueryIntAttribute("height", &height);
  image_element = nullptr;

  // Load all of the tiles into the tileset
  int gid = first_gid;
  for (int y = margin; y < height; y += spacing + _tileset.tile_dimensions.y)
    for (int x = margin; x < width; x += spacing + _tileset.tile_dimensions.x)
    {
      // We only save the rectangle around the tile
      // to help shorten loading times.
      // We can then load the texture every frame when we want
      // to display the tile.
      sf::IntRect rect(x, y, _tileset.tile_dimensions.x, _tileset.tile_dimensions.y);

      SfTile temp_tile(gid, rect);
      _tileset.tiles.push_back(unique_ptr<SfTile>(new SfTile(temp_tile)));
    }

  // Parse the properties of the tileset
  //const XMLElement* properties_element = _element->FirstChildElement("properties");
 /* if (properties_element)
    _tileset.properties->Parse(properties_element);*/

  // Cleanup... cleanup...
  //properties_element = nullptr;
  return true;
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseLayer(const XMLElement* _element, SfLayer& _layer)
{
  // Load the arbitrary name of the layer
  string name = _element->Attribute("name");
  
  cout << "Loading Layer: " << name << endl;

  // Load the dimensions of the layer
  sf::Vector2i layer_dimensions(0, 0);
  _element->QueryIntAttribute("width", &layer_dimensions.x);
  _element->QueryIntAttribute("height", &layer_dimensions.y);

  _layer.layer_dimensions = layer_dimensions;

  // Load the data node
  const XMLElement* data = _element->FirstChildElement("data");

  // Find out the encoding of the data
  string encoding_attr = (data->Attribute("encoding") != NULL) ? data->Attribute("encoding") : "xml";

  // Go-go-gadget, Parsers!
  if (encoding_attr == "xml" && !ParseXmlLayer(data, _layer))
    return false;
  else if (encoding_attr == "base64" && !ParseBase64Layer(data, _layer))
    return false;
  else if (encoding_attr == "csv" && !ParseCsvLayer(data, _layer))
    return false;
  else
    return true;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseXmlLayer(const XMLElement* _element, SfLayer& _layer)
{
  const XMLElement* tile = _element->FirstChildElement("tile");

  for (int y = 0; y < _layer.layer_dimensions.y; ++y)
  {
    vector<int> temp;
    for (int x = 0; x < _layer.layer_dimensions.x; ++x)
    {
      int gid = tile->IntAttribute("gid");

      temp.push_back(gid);

      tile = tile->NextSiblingElement("tile");
    }
    _layer.tile_gids.push_back(temp);
  }
  // Voila! It's a boy!
  return true;
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseBase64Layer(const XMLElement* _element, SfLayer& _layer)
{
  cout << "Cannot parse Base64 data" << endl;
  return false;
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseCsvLayer(const XMLElement* _element, SfLayer& _layer)
{
  cout << "Cannot parse CSV data" << endl;
  return false;
}

}

}