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

            glm::vec2 pre_ramp_vertices[4]
            {
                {int(0 * window_width), int(0 * window_height)},
                {int(0.1f * window_width), int(0 * window_height)},
                {int(0.1f * window_width), int(0.4f * window_height)},
                {int(0 * window_width), int(0.4f * window_height)}
            };

            T2DPhysicCollider pre_ramp_collider(
                                                first_geometry,
                                                glm::vec2{ 0,0 },
                                                pre_ramp_vertices,
                                                sf::Color(126, 190, 255),
                                                200.f,
                                                0.2f,
                                                0.f
                                                );

            T2DPhysicCollider ramp_phase_1(
                                            first_geometry,
                                            glm::vec2{ 0,0 },
                                            glm::vec2{ int(0.1f * window_width), int(0.4f * window_height) },
                                            glm::vec2{ int(0.2f * window_width), int(0.2f * window_height) },
                                            sf::Color(126, 190, 255),
                                            200.f,
                                            0.2f,
                                            0.f
                                            );

            T2DPhysicCollider ramp_phase_2(
                                            first_geometry,
                                            glm::vec2{ 0,0 },
                                            glm::vec2{ int(0.2f * window_width), int(0.2f * window_height) },
                                            glm::vec2{ int(0.3f * window_width), int(0.17f * window_height) },
                                            sf::Color(126, 190, 255),
                                            200.f,
                                            0.2f,
                                            0.f
                                            );

            T2DPhysicCollider ramp_phase_3(
                                            first_geometry,
                                            glm::vec2{ 0,0 },
                                            glm::vec2{ int(0.3f * window_width), int(0.17f * window_height) },
                                            glm::vec2{ int(0.35f * window_width), int(0.2f * window_height) },
                                            sf::Color(126, 190, 255),
                                            200.f,
                                            0.2f,
                                            0.f
                                            );


        }
        
        // POST HOLE RAMP
        {
            glm::vec2 post_ramp_vertices[4]
            {
                {int(0.35f * window_width), int(0 * window_height)},
                {int(0.4f * window_width), int(0 * window_height)},
                {int(0.4f * window_width), int(0.2f * window_height)},
                {int(0.35f * window_width), int(0.2f * window_height)}
            };

            T2DPhysicCollider post_ramp_collider (
                                                    first_geometry,
                                                    glm::vec2{ 0,0 },
                                                    post_ramp_vertices,
                                                    sf::Color (126, 190, 255),
                                                    200.f,
                                                    0.2f,
                                                    0.f
                                                );

            glm::vec2 second_ramp_vertices[4]
            {
                {int (0.55f * window_width), int (0    * window_height)},
                {int (0.85f * window_width), int (0    * window_height)},
                {int (0.85f * window_width), int (0.2f * window_height)},
                {int (0.55f * window_width), int (0.1f * window_height)}
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
                {int (0.25f * window_width), int (0.8f    * window_height)},
                {int (0.4f  * window_width), int (0.8f    * window_height)},
                {int (0.4f  * window_width), int (0.9f * window_height)},
                {int (0.25f * window_width), int (0.9f * window_height)}
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

        first_geometry.get_body()->SetUserData(this);
        bodies.push_back(new T2DPhysicBody(first_geometry));
        
    }

    virtual void update(float delta) {};

    virtual void on_collision_begin(Entity& other) {};

    virtual void on_collision_end(Entity& other) {};
};