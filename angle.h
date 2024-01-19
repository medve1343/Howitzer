/***********************************************************************
 * Header File:
 *    Angle : Holds functions and attributes for Angle class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    All the unit tests for Velocity
 ************************************************************************/

#pragma once

#define PI 3.14159265359

/*********************************************
 * Angle
 * holds angle attributes for the given 
 * object using it
 *********************************************/
class Angle
{
private:
	double radians;
	friend class UnitTests;

public:
	// Default constructor
	Angle()	{ radians = 0; }
	// Non-Default constructor
	Angle(double radians)	{ this->radians = radians; }

	// Sets radians using atan2
	void setDxDy(double dx, double dy)	{ radians = atan2(dx, dy); }
	void addRadians(double newRadians) {radians += newRadians;}
	void setAngle(double angle) {radians = angle;}
	double getRadians() const {return radians;}
	double getDegrees() { return radians * 180 / PI; }
};
