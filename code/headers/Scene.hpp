/*
 * File: Scene.hpp
 * File Created: 9th April 2020
 * ––––––––––––––––––––––––
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * ––––––––––––––––––––––––
 * MIT License
 *
 * Copyright (c) 2020 Pokoidev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <Entity.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "T2DPhysicWorld.hpp"
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"

#include "car.hpp"
#include "Geometry.hpp"
#include "InteractuableGeometry.hpp"
#include "Tower.hpp"
#include "Platform.hpp"
#include "Ball.hpp"

#include <glm/glm.hpp>

class Scene
{
    const size_t BALLS_COUNT = 6;

    std::vector<Entity*> entities;

    T2DPhysicWorld world;


public:

    /**
    @brief Creates the scene and all its entities
    @param window_width The width of the render window
    @param window_height The height of the render window
    */
    Scene(size_t window_width, size_t window_height) : world{ glm::vec2{ 0.f,-10.f } }
    {      

        Car      * car              = new Car(window_width, window_height, world);
        Geometry * solid_geometry   = new Geometry(window_width, window_height, world);
        Tower    * balls_tower      = new Tower(window_width, window_height, world);
        Platform * platform         = new Platform(window_width, window_height, world);
        InteractuableGeometry * receive_platform = new InteractuableGeometry(window_width, window_height, world, *balls_tower, *platform);

        glm::vec2 balls_spawn = balls_tower->get_position();

        for (size_t i = 0; i < BALLS_COUNT; i++)
        {
            Ball* ball = new Ball({ balls_spawn.x, balls_spawn.y + 100 }, world);
            entities.push_back(ball);
        }

        entities.push_back(car);
        entities.push_back(solid_geometry);
        entities.push_back(balls_tower);
        entities.push_back(platform);
        entities.push_back(receive_platform);
    }

    /**
    @brief Updates all the scene entities
    @param delta The seconds between frames
    */
    void update(float delta)
    {
        world.get_world()->Step(delta, 8, 4);

        for (auto& entity : entities)
        {
            entity->update(delta);
        }
    }

    /**
    @brief Render all the scene entities
    @param window The render window context
    */
    void render(sf::RenderWindow& window)
    {
        for (auto& entity : entities)
        {
            entity->render(window);
        }
    }

    /**
    @brief Free memory    
    */
    ~Scene()
    {
        for (auto& entity : entities)
        {
            delete entity;
        }
    }

};