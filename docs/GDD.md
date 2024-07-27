# Game Design Document

## Game Title

**Stellar Salvage**

## Game Overview

**Stellar Salvage** is a 2D action-adventure game where players control a small spaceship from a top-down perspective.
The main objective is to navigate through space, collect valuable items, move obstacles like asteroids, and destroy
enemies to progress through levels.

## Table of Contents

1. [Game Concept](#game-concept)
2. [Gameplay Mechanics](#gameplay-mechanics)
3. [Game World](#game-world)
4. [Characters and Entities](#characters-and-entities)
5. [User Interface](#user-interface)
6. [Controls](#controls)
7. [Art and Sound](#art-and-sound)
8. [Technical Requirements](#technical-requirements)
9. [Development Timeline](#development-timeline)

## Game Concept

### Genre

- Action
- Adventure

### Platform

- PC (Windows, macOS, Linux)

### Target Audience

- Ages 10 and up
- Fans of space-themed games and action-adventure games

## Gameplay Mechanics

### Core Mechanics

- **Spaceship Control**: Players can move the spaceship in all directions using keyboard inputs.
- **Item Collection**: Players collect items scattered throughout the levels for points or power-ups.
- **Obstacle Interaction**: Players can move asteroids and other objects to clear paths or solve puzzles.
- **Combat**: Players can shoot projectiles to destroy enemies and obstacles.

### Objectives

- **Primary Objective**: Collect all valuable items in a level to advance to the next.
- **Secondary Objectives**: Destroy enemies, avoid or move obstacles, and achieve high scores.

### Progression

- Levels become progressively more difficult with more enemies, complex obstacles, and intricate layouts.

## Game World

### Setting

- The game is set in various sectors of space, each with unique backgrounds, obstacles, and enemy types.

### Levels

- **Sector 1**: Introduction to basic mechanics with few enemies and simple obstacles.
- **Sector 2**: Increased number of enemies and introduction of moving asteroids.
- **Sector 3**: Complex layouts requiring strategic movement and item collection.
- **Sector 4**: Advanced enemies with unique behaviors and more challenging item locations.
- **Sector 5**: Boss level with a powerful enemy guarding the final item collection.

## Characters and Entities

### Player Character

- **Spaceship**: The player's avatar with capabilities to move, shoot, and interact with the game world.

### Non-Player Characters

- **Enemies**: Various types of hostile entities with different behaviors and attack patterns.
- **Asteroids**: Moveable obstacles that can be used strategically to block enemy paths or create safe zones.
- **Items**: Collectible objects that provide points or power-ups.

## User Interface

### Main Menu

- Start Game
- Options (Settings for audio, controls, etc.)
- Exit

### In-Game HUD

- **Score**: Displays the current score based on collected items and defeated enemies.
- **Health**: Shows the spaceship's current health status.
- **Mini-Map**: Provides an overview of the current level layout.

### Pause Menu

- Resume Game
- Options
- Main Menu

## Controls

- **Movement**: Arrow keys or WASD for moving the spaceship.
- **Shooting**: Spacebar or left mouse button to shoot projectiles.
- **Interaction**: E key or right mouse button to interact with objects (move asteroids).
- **Pause**: Escape key to pause the game and bring up the pause menu.

## Art and Sound

### Art Style

- 2D pixel art with a vibrant color palette to depict various space environments and entities.

### Sound Effects

- **Spaceship Movement**: Subtle thruster sounds.
- **Item Collection**: A pleasant chime or beep.
- **Shooting**: Laser or projectile sound effects.
- **Enemy Destruction**: Explosion or destruction sound.

### Music

- Ambient space-themed background music with increasing intensity for higher levels.

## Technical Requirements

### Software

- C++ with SDL or SFML for rendering.
- CMake for build configuration.
- Any text editor or IDE for coding (e.g., Visual Studio, CLion, or VS Code).

### Hardware

- Minimum:
    - CPU: Dual-core processor
    - RAM: 2 GB
    - Graphics: Integrated graphics
    - Storage: 100 MB available space

## Development Timeline

### Milestones

1. **Week 1-2**: Project setup, basic game loop, and rendering backend abstraction.
2. **Week 3-4**: Implement spaceship movement, basic item collection, and simple obstacles.
3. **Week 5-6**: Add enemy entities and basic combat mechanics.
4. **Week 7-8**: Level design and progression mechanics.
5. **Week 9-10**: User interface and HUD implementation.
6. **Week 11-12**: Art and sound integration.
7. **Week 13-14**: Testing, bug fixing, and polish.
8. **Week 15**: Final testing and release preparation.

## Conclusion

**Stellar Salvage** aims to provide an engaging and challenging space adventure for players of all ages. With its core
mechanics, progressively challenging levels, and vibrant art style, it promises to be an exciting addition to the
action-adventure genre.
