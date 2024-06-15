#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Tile.hpp"
#include "img/img.hpp"
#include "Monster.hpp"
#include <unordered_map>
#include "Barrage.hpp"

using namespace std;

pair<TileType, img::Image> getMatchingTileTexture(TileType type);

pair<MonsterType, img::Image> getMatchingMonsterTexture(MonsterType type);

unordered_map<TileType, GLuint> setTileTextures();

unordered_map<MonsterType, GLuint> setMonsterTextures();

void drawTile(Tile &tile, GLfloat mapSize);
void drawMonster(Monster &monster, GLfloat map_size);
void drawBarrage(GLuint barrage_texture, GLfloat map_size, Node &node);
void drawLife(vector<GLuint> life, glm::vec2 global_position, GLfloat map_size);