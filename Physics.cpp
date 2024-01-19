/**************************************************************
 * Source file:
 *  Physics
 * Author:
 *  Gergo Medveczky
 * Summary:
 *  The implementation of physics functions to calculate gravity, drag, soundspeed and air density,
 **************************************************************/

#include "Physics.hpp"
#include <cassert>
#include <cmath>

/*******************************************
 * CALC AIR DENSITY
 * Linear Interpolation for Air Density and 
 * select the right range values in the map.
 ******************************************/
double calcAirDensity(double altitude)
{
    const Mapping airDensityMapping[] =
    {
         {0.0,1.2250000},
         {1000,1.1120000},
         {2000,1.0070000},
         {3000,0.9093000},
         {4000,0.8194000},
         {5000,0.7364000},
         {6000,0.6601000},
         {7000,0.5900000},
         {8000,0.5258000},
         {9000,0.4671000},
         {10000,0.4135000},
         {15000,0.1948000},
         {20000,0.0889100},
         {25000,0.0400800},
         {30000,0.0184100},
         {40000,0.0039960},
         {50000,0.0010270},
         {60000,0.0003097},
         {70000,0.0000828},
         {80000,0.0000185}
    };
    //Linear Interpolation calculation for AirDensity
    double airDensity = linearInterpolation1(airDensityMapping,sizeof(airDensityMapping)/sizeof(airDensityMapping[0]), altitude);
    return airDensity;
}

/******************************************
 * CALC AIR DENSITY
 * Linear Interpolation for Speed of Sound 
 * and select the right range values in the
 * map.
 *****************************************/
double calcSoundSpeed(double altitude)
{
    const Mapping soundSpeedMapping[] =
    {
         {0.0,340},
         {1000,336},
         {2000,332},
         {3000,328},
         {4000,324},
         {5000,320},
         {6000,316},
         {7000,312},
         {8000,308},
         {9000,303},
         {10000,299},
         {15000,295},
         {20000,295},
         {25000,295},
         {30000,305},
         {40000,324}
    };
    //Linear Interpolation calculation for SoundSpeed
    double soundSpeed = linearInterpolation1(soundSpeedMapping,sizeof(soundSpeedMapping)/sizeof(soundSpeedMapping[0]), altitude);
    return soundSpeed;
}
/******************************************
 * CALC DRAG COEFFICIENT
 * Linear Interpolation for Drag Coeffiecient 
 * and select the right range values in the map
 *****************************************/
double calcDrag(double mach)
{
    const Mapping cDragMapping[] =
    {
         {0.300,0.1629},
         {0.500,0.1659},
         {0.700,0.2031},
         {0.890,0.2597},
         {0.920,0.3010},
         {0.960,0.3287},
         {0.980,0.4002},
         {1.000,0.4258},
         {1.020,0.4335},
         {1.060,0.4483},
         {1.240,0.4064},
         {1.530,0.3663},
         {1.990,0.2897},
         {2.870,0.2297},
         {2.890,0.2306},
         {5.000,0.2656}
    };
    //Linear Interpolation calculation for Drag Coefficient
    double cDrag = linearInterpolation1(cDragMapping,sizeof(cDragMapping)/sizeof(cDragMapping[0]), mach);
    return cDrag;
}

/******************************************
 * CALC GRAVITY
 * Linear Interpolation for Gravity
 * and select the right range values in the
 * map.
 *****************************************/
double calcGravity(double altitude)
{
    const Mapping gravityMapping[] =
    {
        {0.0,9.807},
        {1000,9.804},
        {2000,9.801},
        {3000,9.797},
        {4000,9.794},
        {5000,9.791},
        {6000,9.788},
        {7000,9.785},
        {8000,9.782},
        {9000,9.779},
        {10000,9.776},
        {15000,9.761},
        {20000,9.745},
        {25000,9.730}
    };
    //Linear Interpolation calculation for gravity
    double gravity = linearInterpolation1(gravityMapping,sizeof(gravityMapping)/sizeof(gravityMapping[0]), altitude);
    return gravity;
}

/******************************************
 * LINEAR INTERPOLATION
 * Draws two values from the graphs and 
 * calculates the exact number.
 *****************************************/
double linearInterpolation1(const Mapping mapping[], int numMapping, double domain)
{
    // off the scale on the small end
    if (domain < mapping[0].domain)
        return mapping[0].range;

    // within the table
    for (int i = 0; i < numMapping - 1; i++)
    {
        // the domain must be in order
        assert(mapping[i + 0].domain < mapping[i + 1].domain);
        if (mapping[i + 0].domain <= domain && domain <= mapping[i + 1].domain)
            return linearInterpolation3(mapping[i + 0], mapping[i + 1], domain);
    }

    // off the scale on the large end
    return mapping[numMapping - 1].range;
}

/******************************************
 * LINEAR INTERPOLATION
 * Returns the range for the given values
 * to calculate the exact number needed.
 *****************************************/
double linearInterpolation2(double d0, double r0,
    double d1, double r1, double d)
{
    assert(abs(d1 - d0) >= abs(d - d0));
    double range = r0 + (r1 - r0) * (d - d0) / (d1 - d0);
    assert(abs(r1 - r0) >= abs(range - r0));
    return range;
}

/******************************************
 * LINEAR INTERPOLATION
 * Draws two values from the graphs and 
 * calculates the exact number.
 *****************************************/
double linearInterpolation3(const Mapping& zero,
    const Mapping& one,
    double d)
{
    return linearInterpolation2(zero.domain, zero.range, one.domain, one.range, d);
}
