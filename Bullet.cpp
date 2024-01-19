/**************************************************************
 * Source file:
 *		Bullet.h
 * Author:
 *		Gergo Medveczky
 * Summary:
 *		Functions needed for the positioning and availability
 *    of a bullet object.
 **************************************************************/

#include "Bullet.h"
#include <cmath>

 /******************************************
  * Bullet : default constructor
  * sets up the bullets starting values.
  *****************************************/
Bullet::Bullet()
{
	bulletAngle = 0;
	alive = false;
}

/******************************************
* ADVANCE
* Updates the velocity and angle of
* the bullet.
*****************************************/
void Bullet::advance(double time)
{
	// Updates dx and dy values of velocity.
	velocity.update(position.getMetersY(), bulletAngle, time, position);

	// Updates bullet angle with dx and dy values.
	bulletAngle = atan2(velocity.getDx(), velocity.getDy());
}

/******************************************
* RESET
* Updates the velocity's angle with the
* given angle and then resets the overall
* velocity back to default.
*****************************************/
void Bullet::reset(Position & newPosition)
{
    changePosition(newPosition);
    velocity.resetVelocity();
}

/******************************************
* HIT TARGET
* Checks if the bullet has hit within 250
* meters of the target.
*****************************************/
bool Bullet::hitTarget(const Position& target)
{
	return (abs(position.getMetersX() - target.getMetersX()) < 250 && abs(position.getMetersY() - target.getMetersY()) < 250);
}
