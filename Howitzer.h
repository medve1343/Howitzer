/***********************************************************************
* Program:
*    Artillery : Code Complete
* Author:
*    Gergo Medveczky
* Summary:
*    Using openGL and real world math, we implement different forces
*		such as air speed, drag, gravity, etc. to calculate the
*		close, but approximate distance of a M777 howitzer artillery
*		shooting a projectile.
***********************************************************************/

#include <cassert>			// for ASSERT
#include "uiInteract.h"		// for INTERFACE
#include "uiDraw.h"			// for RANDOM and DRAW*
#include "ground.h"			// for GROUND
#include "position.h"		// for POINT
#include "artillery.h"		// for ARTILLERY
#include "Bullet.h"			// for BULLET
#include "Trajectory.hpp"	// for TRAJECTORY

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Simulator
{
public:
	// Non-Default Constructor
	Simulator(Position ptUpperRight) :
		ptUpperRight(ptUpperRight),
		ground(ptUpperRight),
		time(-0.5)
	{
		// Resets the ground based on the position of artillery.
		ground.reset(artillery.getPosition());

		// Changes current bullet position to artillery's position.
		bullet.changePosition(artillery.getPosition());
	}

	// Draw different things.
	void draw(const Interface& pUI);

	// Accept input from user
	void handleInput(const Interface& ui);
	
	// Moves the game forward
	void advance();

	// Instantiate objects
	Trajectory trajectory;				// for bullet trajectory
	Ground ground;							// the ground
	Artillery artillery;					// artillery on screen
	Position  ptUpperRight;				// size of the screen
	Bullet bullet;							// bullet to show when shot

	// Keeps track of time
	double time;							// amount of time since the last firing
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
	// the first step is to cast the void pointer into a game object. This
	// is the first step of every single callback function in OpenGL.
	Simulator* pSimulator = (Simulator*)p;

	// accept input
	pSimulator->handleInput(*pUI);

	// advance time by half a second.
	if (pSimulator->time >= 0.0)
		pSimulator->time += 0.5;

	// perform all the game logic
	pSimulator->advance();

	// Draw everything
	pSimulator->draw(*pUI);
}

// Sets distance for meters from pixels ratio
double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
	// Initialize OpenGL
	Position ptUpperRight;
	ptUpperRight.setPixelsX(700.0);
	ptUpperRight.setPixelsY(500.0);
	Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
	Interface ui(0, NULL,
		"Simulator",   /* name on the window */
		ptUpperRight);

	// Initialize the demo
	Simulator Simulator(ptUpperRight);

	// set everything into action
	ui.run(callBack, &Simulator);


	return 0;
}
