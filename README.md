# Breakout

W Kavanagh. June Summer 2024

## controls
Using top number bar - 
1 = keyboard input.
2 = mouse click input.
3 = mouse follow.

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist


# Time Details and Changelist
<Add information to this section about the time you've taken for this task along with a professional changelist.>
21/10/24 20:00 - 20:05 - Fixed compiler issues. Removed #include "PowerupFireBall.h" from PoweupBase.h
21/10/24 20:05 - 20:10 - Code efficiency, removed double input check for movement. Paddle no longer checks input in movement functions, handled by game manager.
21/10/24 20:10 - 20:40 - Added mouse click to paddle
22/10/24 20:00 - 20:30 - Added Paddle to follow mouse 
22/10/24 22:00-23:00 - Added Fast paddle powerup including UI display
23/10/24 8:35 - 8:40 - Paramterize power up spawn in Game manager
23/10/24 8:40- 9:35 CameraShake on Death Added
23/10/24 9:35- 9:45 Added option to switch between inputs using 1,2,3