# CS1230 Final Project: Blueno@Chernobyl

<img src="./readme_stuff/team_banner.jpg" height=300 />

Let's geddit!

## The 3 Parts

#### The Shader Tab

The shader tab is where you can use the laws of evolution to make cool looking shaders. You get to play God with the shaders.

To get started with the shader tab, be sure to press the "Initialize!" button: this only needs to be pressed once. Also press the "Show src" button whenever you want to be able to analyze the source code of shaders that you find interesting. Keep in mind that the source you see there is only the critical part of the source. They do reference to custom methods and whatnot; a quick look at the source code of the project and you'll see the definition of those functions. It also only shows the fragment shader; you'll probably want to see the vertex shader too (it's a super simple vertex shader though).

Regardless, once you've  initialized the scene, there's a number of things you can do. 

1. If you don't like some/all of the shaders that you see, you can replace them with completely new genotypes by selecting those shaders in the selection pane and pressing the "Refresh Population" button (in the "Replace Shaders" tab.)
2. You can also decide to replace the shaders that you don't like with mutations of another shader that you do like. Select the shaders you want to replace in the selection pane, then select the id of the "donor" shader, and hit the "replace with mutations" button.
3. You can also mutate all the currently selected shaders in place by going to the "Mutate current shaders" tab and pressing the "Mutate" button.
4. You can also decide to replace shaders with the offspring of other shaders! This is my favorite feature, actually. Go to the "create offspring" tab, select the ids of the parents, select the shaders you want to replace in the selection pane, and hit the "crease offspring" button!

##### A little note on generations

So shaders normally start out at generation [0] and increment their generation with every mutation. If any part of their source code is edited when they go to generation [n], then that part of the code will have the [n] tab by it.

Offspring, though, start out at generation 1. This is because they get all their initial genes from one parent at generation 0, then go though a custom mutation (which increases their generation) which mutates it with genes from the second parent.



#### The L-System Tab

The L-System tab generates a tree according to the settings on the UI. The user can choose between 6 different L-Systems. Some of these options are 2D (these might show up sideways at first), and others are 3D. The user has the option to change the recursive depth, which determines the number of replacements in the L-system strings. Since the L-System trees generate the same thing each time, to add more variation, the user has the option to add length stochasticity and angle stochasticity. In length stochasticity, the length of each branch is shortened or lengthened by a random amount, and the angle is similarly randomly modified. The user also has the option to add leaves, which puts leaves at the end of each branch pointing downward and then in a random x/z direction to look more natural. As the user updates the settings, the tree will update and regenerate accordingly.

#### The Gallery

The gallery tab randomly generates 5 trees with randomly selected L-Systems and recursive depths, and displays them in pots patterned with the current shaders on the shader evolution tab. 



## A little Devlog

#### [24/11/20 Update]

So we've uploaded a project plan in the readme_stuff folder. It's pretty detailed, though I'm sure we'll deviate from it when we start making this thing.



#### [29/11/20 Update]

So in the process of adding in some of the main courses's support code to this project (so we don't have to reinvent the wheel a thousand times), I ended up having to comment out  the dummy.cpp file in the glm/details. No idea what that does; hopefully that won't bite us in the butt later on. This is Anderson talking, by the way.



#### [06/12/20 Update]

Another update from Anderson! So the [paper](https://www.karlsims.com/papers/siggraph91.html) that the this project was inspired by mentions that they make use of iterated function systems (more about those [here](http://facstaff.susqu.edu/brakke/ifs/default.htm) and [here](http://soft.vub.ac.be/~tvcutsem/teaching/wpo/grafsys/ex4/les4.html). I would love to integrate them into this project, but making a proper IFS system would include the use of FBOs, and since some shader genotypes would use IFSs and some wouldn't (it's completely probabilistic, after all), that means there'd need to be conditional (and possibly nested) use of FBOs. Noooooo thank you.

So I'm gunning for a method for adding fractal like things using a methodology inspired by [this](https://www.mi.sanu.ac.rs/vismath/javier1/index.html) and [this](http://nuclear.mutantstargoat.com/articles/sdr_fract/).
