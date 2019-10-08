# RobotMazeSolver

RobotMazeSolver is a PathFinding Algorithm, the little vacuum cleaner has to find the exit of a flat without
knowing the site layout.

## Installation
Follow steps :
```
$ cd (place where you want to install)
$ git clone https://github.com/aureliensimon/RobotMazeSolver.git
$ cd RobotMazeSolver | make
```

This will result with a exe call **path**

## Usage
```
$ ./path [map name] [mode]
```

*[map name]* : Name of the map you want to use (find it in /maps or create your own)

*[mode]* : 
   - **t** : Textual interface, the program will run in the console
   - **g** : Graphical interface, the program will open a window

## Create your map
If you want to create your own map, open a notepad, a map ***must contain*** :

The first line of the map have to be [height]:[width]

| Name | Character |
| --- | --- |
| Wall | x |
| Start Point | D |
| Target Point / Exit | S |

When done, add your map to the */maps* folder

### Exemples
Here is one basic map file
```
10:5
xxxxx
x D x
x   x
x  xx
x   x
xx  x
x   x
x  xx
x   x
xxSxx
```
