# SDL3Canvas

A simple way to get a window open in any platform and draw anything using [SDL3](https://www.libsdl.org/) and [Dear ImGui](https://www.dearimgui.com/).

## Getting Started

Clone this repository recursively using `git clone --recursive` and compile using CMake. 

### Prerequisites

- [Cmake](https://cmake.org/) (at least version 3.5.0)
- Your favorite C++ compiler

### How it works?
This project is divided in two parts: 

#### SDL3canvas
In this directory is where you can draw. If you just want to get something going on in the screen fast, this is the only part you should modify. There's three main functions:
  - `drawCanvas(SDL_Renderer *renderer)` : Inside this function you can draw anything using the functions provided by SDL.
  - `pollEvent(SDL_Event event, ImGuiIO io)` : With this function you can read all the input catched by SDL and ImGui.
  - `drawGui(SDL_Renderer *renderer, ImGuiIO io)` : You can specify all the ImGui related specifications with this function.
  
If you need to add files to the SDL3canvas project, make sure to include them in the CMake as well.

#### SDL3engine
Contains all the configuration necessary to get a basic SDL3 and Dear ImGui window with basic configuration up and running. You may want to change this part of the project if you need to configure things related with the initialization and configuration of these libraries.


<!-- ### Installing

A step by step series of examples that tell you how to get a development
environment running

Say what the step will be

    Give the example

And repeat

    until finished

End with an example of getting some data out of the system or using it
for a little demo -->

<!-- ## Running the tests

Explain how to run the automated tests for this system

### Sample Tests

Explain what these tests test and why

    Give an example

### Style test

Checks if the best practices and the right coding style has been used.

    Give an example

## Deployment

Add additional notes to deploy this on a live system

## Built With

  - [Contributor Covenant](https://www.contributor-covenant.org/) - Used
    for the Code of Conduct
  - [Creative Commons](https://creativecommons.org/) - Used to choose
    the license -->

<!-- ## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code
of conduct, and the process for submitting pull requests to us. -->

<!-- ## Versioning

We use [Semantic Versioning](http://semver.org/) for versioning. For the versions
available, see the [tags on this
repository](https://github.com/PurpleBooth/a-good-readme-template/tags).

## Authors

  - **Billie Thompson** - *Provided README Template* -
    [PurpleBooth](https://github.com/PurpleBooth)

See also the list of
[contributors](https://github.com/PurpleBooth/a-good-readme-template/contributors)
who participated in this project. -->

<!-- ## License

This project is licensed under the [CC0 1.0 Universal](LICENSE.md)
Creative Commons License - see the [LICENSE.md](LICENSE.md) file for
details

## Acknowledgments

  - Hat tip to anyone whose code is used
  - Inspiration
  - etc -->
