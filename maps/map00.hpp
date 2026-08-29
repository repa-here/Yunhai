#pragma once

// MAP TILE TYPES

// 0 = Empty
// 1 = Wall
// 2 = Door ( FUTURE )
// 3 = GeneralObject

// Map 0 stands for testing map.
// Its purpose is to experiment with new additions and updates without breaking the main maps.
constexpr int map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,1,0,0,1,1,1,0,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};
