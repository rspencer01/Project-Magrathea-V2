---
layout: post
title: Some History
---

So I am currently at a very slow part of the project.  I am pumping out code, don't get me wrong, but it is the kind of code that makes the whole system perform better and be more scalable, without actually changing the look and feel of the end product.

And thus today's post is about how I got to where I am (in the project, not real life.  In actual life, I walked).  As mentioned in my [first post][1], this project was inspired by a similar one, [Project Frontier][2], but with the aim to be even more (!) realistic.

The first generation pretty much followed exactly what Shamus Young did (borrowing a bit from his terrain project as well).  But pretty soon I ran into two large problems.

The first was performance.  I was rendering massive (4Mb) textures fairly often and even displaying these each frame became too slow.  I swapped back and forth between two methods of creating these textures and eventually ran the code into the ground with all the changes.

The second was that it looked ugly.  I was producing nowhere near what Young was achieving.  I also had no sense of vertical perspective, so the terrain looked either very hilly or very flat.

Finding the Goldilocks Zone seemed to be very hard and so the project lapsed.  Then, a few weeks ago I got the urge to start again.  And so I wrenched the paging system and camera out of the old system and rewrote everything.

You can sort of follow my thought process in the [tutorials][3].

This has been a learning experience for me.  I have learned a lot about graphics programming, as well as large program layouts.  One of the turning points (and possibly the reason I rebooted the project) was during a trip to Bulgaria, when our bus passed through some truly stunning valleys, passing some breathtaking scenery.  However I knew that if I had seen something like that in Project Magrathea V1, I would have thrown it out as too unrealistic.

Nature is more beautiful than we think.

[1]: http://rspencer01.github.io/Project-Magrathea-V2/2013/09/08/Initial-Post/
[2]: http://www.shamusyoung.com/twentysidetale/?p=11974
[3]: http://rspencer01.github.io/Project-Magrathea-V2/2013/09/09/Tutorial-1/
