# CS1230 Final Project: Blueno@Chernobyl

<img src="./readme_stuff/team_banner.jpg" height=300 />

Let's geddit!

## README

[shader tab]

The L-System tab generates a tree according to the settings on the UI. The user can choose between 6 different L-Systems. Some of these options are 2D (these might show up sideways at first), and others are 3D. The user has the option to change the recursive depth, which determines the number of replacements in the L-system strings. Since the L-System trees generate the same thing each time, to add more variation, the user has the option to add length stochasticity and angle stochasticity. In length stochasticity, the length of each branch is shortened or lengthened by a random amount, and the angle is similarly randomly modified. The user also has the option to add leaves, which puts leaves at the end of each branch pointing downward and then in a random x/z direction to look more natural. As the user updates the settings, the tree will update and regenerate accordingly.

The gallery tab randomly generates 5 trees with randomly selected L-Systems and recursive depths, and displays them in pots patterned with the current shaders on the shader evolution tab. 

#### [24/11/20 Update]

So we've uploaded a project plan in the readme_stuff folder. It's pretty detailed, though I'm sure we'll deviate from it when we start making this thing.



#### [29/11/20 Update]

So in the process of adding in some of the main courses's support code to this project (so we don't have to reinvent the wheel a thousand times), I ended up having to comment out  the dummy.cpp file in the glm/details. No idea what that does; hopefully that won't bite us in the butt later on. This is Anderson talking, by the way.



#### [06/12/20 Update]

Another update from Anderson! So the [paper](https://www.karlsims.com/papers/siggraph91.html) that the this project was inspired by mentions that they make use of iterated function systems (more about those [here](http://facstaff.susqu.edu/brakke/ifs/default.htm) and [here](http://soft.vub.ac.be/~tvcutsem/teaching/wpo/grafsys/ex4/les4.html). I would love to integrate them into this project, but making a proper IFS system would include the use of FBOs, and since some shader genotypes would use IFSs and some wouldn't (it's completely probabilistic, after all), that means there'd need to be conditional (and possibly nested) use of FBOs. Noooooo thank you.

So I'm gunning for a method for adding fractal like things using a methodology inspired by [this](https://www.mi.sanu.ac.rs/vismath/javier1/index.html) and [this](http://nuclear.mutantstargoat.com/articles/sdr_fract/).
