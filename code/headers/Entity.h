/*
 * File: Entity.h
 * File Created: 9th April 2020
 * 末末末末末末末末末末末末
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * 末末末末末末末末末末末末
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

#include <SFML/Graphics.hpp>
#include <vector> 
#include <string>

#include "T2DPhysicBody.hpp"


class Entity
{
protected:
    std::string name;
    std::vector<T2DPhysicBody*> bodies;

public:     

    /**
    @brief Render of the entity
    @param window The window render context
    */
    void render(sf::RenderWindow& window)
    {
        for (auto& body : bodies)
        {
            if (body->get_body()->IsActive())
            {
                body->render(window);
            }
        }
    }
    
    /**
    @brief Updates the entity behaviour
    @param delta The seconds between frames
    */
    virtual void update(float delta)                = 0;

    /**
    @brief Event called when a collision begins
    @param other The other entity in the collision
    */
    virtual void on_collision_begin(Entity& other)  = 0;

    /**
    @brief Event called when a collision ends
    @param other The other entity in the collision
    */
    virtual void on_collision_end(Entity& other)    = 0;

    /**
    @brief Gets the name of the entity
    @return The name of the entity
    */
    std::string get_name()
    {
        return name;
    }

};