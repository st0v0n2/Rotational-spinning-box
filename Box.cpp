#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include<chrono> 
#include<thread>
float A, B, C;

float cubeWidth = 44;
int width = 120, height = 40;
int comwh = width*height;
float Zaxisbuffer[120 * 40];
char buffer[120 * 40];
int backgroundascoi = ' ';
//background
int idx;

float incrementSpeed = 1.8;

int distanceFromCam = 250;

float x, y, z;

float K1 = 40;
float kkk;
int xp, yp;

float calculateX(int i, int j, int k)
{
    return j * sin(A) * sin(B) * cos(C) - k * 
    cos(A) * sin(B) * cos(C) + j * cos(A) * 
    sin(C) + k * sin(A) * sin(C) + i * 
    cos(B) * cos(C);
}

// that was wrong the correct one is here ^

//    j * cos(A) * cos(C) + k * sin(A) * sin(B) * 
//    sin(C) + k * cos(A) * sin(B) * sin(C) - i * 
//    cos(B) * sin(C);

/*
j * sin(A) * sin(B) * cos(C) - k * 
cos(A) * sin(B) * cos(C) + j * cos(A) * 
sin(C) + k * sin(A) * sin(C) + i * 
cos(B) * cos(C);
*/

float calculateY(int i, int j, int k)
{
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
    j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
    i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k)
{
    //if (k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B) < -1 || 
    //k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B) > 1)
    //{
    //    return 0;
    //}
    
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateSurface(float cubeX, float cubeY, float cubeZ, int ch)
{
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    //if (calculateZ(cubeX, cubeY, cubeZ) < -1 || calculateZ(cubeX, cubeY, cubeZ) > 1)
    //{
    //    return ' ';
    //}
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
    
    kkk =  1/z;
    
    //xp = (int)(width/2 - 2 * cubeWidth + K1 * kkk * x * 2); shifts the thing to the left
    xp = (int)(width/2 + K1 * kkk * x * 2);
    //middle of screen
    //xp = (int)(width/2 - 2 * -cubeWidth + K1 * kkk * x * 2); //right of screen
    yp = (int)(height/2 + K1 * kkk * y);

    idx = xp+yp*width;
    if (idx>=0 && idx < width * height)
    {
        if (kkk>Zaxisbuffer[idx])
        {
            Zaxisbuffer[idx] = kkk;
            buffer[idx] = ch;
        }
    }
}

void calculateSurface2(float cubeX, float cubeY, float cubeZ, int ch)
{
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

    kkk =  1/z;
    
    //xp = (int)(width/2 - 2 * cubeWidth + K1 * kkk * x * 2); //shifts the thing to the left
    xp = (int)(width/2 + K1 * kkk * x * 2);
    //middle of screen
    //xp = (int)(width/2 - 2 * -cubeWidth + K1 * kkk * x * 2); //right of screen
    yp = (int)(height/2 + K1 * kkk * y);

    idx = xp+yp*width;
    if (idx>=0 && idx < width * height)
    {
        if (kkk>Zaxisbuffer[idx])
        {
            Zaxisbuffer[idx] = kkk;
            buffer[idx] = ch;
        }
    }
} 

//clear screen with \x1b[2j
int main()
{
    printf("\x1b[2j");
    while(true)
    {
        memset(buffer, backgroundascoi, width * height);
        memset(Zaxisbuffer, 0, width * height * 4);
        for(float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed)
        {
            for(float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed)
            {
                calculateSurface(cubeX, cubeY, -cubeWidth, '.');
                calculateSurface(cubeWidth, cubeY, cubeX, '+');
                calculateSurface(-cubeWidth, cubeY, -cubeX, '^');
                calculateSurface(-cubeX, cubeY, cubeWidth, '1');
                //top and bottom
                //calculateSurface(cubeX, -cubeWidth, -cubeY, '-');
                //calculateSurface(cubeX, cubeWidth, cubeY, ',');
                
                
                //Due to z stripping into each other, you make it into one full
                //functions of the x,y, and z axis and encount for 
                //negative z axis (z clipping)
            }
        }
        //printf("\e[2j");
        printf("\e[2j\e[H");
        for(int k = 0; k < width * height; k++)
        {
            putchar(k % width ? buffer[k] : 10);
        }
        A+= 0.005;
        B+= 0.005;
        //usleep(1000);
        
        
        /*
        
        memset(buffer, backgroundascoi, width * height);
        memset(Zaxisbuffer, 0, width * height * 4);
        for(float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed)
        {
            for(float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed)
            {
                calculateSurface2(cubeX, cubeY, -cubeWidth, '^');
                calculateSurface2(cubeWidth, cubeY, cubeX, '$');
                calculateSurface2(-cubeWidth, cubeY, -cubeX, '@');
                calculateSurface2(-cubeX, cubeY, cubeWidth, '&');
                calculateSurface2(cubeX, -cubeWidth, -cubeY, '9');
                calculateSurface2(cubeX, cubeWidth, cubeY, 'M');
            }
        }
        printf("\x1b[H");
        for(int k = 0; k < width * height; k++)
        {
            putchar(k % width ? buffer[k] : 10);
        }
        A+= 0.005;
        B+= 0.005;
        //usleep(1000);
        */
    }
    
    
    return 0;
}