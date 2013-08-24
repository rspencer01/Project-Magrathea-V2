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
 * Introduce basic vegetation (this may need to be a second project, at first)
 * See from there.

Process:
--------
 * Write as many and as much of the header files as possible
 * Check that all needed functions are there
 * Write the actual code

Progress:
---------
The following milestones have been passed:
 * Simple paging
 * Simple system of region based rendering
 * Dynamic region creation based on camera position
 * Use of real data (imported)

Data
----
Since the input data is large (3Mb), it is not included in this repo, but can be downloaded from [here][http://www.ked.co.za/temp/smalldata.dat].

Data is 3m resolution of a 9 square kilometers of a section of North America.  More data can be obtained from [here] [http://viewer.nationalmap.gov/viewer/].