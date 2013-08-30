Project-Magrathea-V2
====================

The second generation realistic terrain project.
The first version ended up dying as a result of too many changes of mind.  This will hopefully be better.

Goals:
------
 * Import a heightmap and display it.
 * Do this by caching data near the player (don't load it all at once)
 * Determine the type of terrain at each point algorithmically
 * Display this with textures
 * Introduce basic vegetation and wildlife 
 * See from there.

Progress:
---------
The following milestones have been passed:

 * Simple paging
 * Simple system of region based rendering
 * Dynamic region creation based on camera position
 * Use of real data (imported)
 * Nice trees
 * Nice menu

Wishlist
--------
This is alist of high level things that I want to impliment at some stage.  Low level stuff to do is found in `TODO.md`.

 * ~~Trees~~
 * Birds
 * ~~Colors~~
 * ~~Textures~~
 * Sun and sky
 * Sensical terrain types

Textures
--------
The textures are (currently) 1000 by 1000 BMP files and can be found in `assets`.  Feel free to chop and change these to improve them.  If you develop a better texture, please let me know (or submit a pull request).

Data
----
Since the input data is large (>3Mb), it is not included in this repo, but can be downloaded from [here][1] and [here][3].  It should be placed in the `assets` folder.

Data is 3m resolution of a 9 square kilometers of a section of North America.  More data can be obtained from [here][2].

[1]: http://www.ked.co.za/temp/smalldata.dat "Sample formatted data obtainable here"
[2]: http://viewer.nationalmap.gov/viewer/ "More raw data obtainable here"
[3]: http://www.ked.co.za/temp/full019.dat "Sample tree"
