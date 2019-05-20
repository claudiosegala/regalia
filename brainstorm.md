# Menu State

To show the menu options (Play, Story, Credits)

### Path

ArrowDown → Go up on option

ArrowUp → Go down on option

X → Push Option

# Credits State

To show an image of us.

### Path

O → MenuState → Pop itself

# Story State

To show a text with the story

### Path

ArrowDown → Go up on text

ArrowUp → Go down on text

O → Menu State → Pop Itself

# Prepare State

Just to show an animation before the PlayState

### Path

5s → Main State → Pop Itself and add Main State

# Play State

The fight is in here

### Path

SELECT → ScoreTable (PAUSE) → add ScoreTable

"Set end" → ScoreTable (SET_ENDED) → add ScoreTable

"Last set end" → ScoreTable(MATCH_ENDED) → add ScoreTable

# Score State

Control sets and pause. Shows score of the current match

### Path

R1 → continue (if in PAUSE) → Pop itself

R2 → restart → Pop itself, Pop PlayState, Push PrepareState

L1 → next set (if SET_ENDED) → Pop itself, Pop PlayState, Push PlayState

L2 → quit → RequestQuit

# Constants file
```c++
#pragma once

namespace Constants
{
    namespace Penguin
    {
        const float SHOT_COOLDOWN = 0.5;
    }

    namespace Alien
    {
        const float REST_TIME = 1;
        const float MOVEMENT_SPEED = 500;
        const float ROTATION_SPEED = 10;
    }
    // ...
}
```

# Game Meta Data
```c++
class GameMetaData {
    public:
        static const 
        static bool Finished;
        static int Set;
        enum ResultType {
            NONE,
            PLAYER1_VICTORY,
            PLAYER2_VICTORY
        };
        static ResultType Result[NUMBER_OF_SETS];
}
```
# Player
```c++
class Player : GameObject {
    public:
        int hp;
        PersonaTypes persona; // which persona

        IsMainObject() { return true; } // identify the main object
}
```
# Bullet
```c++
class Bullet : GameObject {

}
```
