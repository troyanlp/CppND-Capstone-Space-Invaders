# CPPND: Capstone Project: Space Invaders

This project is done as the final project of the Udacity C++ Nanodegree utilizing different concepts of programming learned during the course.  The game chosed is Space Invaders.

The game consists on a number of aliens coming down to earth and shooting and only the player can defeat them by avoiding their bullets and shooting to kill. What will be your score? ;)

<img src="SpaceInvaders.jpeg"/>

Instructions 
- Moving --> Left and right arrow
- Shooting --> Space
- Exiting the game --> Esc


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SpaceInvaders`.


## Code structure
The core of this game is a loop that receives input (through the Controller class), updates all the elements of the game (Player, Aliens and Bullets), checks collisions and game logic and finally renders at a frame rate of 40fps.

Since all the elements of the game have some commonalities, there's and Entity class from which all of them inherit to take advantage of the Object Oriented programming benefits.

## Rubric points addressed with this project
* The project demonstrates an understanding of C++ functions and control structures.
	- Using while loop, if - else statements, ..
	
* The project accepts user input and processes the input.
	- Class Controller accepts left and right key, space and handles player accordingly.
	
* The project uses Object Oriented Programming techniques.
	- The main elements of the game inherit from a core class and implement a virtual function
	
* Classes use appropriate access specifiers for class members.
	- All class data members are explicity specified as public, protected or private.
	
* Class constructors utilize member initialization lists.
	- All clases take advantage of member initialization lists
	
* Classes abstract implementation details from their interfaces.
	-  Functions have self-explanatory names
	
* Classes follow an appropriate inheritance hierarchy.

	
* Derived class functions override virtual base class functions.
	- Entity has pure virtual function "void Update()" that is implemented in Alien and Player class.
	
* The project makes use of references in function declarations.
	- Data is passed by reference whenever possible

* The project uses move semantics to move data, instead of copying it, where possible.
	- unique_ptr returned when creating a bullet uses move semantics.
	
* The project uses smart pointers instead of raw pointers.
	- All pointers are smart accross the project. The bullets are stored in unique_ptr.