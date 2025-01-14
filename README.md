# Geometric Arcader
 
### What is a Geometric Arcader?
Geometric Arcader is a 2D arcade game but implemented in the acquired 3D PPGA
throughout GEOA which allows us to then use the 'redundant 3rd dimension' as
the energy-container. You are a small rectangle/triangle constantly moving in a
box which collides with the screen window. You continuously gain an amount of
energy but depending on your movement speed you lose energy. The movement
can only change directions by colliding with an object or rotation around a pillar.
Pressing buttons changes the overall movement speed or initiates the
rotation. What is extra in this game is up to the student.

### How did I use Geometric Algebra in my game?
I used geometric algebra formulas to
1. Move the player character at two different possible speeds in the scene
3. Make the player character able to rotate around objects
4. Determine if any collisions happen with the window borders

Formulas used in the project are:
1. Translation and Rotation

![image](https://github.com/user-attachments/assets/a0af4469-27a9-4433-95e4-68548b2d0e90)

2. Containment test to determine collisions, which is a meet (operator^) of the player position and the collider plane. Collision happens if the meet is equal to 0. The size of the player sprite is also taken into account here.

And here is an overview of the calculations
1. Player movement

![image](https://github.com/user-attachments/assets/6caa4fde-f73a-4cda-8d41-c6412ef74d3c)

2. Player rotation
 
![image](https://github.com/user-attachments/assets/722e528c-8619-4ccf-985b-519bda8ce3d1)

3. Collisions

![image](https://github.com/user-attachments/assets/782cc361-d754-44f9-ac35-3618fcfc32ad)
![image](https://github.com/user-attachments/assets/5ba78334-514c-4d29-aee7-c6e3a762dca4)


