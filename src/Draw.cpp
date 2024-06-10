#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Draw.hpp"
#include "utils.hpp"
#include "img/img.hpp"
#include <unordered_map>
#include "Monster.hpp"
#include "Tile.hpp"
#include <GLHelpers.hpp>

using namespace std;

/* --------------- RECUPERATION DES TEXTURES de TILES ET DE MONSTRES DANS UN TABLEAU D'ID -------------------- */

pair<TileType, img::Image> getMatchingTileTexture(TileType type)
{
    switch (type)
    {
    case TileType::Curve:
        return {TileType::Curve, img::Image{img::load(make_absolute_path("images/curve.png", true), 4, false)}};
    case TileType::FourWays:
        return {TileType::FourWays, img::Image{img::load(make_absolute_path("images/four_ways.png", true), 4, false)}};
    case TileType::ThreeWays:
        return {TileType::ThreeWays, img::Image{img::load(make_absolute_path("images/three_ways.png", true), 4, false)}};
    case TileType::Straight:
        return {TileType::Straight, img::Image{img::load(make_absolute_path("images/straight.png", true), 4, false)}};
    }
    return {TileType::Grass, img::Image{img::load(make_absolute_path("images/grass.png", true), 4, false)}};
}

pair<MonsterType, img::Image> getMatchingMonsterTexture(MonsterType type)
{
    switch (type)
    {
    case MonsterType::Meduse:
        return {MonsterType::Meduse, img::Image{img::load(make_absolute_path("images/meduse.png", true), 4, false)}};
    case MonsterType::Orque:
        return {MonsterType::Orque, img::Image{img::load(make_absolute_path("images/orque.png", true), 4, false)}};
    case MonsterType::Poseidon:
        return {MonsterType::Poseidon, img::Image{img::load(make_absolute_path("images/poseidon.png", true), 4, false)}};
    case MonsterType::Requin:
        return {MonsterType::Requin, img::Image{img::load(make_absolute_path("images/requin.png", true), 4, false)}};
    }
}

// CHARGEMENT DES TEXTURES DES DIFFERENTES TILES ET MONSTRES

unordered_map<TileType, GLuint> setTileTextures()
{

    unordered_map<TileType, GLuint> tile_textures{};
    for (int i{0}; i < 5; i++)
    {
        tile_textures.insert({static_cast<TileType>(i), loadTexture(getMatchingTileTexture(static_cast<TileType>(i)).second)});
    }
    return tile_textures;
}

unordered_map<MonsterType, GLuint> setMonsterTextures()
{
    unordered_map<MonsterType, GLuint> monster_textures{};
    for (int i{0}; i < 4; i++)
    {
        monster_textures.insert({static_cast<MonsterType>(i), loadTexture(getMatchingMonsterTexture(static_cast<MonsterType>(i)).second)});
    }
    return monster_textures;
}

void drawTile(Tile &tile, GLfloat mapSize)
{
    float x = glNormalize(tile.x, mapSize);
    float y = glNormalize(tile.y, mapSize);
    float size = 2.0f / mapSize;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tile.texture);
    glTranslatef(x + size / 2, y + size / 2, 0.0f);
    glRotatef(tile.rotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(-(x + size / 2), -(y + size / 2), 0.0f);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + size, y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + size, y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawMonster(Monster &monster)
{
}