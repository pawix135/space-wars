# Learing C by creating simple 2D Space War Game

Library, tools and art
- [Raylib v5.5](https://www.raylib.com/)
- [Sounds from bfxr](https://www.bfxr.net/)
- [Kenney's Assets](https://kenney.nl/assets/simple-space)
- [Tsoding NoBuild(nob.h)](https://github.com/tsoding/nob.h)

## Build
- Bootstrap the build system with `cc nob.c -o nbuild` or `clang nob.c -o nbuild`
- Run the build executable

## Todo List

### Phase 1: Player Ship & Control

#### 1. Player Definition
- [x] Define the player object with attributes (position, size, speed, current health).
- [x] Establish the player's starting location (bottom center of the screen).

#### 2. Player Display
- [x] Implement a visual representation for the player ship (texture or shape). 
- [x] Draw the player ship to the screen during the game loop.

#### 3. Movement System
- [x] Allow the player to move horizontally based on key input.
- [x] Enforce screen boundaries to keep the player ship within the visible area.

---

### Phase 2: Shooting & Projectiles

#### 4. Projectile Definition
- [x] Define the projectile (bullet) object with attributes (position, direction/velocity, active status).
- [x] Manage a collection of projectiles that can be reused.

#### 5. Firing Mechanic
- [x] Detect the fire input (e.g., a key press).
- [x] Implement a **rate limit** to control how quickly the player can fire.
- [x] Create a new projectile, starting at the player's position, and set it moving upwards.

#### 6. Projectile Behavior
- [x] Update the position of all active projectiles each frame.
- [x] Display the active projectiles on the screen.
- [x] Remove projectiles once they travel off the top edge of the screen.

---

### Phase 3: Enemies & Core Gameplay

#### 7. Enemy Definition & Spawning
- [x] Define the enemy object with attributes (position, health, movement pattern, active status).
- [ ] Implement a system to continuously **spawn new enemies** at random horizontal positions at the top of the screen.

#### 8. Enemy Behavior
- [x] Implement the enemy's movement (e.g., moving straight down).
- [x] Display the active enemies on the screen.
- [x] Remove enemies once they travel off the bottom edge of the screen.

#### 9. Projectile-to-Enemy Interaction
- [x] Check for **collision** between all active projectiles and all active enemies.
- [x] On collision: Remove the projectile, and reduce the enemy's health.
- [x] If an enemy's health reaches zero, remove the enemy.

---

### Phase 4: User Experience & Polish

#### 10. Heads-Up Display (HUD)
- [x] Implement a **Scoring System** that increases when enemies are destroyed.
- [x] Display the current **Score** and the player's remaining **Health** on the screen.

#### 11. Game Flow & States
- [x] Define and manage distinct game states (e.g., **Title Screen**, **Playing**, **Game Over**).
- [x] Create a **Title Screen** where the game starts.
- [x] Create a **Game Over Screen** that displays the final score and allows the player to restart.

#### 12. Audio Feedback
- [x] Add **Background Music** to play during the game.

---

### Game Completion
- [x] Conduct playtesting and adjust game parameters (speed, health, spawn rates) for balanced difficulty.
- [x] Finalize asset loading and memory cleanup.
