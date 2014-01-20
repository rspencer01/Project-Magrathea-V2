Technical
=========

This is an overview of how the entire system works.

Entry
-----
Program entry is into the `main` function of ... `main.cpp`. No surprises there.  This function constructs a `Game` object and calls its `run` function.  In a future version this function will check the command line arguments and possibly start a command line interface, with ascii mapping.

The `Game` Class
----------------
This is the class that handles most of the program.  Upon construction, a variety of things are initialised.  Upon running, control is surrendered to GLUT, the OpenGL window managment system Magrathea uses.

Worth noting is the curious variable, `currentGame`.  This is because GLUT is not happy with taking a function of a class as a callback function, so this variable and the wrapper classes are required.

`Book`, `Page` and the Paging System
------------------------------------
Project Magrathea will idealy grow to be big.  Not big as in "This file is big", but big in the same way space is big.  (Bigger than the trip to your local shop).  As such it is procedurally generated, and at no time is the entire world held in memory.

At present, the main component of the world (heightmap data) is still read in from a file.  This *will* change.

To store the massive amount of information,  we note that at any point, we will only really be interested in data relevant to the player's position.  In the greater scheme of things, we don't care what happens 10km from us.  And so we develop a paging system.

The `Page` class holds a 2D array of `terrainBits`.  It is responsible for their memory, and populating them at the beginning.  Pages will eventually be about 100m in size.  They will also have a timeout system (not yet implimented) that earmarks them for deletion after a certain time has passed without an access.

`Page`s are held in `Book`s. Books decide which page to ask for a certain piece of data.  They will also handle the freeing of pages, if the page states that it is ready to be deleted.

DynoTrees and Their Generation
------------------------------
`DynoTree` is the class that handles the generation of cool looking trees.  These trees are (currently) binary, ie each branch divides into two.

Each branch consists of 20 points: 2 rings of 10, joined by 20 triangles.

Once the branch divides in two, one of the branches "continues" the old branch by using the points that the old branch ended on as its starting ring.  The other starts anew.

Once the branches are small enough, 6 "plates" are placed randomly just off the branch.  These large squares hold a transparant texture with leaves that gives a most pleasing effect.

Once the branches are even smaller, the recursion stops.

Graphics and `Object`s
----------------------
Project Magrathea stores all the visible things as `Object`s.  This class has the functions `addPoint`, `addTriangle` which, when used with the initialiser `clearTriangleData` and the `pushTriangleData` function construct 3d objects and push the data to the GPU for it to handle.  A copy of the data is kept in CPU memory, for easy mutation, for when animation is introduced.

Another funciton, not fully tested, but seeming to work, is the `loadFromOBJFile` function.  This loads `obj` files.

The `ObjectManager`
--------------------
This class stores all the objects on the screen, renders them and also has a fairly(ish) efficient order of creation of the objects.  If you want a new object, you call its `addObject` method, and it will, at some point in the future be added to the scene.

Shadows
-------
Oooh.  Shadows.  Both a headache and very neat.  The rendering of shadows required a complete rewrite of the rendering process of Magrathea.  For starters, shaders (4 of them) had to be written.  Then data had to be passed with Vertex attribute arrays and `glVertexAttribPointerARB`.  Much of their development was done in the dark (literally!) with little to no feedback on what was working and what was not.  The reason I say this, is as a warning to changing stuff.  It works.  I offer no guarantee that tinkering with it will not break it.

Having said that, the entire shadow production is quite cool (in my opinion).  Firstly we requre a new `Camera` (most of what follows is folded into the `ShadowManager` class).  Then we require a completely different projection matrix (this is to avoid z-fighting).   We use an orthographic matrix.  Before rendering (or in this case, at the first frame) we render the entire scene from the point of view of the sun *to a texture*.  In that texture we store, not a colour, but only the depth.

Then we pass the texture, during every subsequent render pass to the fragment shader (in sampler number 7).  The vertex shader for each point determines its position, not only from the POV of the player, but also from the sun.  It passes this to the fragment shader which compares whether or not the fragment is further from the sun than the value in the depth buffer

    if (texture(shadowTexture,ShadowCoord.xy).z < ShadowCoord.z-0.002)
      ...

The `0.002` is a small offset to prevent items from throwing a shadow on themselves (acne, I think it is called).  If it fails this check, it is darkened.

The shadows are updated every few seconds to follow the player and to turn with the sun.

Birds
-----
Birds are a pair of triangles with a texture.  They are kinematic (use velocity/acceleration etc) and fly fairly well.  The flapping pattern is not sinusoidal, but rather the sum of sin functions, giving a rounded triangular shape.  Soon they will flock.  Mwaaahahahah!

Terrain
-------
One of the headaches with creating terrain is constructing a realistic transition from one type (say grass) to another (say rock).  One of the effective methods for this is to just fade from one texture on the ground to another.

The origional plan was for each `Region` to have a texture that it creates and lays over itself.  However, this is costly on creation and requires storing lots of big images.  A better plan is to pass the task to the fragment shader!  This shader samples a number of textures and outputs the correct pixel colour based on that.

Any weirdnesss with a half grass half rock portion of land will hopefully be brushed over with actual grass objects or other things that cover the ground.

In practice, the fragment shader is passed a texture with 4 squares or blocks in it.  It is also passed a `vec4` of weightings to take from each block.  It gets the weighted average pixel and outputs that.

This is orders of magnitude ( `O(1)` vs `O(n^2)` ) better than the previous method.

Complexity
----------
A massive problem when rendering natural scenes is the complexity.  Let us analyse this.

At maximum detail we would want about 21 blades of grass per 20^2cm ~ 500 blades per square meter.  A level of detail like this for 10^2m gives 50 000 blades.  This is reasonable.  If we make each region 5m on a side and render the four nearest at max detail we should be fine.  This would mean a max size of Magrathea of 500^2m with the current region rendering method.
