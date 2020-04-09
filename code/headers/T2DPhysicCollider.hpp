/*
 * File: T2DPhysicCollider.hpp
 * File Created: 8th April 2020
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

#include <memory>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

class T2DPhysicCollider
{
    enum collider_types { CIRCULAR, POLYGON, EDGE };
    collider_types type;

    std::shared_ptr<b2FixtureDef> fixture = nullptr;
    sf::Color render_color;
    
    struct
    {      
        b2CircleShape   circular_shape;
        b2PolygonShape  polygon_shape;
        b2EdgeShape     edge_shape;
    } shape;


public:

    T2DPhysicCollider   (
                            class T2DPhysicBody & body, 
                            glm::vec2 local_position, 
                            float radius,
                            sf::Color color,
                            float density       = 1.f,
                            float friction      = 0.f,
                            float restitution   = 0.f
                        );

    T2DPhysicCollider   (
                            class T2DPhysicBody & body, 
                            glm::vec2 local_position,
                            glm::vec2 vertices[4],
                            sf::Color color,
                            float density       = 1.f,
                            float friction      = 0.f,
                            float restitution   = 0.f
                        );

    T2DPhysicCollider   (
                            class T2DPhysicBody & body, 
                            glm::vec2 local_position, 
                            glm::vec2 origin, 
                            glm::vec2 end,
                            sf::Color color,
                            float density       = 1.f, 
                            float friction      = 0.f,
                            float restitution   = 0.f
                        );    

    void set_density(float value)
    {
        fixture->density = value;
    }

    void set_friction(float value)
    {
        fixture->friction = value;
    }

    void set_restitution(float value)
    {
        fixture->restitution = value;
    }

    float get_density()
    {
        return fixture->density;
    }

    float get_friction()
    {
        return fixture->friction;
    }

    float get_restitution()
    {
        return fixture->restitution;
    }

    b2FixtureDef & get_fixture()
    {
        return *fixture;
    }

    void render(sf::RenderWindow & window, class T2DPhysicBody body);

};
