Technical
=========

This is an overview of how the entire system works.

Entry
-----
Program entry is into the `main` function of ... `main.cpp`. No surprises there.  This function constructs a `Game` object and calls its `run` function.  In a future version this function will check the command line arguments and possibly start a command line interface, with ascii mapping.

The `Game` Class
----------------
This is the class that handles most of the program.  Upon construction, a variety of things are initialised.  Upon running, control is surrendered to GLUT, the OpenGL window managment system Magrathea uses.

`Book`, `Page` and the Paging System
------------------------------------
Project Magrathea will idealy grow to be big.  Not big as in "This movie is big", but big in the same way space is big.  (Bigger than the trip to your local shop).  As such it is procedurally generated, and at no time is the entire world held in memory.

At present, the main component of the world (heightmap data) is still read in from a file.  This *will* change.

To store the massive amount of information,  we note that at any point, we will only really be interested in data relevant to the player's position.  In the greater scheme of things, we don't care what happens 10km from us.  And so we develop a paging system.

The `Page` class holds a 2D array of `terrainBits`.  It is responsible for their memory, and populating them at the beginning.  Pages will eventually be about 100m in size.  They will also have a timeout system (not yet implimented) that earmarks them for deletion after a certain time has passed without an access.

`Page`s are held in `Book`s. Books decide which page to ask for a certain piece of data.  They will also handle the freeing of pages, if the page states that it is ready to be deleted.

DynoTrees and Their Generation
------------------------------
`DynoTree` is the class that handles the generation of cool looking trees.