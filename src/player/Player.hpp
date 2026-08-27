#pragma once

// Player Variables

struct Player
{
	// Starting Positions
	float posX  = 2.5f;
	float posY  = 2.5f;

	float angle = 0.0f;
	float pitch = 0.0f;
	float mouseSensitivity = 0.003f;

	float speed = 0.003f;

	// Calling the functions from Player.cpp
	void movement_update();
	void mouse_update(float mouseDeltaX, float mouseDeltaY);
};
