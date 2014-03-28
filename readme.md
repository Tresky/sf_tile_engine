SfTileEngine
==============

This tile engine is very easy-to-use and almost fully customize-able. It takes advantage of SFML for event handling and rendering while supporting the importing of TMX style maps from the [Tiled Map Editor](http://mapeditor.org).

This tile engine is still in early development.

If you wish to compile this engine right now, you need to download SFML 2.0 (if you don't have it already) and extract it somewhere. Then when you open the solution for SfTileEngine, you need to change the properties to tell Visual Studio where SFML 2.0 is. Instructions for doing so can be found on [SFML's website](http://sfml-dev.org).

The current compilation demonstrates a single feature of the Smart Camera feature. If you wish to play around with the engine and test other things you can easily figure it out by reading the provided comments in the example code below and also throughout the engine. I will not waste my time creating tutorials right now as everything is subject to change. :)

Current Features
==============
* Loading and rendering of tile map
* Simple syntax to implement the engine
* SFML for 2D graphics and event handling
* Abstract camera class for extensibility
* Preloaded "smart camera" class with many features (in progress)
  * Tracking modes (4/6 completed)
* Basic TMX map support (orthogonal maps only)
* TinyXML to load XML data

Possible Features
==============
* Toggle-able layers
* Animated tiles
* Event triggers
* Map partitioning for separate properties
* Toggle-able and customize-able mini-map
* Cinematic camera controls
* Elevated tiles

Dependencies
==============
* SFML 2.0 (not included in source)
* TinyXML (included in source)

Example Code
============
Example code can be viewed/downloaded from here: http://bit.ly/1gowJbL

Please let me know what you think and how I can improve my engine.
