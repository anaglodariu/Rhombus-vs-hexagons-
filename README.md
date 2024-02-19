# Rhombus-vs-hexagons-
Similar game to "Plants vs Zombies"

![Screenshot 2024-02-20 001915](https://github.com/anaglodariu/Rhombus-vs-hexagons-/assets/94357049/2a9c74cd-0cce-4de5-ad63-4b01c5cc4955)

Core Functionality
==
- Construction of scene elements:
  - Game scene geometry drawing
  - Drawing rhombus geometry
  - Drawing enemy geometry
  - Star geometry drawing
    
- Animations:
  - Enemy movement on line
  - Projectile movement and rotation
  - Diamond disappearing animation
  - Enemy disappearance animation
    
- Game Behavior:
  - Detecting the selection of a game cell by pressing the left mouse button and placing a diamond in the cell
  - Enemies spawn at random intervals
  - Detecting that an enemy has completely crossed a line
  - Projectile spawn near a diamond when there is enemy on line
  - Projectile-enemy collision detection
  - Diamond-Enemy Collision Detection

Advanced features
==
- Drag & drop behavior
- GUI drawing of 4 borders containing bounding rectangles and the 4 types of 5p diamonds
- Detection of selection and display of diamond on screen at cursor position while left mouse button is pressed
- Detecting that the left mouse button is no longer pressed when the mouse position is inside a valid cell
- Quantifying the number of lives left, initially 3, and displaying them
- Detecting the deletion selection of a rhombus by pressing the right mouse button in the cell where a rhombus is already located
- Stars appear on the screen, at certain intervals
- Detecting the selection of an asterisk by pressing the left mouse button and its disappearance from the screen
- Drawing in the GUI, under each type of diamond, the number of stars required to place that type
- Allowing a diamond to be placed, only when the number of stars is sufficient
- Quantification of collected and consumed stars, drawing in GUI the number of stars present at the time of drawing
- Color based game behavior management
- GUI drawing of 4 types of diamonds, differentiated by a specific color
- The appearance at certain intervals of 4 different types of enemies, differentiated by a specific color
- The appearance of the projectile next to a diamond that has a certain color, only when there is an enemy of the same color on its line
- Projectile appearance with the same color as that of the adjacent diamond that appeared
- Projectile-enemy collision detection, only if the projectile has the same color as the enemy
