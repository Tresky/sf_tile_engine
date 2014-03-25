#ifndef SF_EXPORT_MACRO_H
#define SF_EXPORT_MACRO_H

#ifdef SF_TILE_ENGINE_EXPORT
  #define SF_TILE_API __declspec(dllexport)
#else
  #define SF_TILE_API __declspec(dllimport)
#endif

#endif /// SF_EXPORT_MACRO_H