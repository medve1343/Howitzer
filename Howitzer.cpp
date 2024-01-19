/**************************************************************
 * Source file:
 *		Howitzer.h
 * Author:
 *		Gergo Medveczky
 * Summary:
 *		Functions needed for running the game. This is where you
 *		draw, advance, and handle the input from and for the
 *		user.
 **************************************************************/

#include <cmath>
#include "Howitzer.h"
#include <iomanip>
#include <iostream>

 /******************************************
 * DRAW
 * draws the different things for the game
 *****************************************/
void Simulator::draw(const Interface& pUI)
{
	// draw everything
	ogstream gout(Position(10.0, ptUpperRight.getPixelsY() - 20.0));

	// draw the ground first
	ground.draw(gout);

	// draw the howitzer
	gout.drawHowitzer(artillery.getPosition(), artillery.getAngle().getRadians(), time);

	gout.setf(ios::fixed | ios::showpoint);
	gout.precision(1);
	Position textPos(23250.0, 19500.0);
	gout.setPosition(textPos);

	// draws the bullet if its alive
	// draw some text on the screen
	if (bullet.checkAlive())
	{
		gout.drawProjectile(bullet.getPosition(), 0.5);
		trajectory.draw(gout);
		gout << "altitude:\t\t\t\t" << bullet.getPosition().getMetersY() -
			ground.getElevationMeters(bullet.getPosition()) << "m\n" 
			<< "speed:\t\t\t\t\t\t" << bullet.getVelocity().getOverallVelocity() << "m/s\n"
			<< "distance:\t\t\t" << abs(artillery.getPosition().getMetersX()
			- bullet.getPosition().getMetersX()) << "m\n";
	}
	else
	{
		if (artillery.getAngle().getDegrees() == 360 || artillery.getAngle().getDegrees() == -360)
			artillery.setAngle(0);
		gout << "Angle:\t\t" << artillery.getAngle().getDegrees() << "°\n";
	} 
	if (time >= 0)
		gout << "Hang time:\t"<< time << "s\n";
}

/******************************************
* HANDLE INPUT
* takes input from the user and uses it
* to move the artillery angle and shoot.
*****************************************/
void Simulator::handleInput(const Interface& ui)
{
	// move a large amount
	if (ui.isRight())
		artillery.addAngle(0.05);
	if (ui.isLeft())
		artillery.addAngle(-0.05);

	// move by a little up or down
	if (ui.isUp())
		artillery.addAngle(artillery.getAngle().getRadians() >= 0 ? -0.003 : 0.003);
	if (ui.isDown())
		artillery.addAngle(artillery.getAngle().getRadians() >= 0 ? 0.003 : -0.003);

	// fire the bullet and increment time
	if (ui.isSpace() && !bullet.checkAlive())
	{
		time += 0.5;
		bullet.setAngle(artillery.getAngle().getRadians());
		bullet.fire();
	}
}

/******************************************
* ADVANCE
* Moves the simulator forward when called
*****************************************/
void Simulator::advance()
{
	// If bullet has been fired advance it
	if (bullet.checkAlive())
		bullet.advance(0.5);

	// Bullet trajectory
	trajectory.addTrajectory(bullet.getPosition());

	// Kills the bullet when it hits the ground and reset everything if it hits the target.
	if (ground.getElevationMeters(bullet.getPosition()) > bullet.getPosition().getMetersY() && bullet.hitTarget(ground.getTarget()))
	{
		bullet.kill();
		artillery.getPosition().setMetersX(random(300, 23000));
		artillery.getPosition().setMetersY(random(400, 600));
		ground.reset(artillery.getPosition());
		bullet.reset(artillery.getPosition());
		time = -0.5;
	}
	else if(ground.getElevationMeters(bullet.getPosition()) > bullet.getPosition().getMetersY())
	{
		bullet.kill();
		bullet.reset(artillery.getPosition());
		time = -0.5;
	}
}
