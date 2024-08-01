# minirt
42's MiniRT

with https://github.com/Javocho !!

# Example renders

# Install

```
git clone --recurse-submodules <url> [directory]
cd [directory]
make
```

You will now have a miniRT executable.

Definitely works on: ubuntu 22.04

Prerequisites: ```build-essentials```

# Features

A simple raytracer. Works with geometrical shapes: plane, sphere, cylinder (finite, must specify height); no model support or anything like that.

Hardcore diffuse light model. No bounces. This means that a completely red room with a completely white sphere and a completely blue light will be completely black, with the sphere being lit in blue.

There are (hard) shadows, but only from point lights.

# Map format

### ```.rt``` files with the following rules:
#### General:

1 or 0 ambient lights:
```
A intensity r,g,b
```

1 camera:
```
C x,y,z normal_x,normal_y,normal_z fov
```

Light(s) (non-obligatory):
```
L x,y,z intensity r,g,b
```
*If there's no RGB set for the L light, it will be white automatically*

#### Objects:

Plane(s):
```
pl x,y,z normal_x,normal_y,normal_z r,g,b
```

Sphere(s):
```
sp x,y,z diameter r,g,b
```

Cylinder(s):
```
cy x,y,z normal_x,normal_y,normal_z diameter height r,g,b
```
*Cylinder's origin point is in its bottom cap*

The recommended values for the coordinates and sizes are within the 0.5 to 10 range. Beyond that, light begin to be almost innoticable. To ammend that, however, you might want to toy around with the ```inc/minirt.h``` file's ```FALLOFF``` define. It should not be set to 1.0 or less, but the closer to 1.0 it is, the more gradual the fall-off of lights is.

The values for the normal vector will be normalized.

The rgb values are integers from 0 to 255.

The intensity is a floating point number with a range from 0.0 to 1.0.

If there's a problem with the configuration, you will be told that upon attempting to launch the program, with varying degrees of narrowness :P

# Known Issues (c)

Using valgrind, you will find a suppressed error. It's probably something from the MLX library, although I'm not quite sure.

Placing the camera inside of a plane (or very close to it) (or perhaps this also works with any other surface) will sometimes produce noise; this is probably due to the floating point inaccuracy creeping in on the "shall we ignore this light" optimization-light-blocker checker. I haven't yet thought of a way to fix this; I've tried checking more things using ```> EPSILON``` in place of ```> 0```, but it didn't really seem to help me this time.

Each object adds a pass to each pixel. Each light adds as many check-if-ignored passes as there are objects in the scene to each pixel. Each non-ignored light adds as many ray passes as there are objects to each pixel as well. The point is: it's quite slow. But on something like a 1000x1000 window with 5 objects and 3 lights it's OK ^^.

#### P.S. You Might Find The Following Command Quite Useful (bash)

```
for i in scenes/*.rt; do echo $i; cat $i; ./miniRT $i; done
```
