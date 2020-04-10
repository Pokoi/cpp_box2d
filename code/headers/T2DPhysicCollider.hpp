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

    /**
    @brief Creates a circular collider
    @param body A reference to its owner body
    @param local_position The local pivot coordinates
    @param radius The radius of the collider
    @param color The color to render
    @param density The density of the collider
    @param friction The friction of the collider
    @param restitution The restitution of the collider
    */
    T2DPhysicCollider   (
                            class T2DPhysicBody & body, 
                            glm::vec2 local_position, 
                            float radius,
                            sf::Color color,
                            float density       = 1.f,
                            float friction      = 0.f,
                            float restitution   = 0.f
                        );

    /**
    @brief Creates a box collider
    @param body A reference to its owner body
    @param local_position The local pivot coordinates
    @param vertices The vertices coordinates of the box
    @param color The color to render
    @param density The density of the collider
    @param friction The friction of the collider
    @param restitution The restitution of the collider
    */
    T2DPhysicCollider   (
                            class T2DPhysicBody & body, 
                            glm::vec2 local_position,
                            glm::vec2 vertices[4],
                            sf::Color color,
                            float density       = 1.f,
                            float friction      = 0.f,
                            float restitution   = 0.f
                        );

    /**
    @brief Creates a edge collider
    @param body A reference to its owner body
    @param local_position The local pivot coordinates
    @param origin The origin coordinates of the edge
    @param end The origin coordinates of the edge
    @param color The color to render
    @param density The density of the collider
    @param friction The friction of the collider
    @param restitution The restitution of the collider
    */
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
    /**
    @brief Set the density of the collider
    @param value The density to apply
    */
    void set_density(float value)
    {
        fixture->density = value;
    }

    /**
    @brief Set the friction of the collider
    @param value The friction to apply
    */
    void set_friction(float value)
    {
        fixture->friction = value;
    }

    /**
    @brief Set the restitution of the collider
    @param value The restitution to apply
    */
    void set_restitution(float value)
    {
        fixture->restitution = value;
    }

    /**
    @brief Get the density of the collider
    @return The density of the collider
    */
    float get_density()
    {
        return fixture->density;
    }

    /**
    @brief Get the friction of the collider
    @return The friction of the collider
    */
    float get_friction()
    {
        return fixture->friction;
    }

    /**
    @brief Get the restitution of the collider
    @return The restitution of the collider
    */
    float get_restitution()
    {
        return fixture->restitution;
    }

    /**
    @brief Get a reference to the fixture of the collider
    @return The fixture of the collider
    */
    b2FixtureDef & get_fixture()
    {
        return *fixture;
    }

    /**
    @brief Render the collider
    @param window The render window context
    @param body The T2DPhysicBody owner of this collider
    */
    void render(sf::RenderWindow & window, class T2DPhysicBody body);

};
