Project-Magrathea-V2
====================
V2.0.5

----------

The second generation realistic terrain project.
The first version ended up dying as a result of too many changes of mind.  This will hopefully be better.
The project has a [webpage][1], which has some nice screenshots.

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
 * Shadows

Wishlist
--------
This is alist of high level things that I want to impliment at some stage.  Low level stuff to do is found in `TODO.md`.

 * [x] Trees
 * [.] Birds
 * [x] Colors
 * [x] Textures
 * [.] Sun and sky
 * [.] Sensical terrain types

Control
-------
Use the mouse to point and go.  Keys `S` and `W` to move forward and backward.  Left click to enter/exit pointing mode.  Middle click (or `o` key) to enter/exit first person mode.  If you don't have a mouse, use keys `A`, `D`, `Q` and `E` to move around.

Assets and Data
---------------
The assets and data are too large to hold in this repo.  They can be found [here][2] (link may be outdated.  [email][4] me if it is...) .  Unpack the zip file into a folder called `assets` one directory below where you run the executable.  It is worth noting that in the same directory as `assets`, the folder `src/shaders` should be copied.

The textures are [TGA][1] files.  Feel free to chop and change these to improve them.  If you develop a better texture, please let me know.

Heightmap Data
--------------
Data is 3m resolution of a 9 square kilometers of a section of North America.  More data can be obtained from [here][3].

Code Technicalities
-------------------
Whenever I see new code, I hate having to reinvent the wheel to work out how the thing works.  I hope that this code is sufficently readable to make understanding it easy (even to those not familiar with OpenGL coding).  To this end, I have written `TECHNICAL.md` which givs an overview of how the code works and what calls what etc. as well as `DEVELOPMENT.md` which documents my coding style.

There are also some tutorials up on the project webpage (these are currently growing).

[2]: http://www.ked.co.za/temp/assets.zip "Sample formatted data obtainable here"
[3]: http://viewer.nationalmap.gov/viewer/ "More raw data obtainable here"
[4]: mailto:robert.spencer94@gmail.com
[1]: http://www.paulbourke.net/dataformats/tga/