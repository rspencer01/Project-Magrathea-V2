---
layout: layout
title: Project Magrathea V2
---

<h3><a name="welcome-to-github-pages" class="anchor" href="#welcome-to-github-pages"><span class="octicon octicon-link"></span></a>Welcome to Project Magrathea (the second)</h3>

Project Magrathea (v1) was started in May 2013 as an attempt to get to know OpenGL and, in part, to replicate the results of <a href="http://www.shamusyoung.com/twentysidedtale/?p=11874"> Project Frontier </a>.  However, where the author of that project stated in post 4 that he was "... not aiming for realism. [He is] looking for whimsical, retro, and fantastic.", Project Magrathea was to be as realistic as possible.  Things went fairly well (considering the author had never touched graphics programming before) but then disaster struck when terrain rendering was too slow and unrealistic and the project lost momentum.

Nothing much happened then for a while, until the project got a complete reboot, from the beginning, giving you v2.  V2 is better, faster, has vegetation shadows and (soon) birds.  The whole project is an exercise in combining many algorithms in one simulation.  There will be plant growing algorithms, animal behaviour patterns and weather patterning.

At the moment, it has a long way to go, but it is getting there steadily.  We will hopefully have some screenshots up here soon.

If you would like to browse, checkout or even edit the code, simply run

    {% highlight bash %}
    $ git clone https://github.com/rspencer01/Project-Magrathea-V2{% endhighlight %}

There is a lot more documentation in the repo, but that also, will start to move to this site. </p>

<h3> Blog posts</h3>
This is a list of blog posts.  There are also some tutorials scattered in between them
<ul>
  {% for post in site.posts %}
  <li>
    <span>{{ post.date | date: "%B %e, %Y" }}</span> <a href="http://rspencer01.github.io/Project-Magrathea-V2{{ post.url }}">{{ post.title }}</a>
	  <div class="post-excerpt">
		{{post.excerpt }}...
    </div>
  </li>
  {% endfor %}
</ul>
