# Pong

This is a re-make of the classic Pong game implemented in C++ using SFML for graphics and sound. No other external libraries were used.

## Building

```bash
> mkdir Release
> cd Release
> cmake ..
> make
> ./pong
```

## Core Features
All core features have been implemented and work correctly.

## Implemented Bonus Features

- Pausing when the game is minimized
- Paddle acceleration/deceleration
- User-selectable difficulty
- Sound effects
- Title screen
- Speed of paddle affects the bounce direction of the ball

## Known Issues
- Upon exiting, `AL lib` cleanup error messages are occasionally displayed in the terminal.
- At high speeds, it is possible for the ball to travel through the paddle.

## Lessons Learned / Things I Would Change

- **Implement a resource manager**. Passing references to resources (Textures, SoundBuffers, etc.) down the chain of Game States was fine at first, but as the amount of resources grew, this approach did not scale easily. It is clumsy and error-prone.

## Time Spent

Activity | Time
---|---
Implementing core features | 9 hours
Implementing bonus features | 6 hours
Fighting with the C++ compiler | 5 hours
