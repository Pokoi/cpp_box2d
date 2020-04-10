/*
 * File: Geometry.hpp
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
#include <T2DPhysicWorld.hpp>
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"

class Geometry : public Entity
{

public:

    Geometry(size_t window_width, size_t window_height, T2DPhysicWorld& world)
    {
        this->name = "geometry";

        T2DPhysicBody first_geometry(world, T2DPhysicBody::body_types::STATIC, { 0,0 });

        // RAMP
        {

            glm::vec2 vertices[4]
            {
                {int(0     * window_width), int(0     * window_height)},
                {int(0.09f * window_width), int(0     * window_height)},
                {int(0.09f * window_width), int(0.29f * window_height)},
                {int(0     * window_width), int(0.29f * window_height)}
            };

            T2DPhysicCollider pre_ramp_collider(
                                                first_geometry,
                                                glm::vec2{ 0,0 },
                                                vertices,
                                                sf::Color(126, 190, 255),
                                                200.f,
                                                0.2f,
                                                0.f
                                                );

            
            vertices[0] = { int(0.09f * window_width), int(0 * window_height) };
            vertices[1] = { int(0.12f * window_width), int(0 * window_height) };
            vertices[2] = { int(0.12f * window_width), int(0.19f * window_height) };
            vertices[3] = { int(0.09f  * window_width),  int(0.29f * window_height)};
            

            T2DPhysicCollider ramp_phase_1_collider(
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color(126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                    );

            vertices[0] = { int(0.12f * window_width), int(0 * window_height) };
            vertices[1] = { int(0.15f * window_width), int(0 * window_height) };
            vertices[2] = { int(0.15f * window_width), int(0.13f * window_height) };
            vertices[3] = { int(0.12f * window_width),  int(0.19f * window_height)};
            

            T2DPhysicCollider ramp_phase_2_collider(
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color(126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                    );

            vertices[0] = { int(0.15f * window_width), int(0 * window_height) };
            vertices[1] = { int(0.19f * window_width), int(0 * window_height) };
            vertices[2] = { int(0.19f * window_width), int(0.08f * window_height) };
            vertices[3] = { int(0.15f * window_width),  int(0.13f * window_height)};
            

            T2DPhysicCollider ramp_phase_3_collider(
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color(126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                    );

            vertices[0] = { int(0.19f * window_width), int(0 * window_height) };
            vertices[1] = { int(0.36f * window_width), int(0 * window_height) };
            vertices[2] = { int(0.36f * window_width), int(0.09f * window_height) };
            vertices[3] = { int(0.19f * window_width),  int(0.08f * window_height)};
            

            T2DPhysicCollider ramp_phase_4_collider(
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color(126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                    );

            vertices[0] = { int(0.36f * window_width), int(0 * window_height) };
            vertices[1] = { int(0.44f * window_width), int(0 * window_height) };
            vertices[2] = { int(0.44f * window_width), int(0.14f * window_height) };
            vertices[3] = { int(0.36f * window_width),  int(0.09f * window_height)};
            

            T2DPhysicCollider ramp_phase_5_collider(
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color(126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                    );

        }
        
        // POST HOLE RAMP
        {
            glm::vec2 second_ramp_vertices[4]
            {
                {int (0.62f * window_width), int (0    * window_height)},
                {int (0.87f * window_width), int (0    * window_height)},
                {int (0.87f * window_width), int (0.1f * window_height)},
                {int (0.62f * window_width), int (0.05f * window_height)}
            };
        
        
            T2DPhysicCollider second_ramp_collider (
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    second_ramp_vertices,
                                                    sf::Color (126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                );
        }

        // FLY PLATFORM
        {
            glm::vec2 fly_platform_vertices[4]
            {
                {int (0.33f * window_width), int (0.60f * window_height)},
                {int (0.44f * window_width), int (0.60f * window_height)},
                {int (0.44f * window_width), int (0.65f * window_height)},
                {int (0.33f * window_width), int (0.65f * window_height)}
            };
        
        
            T2DPhysicCollider second_ramp_collider (
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    fly_platform_vertices,
                                                    sf::Color (126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                );
        }

        // FLY PLATFORM RECEIVE ZONE
        {
            glm::vec2 vertices[4]
            {
                {int (0.26f * window_width), int (0.39f * window_height)},
                {int (0.33f * window_width), int (0.60f * window_height)},
                {int (0.33f * window_width), int (0.65f * window_height)},
                {int (0.25f * window_width), int (0.41f * window_height)}
            };
        
        
            T2DPhysicCollider rigth_limit       (
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color (126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                );

            vertices[0] = { int(0.18f * window_width), int(0.62 * window_height) };
            vertices[1] = { int(0.26f * window_width), int(0.39f * window_height) };
            vertices[2] = { int(0.27f * window_width), int(0.41f * window_height) };
            vertices[3] = { int(0.19f * window_width),  int(0.65f * window_height) };

        
            T2DPhysicCollider left_limit       (
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    vertices,
                                                    sf::Color (126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                );
        }

        //WALLS
        {            
            T2DPhysicCollider left_wall(first_geometry, glm::vec2{ 0,0 }, glm::vec2{ 0,0 }, glm::vec2{ 0, window_height }, sf::Color::Transparent, 1.f, 0.f, 0.f);
            T2DPhysicCollider rigth_wall(first_geometry, glm::vec2{ 0,0 }, glm::vec2{ window_width,0 }, glm::vec2{ window_width, window_height }, sf::Color::Transparent, 1.f, 0.f, 0.f);
        }

        first_geometry.get_body()->SetUserData(this);
        bodies.push_back(new T2DPhysicBody(first_geometry));
        
    }

    virtual void update(float delta) {};

    virtual void on_collision_begin(Entity& other) {};

    virtual void on_collision_end(Entity& other) {};
};