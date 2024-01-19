/***********************************************************************
 * Header File:
 *    Bullet : Holds functions and attributes for bullet class
 * Author:
 *    Gergo Medveczky
 * Summary:
 *    All required functions to show the location, position, and
 *    current state of the given bullet object.
 ************************************************************************/

#pragma once
#include "position.h"
#include "velocity.h"
#include "Physics.hpp"

 /*************************************************************************
  * Bullet
  * Class to hold attributes and functions to move and position the
  * location and state of the bullet object.
  *************************************************************************/
class Bullet
{
private:
	// Instatiate Position
	Position position;

	// Instatiate Velocity
	Velocity velocity;

	// Bullets angle
	double bulletAngle;

	// Bullets current state
	bool alive;

public:
	// Default Constructor
	Bullet();

	// Non-Default Constructor
	Bullet(Position pos)
	{
		position.setPixelsX(pos.getPixelsX());
		position.setPixelsY(pos.getPixelsY());
		position.setMetersX(pos.getMetersX());
		position.setMetersY(pos.getMetersY());
	}

	// Changes position to 
	void changePosition(Position pos)
	{
		position.setMetersX(pos.getMetersX());
		position.setMetersY(pos.getMetersY());
		position.setPixelsX(pos.getPixelsX());
		position.setPixelsY(pos.getPixelsY());
	}
	// Setter
	void setAngle(double angle)			{ bulletAngle = angle;	}
	void kill()									{ alive = false;			}
	void fire()									{ alive = true;			}

	// Getter
	double displayBulletAngle() const	{ return bulletAngle;	}
	bool checkAlive()							{ return alive;			}
	Position getPosition() const			{ return position;		}
	Velocity getVelocity() const			{ return velocity;		}

	// Advances bullet
	void advance(double time);

	// Checks if bullet hit the target
	bool hitTarget(const Position& target);

	// Resets the bullets position
	void reset(Position & newPosition);
};
