/***********************************************************************
 * Header File:
 *    Velocity : Holds functions and attributes for velocity class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Holds the functions and attributes for velocity
 ************************************************************************/

#pragma once

#include <cmath>
#include "position.h"
#define PI 3.14159265

 /*********************************************
  * Velocity
  * holds velocity for given object using it
  *********************************************/
class Velocity
{
private:
	double dx;
	double dy;
	friend class UnitTests;
	double overAllVelocity;

public:
	// Default constructor
	Velocity();

	// Non-Default constructor
	Velocity(double dx, double dy);

	// take inverse of dx and dy values
	void reverse();

	// Adds velocity that is passed in with its current values
	void addDx(double dx) { this->dx += dx; }
	void addDy(double dy) { this->dy += dy; }

	// Getters
	double getDx() const { return dx; }
	double getDy() const  { return dy; }
	double getOverallVelocity() const { return overAllVelocity; }

	// Setters
	void setDx(double dx) { this->dx = dx; }
	void setDy(double dy) { this->dy = dy; }

	// updates dx and dy with physics
	void update(double altitude, double angle, double time, Position& pos);

	void resetVelocity();
};

