/***********************************************************************
 * Source File:
 *    Velocity.h
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Functions needed for the velocity class
 ************************************************************************/

#include "velocity.h"
#include "Physics.hpp"

 /******************************************
 * Velocity : default constructor
 * create a velocity with 0 dx and dy
 *****************************************/
Velocity::Velocity()
{
	overAllVelocity = 827;
	dx = 0;
	dy = 0;
}

/******************************************
* Velocity : non-default constructor
* create a velocity with given dx and dy
*****************************************/
Velocity::Velocity(double dx, double dy)
{
	this->dx = dx;
	this->dy = dy;
}

/******************************************
* Reverse
* inverts the current dx and dy values
*****************************************/
void Velocity::reverse()
{

	dx = -dx;
	dy = -dy;
}

/******************************************
* UPDATE
* inverts the current dx and dy values
*****************************************/
void Velocity::update(double altitude, double angle, double time, Position& pos)
{
	// Calculate the initial Dx and Dy
	double dx0 = sin(angle) * overAllVelocity;
	double dy0 = cos(angle) * overAllVelocity;

	// Calculate air density
	double airDensity = calcAirDensity(altitude);

	// Calculate sound speed
	double soundSpeed = calcSoundSpeed(altitude);

	// Calculate mach
	double mach = overAllVelocity / soundSpeed;

	// Calculate drag
	double cDrag = calcDrag(mach);

	// Calculate gravity
	double gravity = calcGravity(altitude);

	// Calculate the force
	double f = 0.5 * cDrag * airDensity * (overAllVelocity * overAllVelocity) * 0.0188424;
	double acceleration = f / 46.7;

	//Calculate ddx and ddy
	double ddx = -sin(angle) * acceleration;
	double ddy = -gravity - cos(angle) * acceleration;

	//Calculate dx and dy
	dx = dx0 + ddx * time;
	dy = dy0 + ddy * time;

	// Calculate the overall velocity with dx and dy
	overAllVelocity = sqrt((dx * dx) + (dy * dy));

	// Calculates the new dx and dy velocity
	double newX = dx0 * time + 0.5 * ddx * (time * time);
	double newY = dy0 * time + 0.5 * ddy * (time * time);

	// updates the meters for the position
	pos.addMetersX(newX);
	pos.addMetersY(newY);
}

void Velocity::resetVelocity()
{
    overAllVelocity = 827;
    dx = 0;
    dy = 0;
}
