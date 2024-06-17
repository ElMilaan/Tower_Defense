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
        return {MonsterType::Meduse, img::Image{img::load(make_absolute_path("images/meduse.png", true), 4, true)}};
    case MonsterType::Orque:
        return {MonsterType::Orque, img::Image{img::load(make_absolute_path("images/orque.png", true), 4, true)}};
    case MonsterType::Poseidon:
        return {MonsterType::Poseidon, img::Image{img::load(make_absolute_path("images/poseidon.png", true), 4, true)}};
    case MonsterType::Requin:
        return {MonsterType::Requin, img::Image{img::load(make_absolute_path("images/requin.png", true), 4, true)}};
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

// unordered_map<MonsterType, GLuint> setBarrageTextures()
// {
//     unordered_map<MonsterType, GLuint> barrage_textures{};
//
//     barrage_texture.insert();
//
//     return barrage_texture;
// }

void drawTile(Tile &tile, GLfloat mapSize)
{
    glm::vec2 pos{glNormalize({tile.x, tile.y}, mapSize, true)};
    float size = 2.0f / mapSize;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tile.texture);
    glTranslatef(pos.x + size / 2, pos.y + size / 2, 0.0f);
    glRotatef(tile.rotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(-(pos.x + size / 2), -(pos.y + size / 2), 0.0f);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(pos.x, pos.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(pos.x + size, pos.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(pos.x + size, pos.y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(pos.x, pos.y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawLifeLine(glm::vec2 pos, GLfloat map_size, float life, float max_life)
{
    float size = 2.0f / map_size;

    float barWidth = size;    // La largeur de la barre de vie est la même que la taille du monstre
    float barHeight = 0.02f;  // Hauteur de la barre de vie
    float barOffsetY = 0.05f; // Offset au-dessus du monstre

    float lifeRatio = static_cast<float>(life) / max_life;
    float lifeWidth = barWidth * lifeRatio;

    // Dessiner la vie restante en vert
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(pos.x, pos.y + size + barOffsetY);
    glVertex2f(pos.x + lifeWidth, pos.y + size + barOffsetY);
    glVertex2f(pos.x + lifeWidth, pos.y + size + barOffsetY + barHeight);
    glVertex2f(pos.x, pos.y + size + barOffsetY + barHeight);
    glEnd();

    // Dessiner la vie perdue en gris
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(pos.x + lifeWidth, pos.y + size + barOffsetY);
    glVertex2f(pos.x + barWidth, pos.y + size + barOffsetY);
    glVertex2f(pos.x + barWidth, pos.y + size + barOffsetY + barHeight);
    glVertex2f(pos.x + lifeWidth, pos.y + size + barOffsetY + barHeight);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawMonster(Monster &monster, GLfloat map_size)
{
    glm::vec2 pos{glNormalize({monster.getPosition().x, monster.getPosition().y}, map_size, false)};

    float size = 2.0f / map_size;

    glTranslatef(pos.x + size / 2, pos.y + size / 2, 0.0f);
    glTranslatef(-(pos.x + size / 2), -(pos.y + size / 2), 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, monster.getTexture());

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(pos.x, pos.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(pos.x + size, pos.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(pos.x + size, pos.y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(pos.x, pos.y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    drawLifeLine(pos, map_size, monster.getHealthPoints(), monster.getMaxHealth());
}

void drawBarrage(GLuint barrage_texture, GLfloat map_size, Node &node)
{
    float mid_barrage{0.5};
    float mid_tile{0.5};
    glm::vec2 pos{glNormalize({node.getPosition().x, node.getPosition().y + mid_barrage + mid_tile}, map_size, false)};

    float size = 2.0f / map_size;

    glTranslatef(pos.x + size / 2, pos.y + size / 2, 0.0f);
    glTranslatef(-(pos.x + size / 2), -(pos.y + size / 2), 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, barrage_texture);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(pos.x, pos.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(pos.x + size, pos.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(pos.x + size, pos.y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(pos.x, pos.y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawTower(Tower t, GLfloat map_size)
{
    float mid_barrage{0.5};
    float mid_tile{0.5};
    glm::vec2 pos{glNormalize({t.getPosition().x, t.getPosition().y + mid_barrage + mid_tile}, map_size, false)};

    float size = 2.0f / map_size;

    glTranslatef(pos.x + size / 2, pos.y + size / 2, 0.0f);
    glTranslatef(-(pos.x + size / 2), -(pos.y + size / 2), 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t.getTexture());

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(pos.x, pos.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(pos.x + size, pos.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(pos.x + size, pos.y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(pos.x, pos.y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawProjectile(glm::vec2 projectile_pos, GLfloat map_size)
{
    glm::vec2 pos{glNormalize(projectile_pos, map_size, false)};

    float size = 2.0f / map_size;

    glTranslatef(pos.x + size / 2, pos.y + size / 2, 0.0f);
    glTranslatef(-(pos.x + size / 2), -(pos.y + size / 2), 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(pos.x, pos.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(pos.x + size, pos.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(pos.x + size, pos.y + size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(pos.x, pos.y + size);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawGameLife(vector<GLuint> life, glm::vec2 global_position, GLfloat map_size)
{
    float size = 2.0f / map_size;
    int gap{0};
    for (GLuint heart : life)
    {
        glm::vec2 pos{glNormalize({global_position.x + gap, global_position.y + 2}, map_size, false)};

        glTranslatef(pos.x + size / 2, pos.y + size / 2, 0.0f);
        glTranslatef(-(pos.x + size / 2), -(pos.y + size / 2), 0.0f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, heart);

        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(pos.x, pos.y);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(pos.x + size, pos.y);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(pos.x + size, pos.y + size);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(pos.x, pos.y + size);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        gap++;
    }
}