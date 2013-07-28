#ifndef SF_ENTITY_H
#define SF_ENTITY_H

#include <iostream>
  using std::cout;
  using std::endl;

#include <SFML\Graphics.hpp>

#include "sf_dll_macro.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{
  class SfTilemapLoader;
}

class SF_TILE_API SfEntity
{
friend class priv::SfTilemapLoader;
public:
  ////////////////////////////////////////////////////////////
  /// \brief Default constructor
  ///
  /// Constructs an empty entity.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfEntity();


  ////////////////////////////////////////////////////////////
  /// \brief Copy constructor
  ///
  /// Copies an existing tile map.
  ///
  ////////////////////////////////////////////////////////////
  explicit SfEntity(const SfEntity& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Assignment operator
  ///
  /// Copies an existing tile map.
  ///
  ////////////////////////////////////////////////////////////
  SfEntity& operator=(const SfEntity& _copy);


  ////////////////////////////////////////////////////////////
  /// \brief Renders the entity.
  ///
  /// \param _window SFML window to render to
  ///
  ////////////////////////////////////////////////////////////
  void Render(sf::RenderWindow& _window);

private:
};

}

#endif