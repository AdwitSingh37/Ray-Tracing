# SDL3 Ray Tracing

A simple 2D light and shadow simulation built with SDL3 in C++.

## What It Does

A light source casts rays in all directions. Another circle acts as a blocker, casting a shadow behind it. 
## Dependencies

- [SDL3](https://github.com/libsdl-org/SDL)
- A C++ compiler with C++11 or later

## Building

```bash
g++ window.cpp -o app -lSDL3
```

## How It Works

The light source casts rays at 0.5° increments across all 360°. Each ray travels outward until it either hits a blocker circle or reaches the edge of the window. The result is drawn as a line, producing a basic shadow effect.

## Future Plans

- Extend the simulation to 3D

