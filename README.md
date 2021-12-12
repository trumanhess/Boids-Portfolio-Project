# OpenGL Boids Simulation
An OpenGL boid (bird-oid) simulation project written in C++.
![boids simulation](./Images/boids_running.gif)

This project simulates the behavior of bird like objects as outlined by [Craig Reynolds](http://www.red3d.com/cwr/).
My program follows the three main rules of the boid algorithm:

1. Separation
  Avoid collsion with local boids.
2. Alignment
  Move towards the average vector of the flock.
3. Cohesion
  Move towards the average position of the flock.

Certain simulation parameters are made editable so that the user can create countless unique boid flocks. Below is a screenshot of the window that users can use to edit parameters like the alignment, cohesion, separation factors as well as the time step (to slow or speed up the program) and the visual range of each boid (increasing or decreasing this variable will result in bigger or smaller flocks respectively).
![user interface window](./Images/edit_window.PNG)

