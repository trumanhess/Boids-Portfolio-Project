#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "boid.h"

float VisualRange = 20.0f;
boid Boids[NUMBOIDS];

void VectorDiv(float vec[], float div, float ret[])
{
	ret[0] = vec[0] / div;
	ret[1] = vec[1] / div;
	ret[2] = vec[2] / div;
}

float BoidDistance(boid* b1, boid* b2) 
{
	return sqrt((b1->x - b2->x) * (b1->x - b2->x) + (b1->y - b2->y) * (b1->y - b2->y) + (b1->z - b2->z) * (b1->z - b2->z));
}

void Coherence(boid *cb, float pos[])
{
	int i;
	struct boid* b;
	int numNeighbors = 0;
	pos[0] = 0.;
	pos[1] = 0.;
	pos[2] = 0.;

	for (i = 0, b = Boids; i < NUMBOIDS; i++, b++)
	{
		//not the same boid and within visual range, then add position vector to pos
		if (BoidDistance(cb, b) < VisualRange && cb != b)
		{
			pos[0] += b->x;
			pos[1] += b->y;
			pos[2] += b->z;
			numNeighbors += 1;
		}
	}

	if (numNeighbors)
	{
		VectorDiv(pos, numNeighbors, pos);

		pos[0] = (pos[0] - cb->x);
		pos[1] = (pos[1] - cb->y); 
		pos[2] = (pos[2] - cb->z);
	}
}

void Separation(boid *cb, float pos[])
{
	int i;
	struct boid* b;
	pos[0] = 0.;
	pos[1] = 0.;
	pos[2] = 0.;

	for (i = 0, b = Boids; i < NUMBOIDS; i++, b++)
	{
		//not the same boid and distance is less than the separation amount, then add the difference between their distance
		if (cb != b && BoidDistance(cb, b) < SEPARATIONAMOUNT)
		{
			pos[0] += cb->x - b->x;
			pos[1] += cb->y - b->y;
			pos[2] += cb->z - b->z;
		}
	}
}

void Alignment(boid *cb, float pos[])
{
	int i;
	struct boid* b;
	int numNeighbors = 0;
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	for (i = 0, b = Boids; i < NUMBOIDS; i++, b++)
	{
		//within range and not the same boid, then add the velocities to the pos vec
		if (cb != b && BoidDistance(cb, b) < VisualRange)
		{
			pos[0] += b->vx;
			pos[1] += b->vy;
			pos[2] += b->vz;
			numNeighbors += 1;
		}
	}

	if (numNeighbors)
	{
		VectorDiv(pos, numNeighbors, pos);

		pos[0] = (pos[0] - cb->vx); 
		pos[1] = (pos[1] - cb->vy); 
		pos[2] = (pos[2] - cb->vz);
	}
}

void BoundPosition(boid *cb, float pos[])
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	if (cb->x < XMIN)
		pos[0] = BOUNDSMOVEAMOUNT;
	else if(cb->x > XMAX)
		pos[0] = -BOUNDSMOVEAMOUNT;

	if (cb->y < YMIN)
		pos[1] = BOUNDSMOVEAMOUNT;
	else if (cb->y > YMAX)
		pos[1] = -BOUNDSMOVEAMOUNT;

	if (cb->z < ZMIN)
		pos[2] = BOUNDSMOVEAMOUNT;
	else if (cb->z > ZMAX)
		pos[2] = -BOUNDSMOVEAMOUNT;
}

void LimitVelocity(boid *cb)
{
	float speed = sqrt(cb->vx * cb->vx + cb->vy * cb->vy + cb->vz * cb->vz);
	if (speed > SPEEDLIMIT)
	{
		cb->vx = (cb->vx / speed) * SPEEDLIMIT;
		cb->vy = (cb->vy / speed) * SPEEDLIMIT;
		cb->vz = (cb->vz / speed) * SPEEDLIMIT;
	}
}

void Goal(boid* cb, float pos[])
{
	pos[0] = (GOALPOS[0] - cb->x);
	pos[1] = (GOALPOS[1] - cb->y);
	pos[2] = (GOALPOS[2] - cb->z);
}