<div align="center">

# Yunhai Engine

<br>

<p align="center">
  <img src="https://github.com/user-attachments/assets/e6b5ae45-967d-4898-bd96-16b49feddda6#gh-dark-mode-only" width="300">
</p>

<br>
<br>

**A lightweight C++ game engine focused on data-driven game development without traditional scripting.**

The engine is designed around the idea that game behavior,
properties, and content can be modified through built-in tools
and data rather than requiring users to edit source code.
</div>
<br>

## Development

Yunhai is being developed in stages, with each stage building toward the final engine.

The first phase is focused on creating a complete base game with the fundamental systems that a game would need, such as player movement, collision, rendering, maps, objects, and other core functionality. This initial game will serve as the foundation and testing ground for Yunhai's future engine systems.

Once these systems are stable and properly separated, they can gradually be transformed into reusable engine functionality. The goal is for the finished engine to allow developers to modify existing systems, create new content, and eventually build entirely new games without having to directly modify the engine's source code.

This approach allows Yunhai to grow naturally from a functional game into a flexible game development environment.

<br>

Planned systems include:

- Game objects
- Data-driven properties
- Built-in level/map editor
- Game configuration tools
- Non-scripting workflow

<br>

## Code Organisation

Yunhai is organised into separate systems to keep the project easy to navigate and understand for both beginners and experienced developers.

The project is structured around keeping individual systems separated from one another, making it easier to locate, modify, and expand specific parts of the engine without unnecessarily affecting unrelated systems.

Another goal is to make the code itself easy to understand. Comments are used to explain important logic and concepts where necessary, while avoiding excessive comments that can make the code harder to read.

As Yunhai grows, maintaining a clear and understandable codebase will remain an important part of its development.

<br>

## License

Yunhai Engine is licensed under the Mozilla Public License 2.0.
