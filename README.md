# Game Engine

A modern **C++20 component-based game engine** built with **SDL3**, **FMOD**, **Box2D**, and **RapidJSON**.

The engine is designed around a modular, system-driven architecture where gameplay objects are composed of reusable components. Included with the engine is a demo game showcasing actors, components, tilemaps, physics interactions, audio, and UI functionality.

---

## Features

### Component-Based Architecture

- Actor/Component framework
- Reusable gameplay components
- Data-driven design
- Easy system extension
- Modular game object composition

### Engine Systems

#### Renderer System
- SDL3-based rendering
- Sprite rendering
- Tilemap rendering
- Camera support
- UI rendering

#### Physics System
- Box2D integration
- Rigid body simulation
- Collision detection
- Trigger events
- Physics-driven gameplay

#### Audio System
- FMOD integration
- Sound effect playback
- Music playback
- Runtime audio controls

#### Input System
- Keyboard input handling
- Mouse input handling
- Input state tracking
- Action-based gameplay input

### Serialization

- RapidJSON-based serialization
- Scene loading and saving
- Actor serialization
- Component serialization

---

## Architecture

The engine follows a component-based design where Actors act as containers for reusable Components.

```text
Actor
??? TransformComponent
??? SpriteComponent
??? RigidbodyComponent
??? AudioComponent
??? Custom Components
```

This approach allows gameplay behavior to be composed without deep inheritance hierarchies, resulting in a flexible and maintainable codebase.

---

## Demo Game

The repository includes a demo game used to demonstrate the engine's capabilities.

### Demonstrated Features

- Actor creation and management
- Custom components
- Physics interactions
- Tilemap rendering
- Audio playback
- User interface elements
- Scene serialization
- Component-based gameplay logic

The demo serves as both a showcase and a reference implementation for new projects built on the engine.

---

## Technologies

### Core Libraries

- **C++20**
- **SDL3** - Windowing, rendering, and input
- **FMOD** - Audio and sound management
- **Box2D** - 2D physics simulation
- **RapidJSON** - Serialization and data loading

---

## Project Structure

```text
Engine/
?
??? Engine/
?   ??? Actors/
?   ??? Components/
?   ??? Audio/
?   ??? Physics/
?   ??? Rendering/
?   ??? Input/
?   ??? Serialization/
?
??? DemoGame/
?   ??? Assets/
?   ???