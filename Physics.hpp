/**************************************************************
 * Source file:
 *  Physics
 * Author:
 *  Gergo Medveczky
 * Summary:
 *  Prototype for physics calculate functions.
 **************************************************************/

#ifndef Physics_hpp
#define Physics_hpp
#include <stdio.h>

// Struct to make a dictionary in an array.
struct Mapping
{
    double domain;
    double range;
};
//Calculates air density.
double calcAirDensity(double altitude);
//Calculates sound speed.
double calcSoundSpeed(double altitude);
//Calculates drag coefficient.
double calcDrag(double mach);
//Calculates gravity.
double calcGravity(double altitude);

//LinearInterPolation functions
double linearInterpolation1(const Mapping mapping[], int numMapping, double domain);
double linearInterpolation2(double d0, double r0,
                                    double d1, double r1, double d);
double linearInterpolation3(const Mapping& zero, const Mapping& one, double d);

#endif /* Physics_hpp */
