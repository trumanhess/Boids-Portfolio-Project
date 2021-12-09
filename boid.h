#ifndef __BOID_H_INCLUDED__
#define __BOID_H_INCLUDED__

#define NUMBOIDS 100

const float XMIN = { -500.0f };
const float XMAX = { 500.0f };
const float YMIN = { 0.0f };
const float YMAX = { 500.0f };
const float ZMIN = { -500.0f };
const float ZMAX = { 500.0f };
const float GOALPOS[3] = { 0.0f, 150.0f, 50.0f };
const float SPEEDLIMIT = { 100.0f };
const float BOUNDSMOVEAMOUNT = { 4.0f };
const float SEPARATIONAMOUNT = { 20.0f };

extern float VisualRange;

struct boid
{
	float x0, y0, z0;	// starting location	
	float vx, vy, vz;	// velocity			
	float x, y, z;		// current location	
};
extern boid Boids[NUMBOIDS];

//http://www.kfish.org/boids/pseudocode.html
void VectorDiv(float vec[], float div, float ret[]);
float BoidDistance(boid* b1, boid* b2);
void Coherence(boid *cb, float pos[]);
void Separation(boid *cb, float pos[]);
void BoundPosition(boid *cb, float pos[]);
void LimitVelocity(boid* cb);
void Alignment(boid* cb, float pos[]);
void Goal(boid* cb, float pos[]);

#endif