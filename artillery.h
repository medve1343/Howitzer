/***********************************************************************
 * Header File:
 *    Artillery : Holds functions and attributes for Artillery class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    Artillery attributes are stored here along with the angle of the
 *		artillery and other functions needed for it.
 ************************************************************************/

#pragma once
#include "position.h"
#include "angle.h"

 /*************************************************************************
  * Artillery
  * Class to hold attributes and functions to move and position for artillery.
  *************************************************************************/
class Artillery
{
private:
	// Instantiate a position
	Position position;

	// Instantiate an Angle
	Angle angle;

public:
	// Default constructor
	Artillery()
	{
		position.setPixelsX(350);
		position.setPixelsY(500);
	}

	// Returns position of artillery

	Position& getPosition()				{ return position; }
	Angle getAngle() const				{ return angle; }
	void addAngle(double newAngle)	{ angle.addRadians(newAngle); }
	void setAngle(double sangle) {angle.setAngle(sangle);}
};
