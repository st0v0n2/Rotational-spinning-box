# Rotational Spinning Cube Using ASCII Art and Rotational Matrices

This C++ project renders a 3D cube that spins using rotational matrices. The cube is projected onto a 2D ASCII art display, creating a visual representation of the spinning cube in the console. The code utilizes trigonometric functions to apply 3D rotations and a Z-buffer to manage depth perception, ensuring the correct parts of the cube are visible during the rotation.

## Explanation of the Code

### 1. Including Libraries

```cpp
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>
```

---

**math.h**: Provides mathematical functions (e.g., sin, cos).
**stdio.h**: Provides functions for input/output like printf.
**unistd.h**: Used for the usleep function to control the frame rate.
**cstring**: For memory functions like memset to clear buffers.
**iostream**: Used for input/output operations.
**chrono & thread**: Used for handling timing operations (not used in the current version of the code).

---

### 2. Global Variables

```cpp
float A, B, C;
float cubeWidth = 44;
int width = 120, height = 40;
int comwh = width * height;
float Zaxisbuffer[120 * 40];
char buffer[120 * 40];
int backgroundascoi = ' ';
int idx;
float incrementSpeed = 1.8;
int distanceFromCam = 250;
float x, y, z;
float K1 = 40;
float kkk;
int xp, yp;
```

---

**A, B, C:** Rotation angles around the X, Y, and Z axes.
**cubeWidth**: Defines the size of the cube.
**width, height**: Dimensions of the screen (120 columns, 40 rows).
**Zaxisbuffer**: Stores depth information to handle which parts of the cube are closer to the camera.
**buffer**: Stores the ASCII characters to be rendered on the screen.
**backgroundascoi**: The character used to clear the screen (space ' ').
**incrementSpeed**: Controls how fast the cube is drawn and rotated.
**K1**: A scaling factor for the perspective projection.

---

### 3. Rotation Functions

```cpp
float calculateX(int i, int j, int k) { ... }
float calculateY(int i, int j, int k) { ... }
float calculateZ(int i, int j, int k) { ... }
```

---

calculateX: Computes the new X-coordinate after rotating the cube based on the rotation angles A, B, and C.
calculateY: Computes the new Y-coordinate using trigonometric transformations.
calculateZ: Computes the new Z-coordinate for depth.
These functions take in 3D coordinates and transform them based on the current rotation angles, allowing the cube to spin in 3D space.

---

### 4. Surface Calculation

```cpp
void calculateSurface(float cubeX, float cubeY, float cubeZ, int ch) { ... }
```

---

This function projects the 3D points of the cube onto a 2D plane (the screen):

x, y, z: The 3D coordinates are transformed using the rotation functions calculateX, calculateY, and calculateZ.
kkk = 1 / z: Perspective projection is achieved by inverting the Z value, making objects appear larger as they get closer to the camera.
xp, yp: 2D screen coordinates are calculated based on the 3D transformed points.
Z-buffering: If the calculated point is closer to the camera than what is currently stored in the Z-axis buffer, it gets drawn on the screen.

---

### 5. Main Loop

```cpp
int main() { ... }
```

---

The main function handles the drawing of the cube and its animation:

Clear Buffers: Each frame, the buffers are cleared using memset to reset the screen and Z-buffer.
Loop Over Cube Points: For each face of the cube, points are calculated and projected onto the 2D plane using calculateSurface.
Render the Cube: The buffer is printed to the console with putchar, displaying the spinning cube.
Rotation: The rotation angles A and B are updated slightly on each frame, giving the spinning effect.

---

### 6. Alternative Surface Function (calculateSurface2)

```cpp
void calculateSurface2(float cubeX, float cubeY, float cubeZ, int ch) { ... }
```

---

## This alternative version of the surface calculation function can be used to display different characters for various faces of the cube, allowing for customization of the cube's appearance.

### 7. Rotational Increments

```cpp
A += 0.005;
B += 0.005;
```

---

These increments in the rotation angles A and B cause the cube to continuously rotate on the screen.

**_Features_**
Real-time rendering of a rotating 3D cube using ASCII characters.
Perspective projection using Z-buffering for accurate depth calculation.
Customizable cube size, rotation speed, and screen resolution.

---

### How to Run

_Compile the program using a C++ compiler:_

## g++ -o spinning_cube spinning_cube.cpp -lm

_Run the program:_

## ./spinning_cube

This will render the spinning cube in your terminal.
