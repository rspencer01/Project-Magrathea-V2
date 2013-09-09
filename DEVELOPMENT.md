Development
===========

This details thing developers should know if they wish to contribute, such as the coding style and git layout.  Not all existing code follows these, but all *should* and will move towards there.  Any new code should.

Coding Style
------------
The following should be adhered to at all times

###Indentations
Indentations are given by 2 spaces.  There should be indentations after

* Any open curly brace (`{`)
* Any single line flow satement (`if` or `for` or `while`)

###Braces
Braces are a bit of a flame war topic.  Project Magrathea uses "Allman" or "ANSII" style.  Braces should be placed on the next line after a control statement, indented to the same level as the control statement.  Braces are not required if there is only a single instruction after a control statement.

###Variable/Function names
Variable and function names should be as explicit as possible.  Self documenting code is ideal.  Names such as `numberOfTriangles` and `editTextureCoord` are good.  However, abbreviations are discouraged, so the last should be `editTextureCoordinate`.

Variable and function names should start with a lower case letter.  Where multiple words are desired, subsequent words should be capitalised.

###Class names
Class names should be nouns, and their first letters should be capitalised.

###Examples

    if (someBoolean)
      doSomething();

	for (int y = 0; y<5;y++)
	{
      someFunction(y);
      ...
    }

    void Sky::Render(int refreshTime)
    {
      Object::Render(refreshTime);
    }

Commenting
----------
Project Magrathea uses `Doxygen` as a documentation generation system.  `Doxygen` uses very particular comments as its input.  These can either be in Javadoc format (`/**`) or the alternative tripple slash, `///`.  The latter is used.

Functions should be commented twice.  Once in the header file, with a short description and once in the cpp file with a longer description and parameter/return list

For example

**Object.h**

    /// Initialise the triangle and position datas
    void clearTriangleData(int,int);

**Object.cpp**

    /// Reset the data.  Clear the internal arrays, and the GPU arrays.
    /// Reserve space for p point and t triangles
    /// @param p Number of points
    /// @param t Number of triangles
    void Object::clearTriangleData(int p, int t)
    {
      // Clear all the data and the buffers (if required)
      if (triangleDataVBO!=NULL)
        delete triangleDataVBO;
      ...
    }

Comments not intended for documentation (typically inside functions) should simply be `//` indented to the same level as the code.

File comments are recommended, but are not really useful.  Also, they are pig ugly.  They may or may not stay.  An example is below

    /// @file graphics.h
    /// @author  Robert Spencer <robert.spencer94@gmail.com>
    /// @section DESCRIPTION
    ///
    /// This file contains a number of useful functions to do with graphics.

Comments on how to make the code prettyer are welcome.

Git
---

Fairly soon (within one or two commits, hopefully), we will move to the git system described [here][1]

In summary, the only things alowed on `master` are those that are major milestones *that work*.  Every master commit will be given a version number.  On the other hand `develop` will be the branch to which working progress is put.  Every new feature should be developed in its own branch, and merged with `develop` once complete.  The only branches held on Github will be `master` and `develop`.

For more detail, please consult the link.  

Finally, please use the `git merge --no-ff`.  This will make the development flow plot much nicer.

[1]: http://nvie.com/posts/a-successful-git-branching-model/ "A successful git branching model"