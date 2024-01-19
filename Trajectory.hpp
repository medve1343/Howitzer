//
//  Trajectory.hpp
//  Lab08
//
//  Created by Gergo Medveczky on 3/26/22.
//

#ifndef Trajectory_hpp
#define Trajectory_hpp
#include "position.h"
#include <stdio.h>
#include <list>
#include <iostream>
class Trajectory
{
private:
    std::list<Position>trajectories;
public:
    Trajectory()
    {
        
    }
    Trajectory(Position pos)
    {
        trajectories.push_back(pos);
    }
    void addTrajectory(Position pNext)
    {
        trajectories.push_front(pNext);
        if(trajectories.size() >20)
            trajectories.pop_back();
    }
    void draw(ogstream &gout)
    {
        int color =0;
        for (Position iterator:trajectories)
        {
            gout.drawProjectile(iterator, (0.5*(double)color));
            color++;
        }
    }
};

#endif /* Trajectory_hpp */
