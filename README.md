# Learing C by creating simple 2D Space War Game

Library, tools and art
- [Raylib v5.5](https://www.raylib.com/)
- [Sounds from bgxr.net](https://www.bfxr.net/)
- [Kenney's Assets](https://kenney.nl/assets/simple-space)
- [Tsoding NoBuild(nob.h)](https://github.com/tsoding/nob.h)

## Build
- Bootstrap the build system with `cc nob.c -o build`
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
- [ ] Define the projectile (bullet) object with attributes (position, direction/velocity, active status).
- [ ] Manage a collection of projectiles that can be reused.

#### 5. Firing Mechanic
- [ ] Detect the fire input (e.g., a key press).
- [ ] Implement a **rate limit** to control how quickly the player can fire.
- [ ] Create a new projectile, starting at the player's position, and set it moving upwards.

#### 6. Projectile Behavior
- [ ] Update the position of all active projectiles each frame.
- [ ] Display the active projectiles on the screen.
- [ ] Remove projectiles once they travel off the top edge of the screen.

---

### Phase 3: Enemies & Core Gameplay

#### 7. Enemy Definition & Spawning
- [ ] Define the enemy object with attributes (position, health, movement pattern, active status).
- [ ] Implement a system to continuously **spawn new enemies** at random horizontal positions at the top of the screen.

#### 8. Enemy Behavior
- [ ] Implement the enemy's movement (e.g., moving straight down).
- [ ] Display the active enemies on the screen.
- [ ] Remove enemies once they travel off the bottom edge of the screen.

#### 9. Projectile-to-Enemy Interaction
- [ ] Check for **collision** between all active projectiles and all active enemies.
- [ ] On collision: Remove the projectile, and reduce the enemy's health.
- [ ] If an enemy's health reaches zero, remove the enemy.

#### 10. Player-to-Enemy Interaction
- [ ] Check for **collision** between the player ship and all active enemies.
- [ ] On collision: Remove the enemy and reduce the player's health.
- [ ] Implement a **temporary invulnerability** period for the player after taking damage.

---

### Phase 4: User Experience & Polish

#### 11. Heads-Up Display (HUD)
- [ ] Implement a **Scoring System** that increases when enemies are destroyed.
- [ ] Display the current **Score** and the player's remaining **Health** on the screen.

#### 12. Game Flow & States
- [ ] Define and manage distinct game states (e.g., **Title Screen**, **Playing**, **Game Over**).
- [ ] Create a **Title Screen** where the game starts.
- [ ] Create a **Game Over Screen** that displays the final score and allows the player to restart.

#### 13. Audio Feedback
- [ ] Add **Background Music** to play during the game.
- [ ] Add sound effects for player actions (e.g., **firing a weapon**).
- [ ] Add sound effects for events (e.g., **explosions/hits**).

---

### Game Completion
- [ ] Conduct playtesting and adjust game parameters (speed, health, spawn rates) for balanced difficulty.
- [ ] Finalize asset loading and memory cleanup.