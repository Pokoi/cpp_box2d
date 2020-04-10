/*
 * File: InteractuableGeometry.hpp
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
#include <Tower.hpp>
#include <T2DPhysicWorld.hpp>
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"

class InteractuableGeometry : public Entity
{

    Tower target;

public:

    InteractuableGeometry(size_t window_width, size_t window_height, T2DPhysicWorld& world, Tower& target) : target{target}
    {
        this->name = "interactuable geometry";
               

        T2DPhysicBody geometry(world, T2DPhysicBody::body_types::STATIC, { 0,0 });

        glm::vec2 pre_ramp_vertices[4]
        {
            {int(0.87f * window_width), int(0 * window_height)},
            {int(1.f   * window_width), int(0 * window_height)},
            {int(1.f   * window_width), int(0.11f * window_height)},
            {int(0.87f * window_width), int(0.1f * window_height)}
        };

        T2DPhysicCollider collider  (
                                        geometry,
                                        glm::vec2{ 0,0 },
                                        pre_ramp_vertices,
                                        sf::Color (63, 191, 63),
                                        200.f,
                                        0.2f,
                                        0.f
                                    );

        

        geometry.get_body()->SetUserData(this);
        bodies.push_back(new T2DPhysicBody(geometry));


    }

    virtual void update(float delta) {};

    virtual void on_collision_begin(Entity& other) 
    {
        if (other.get_name() == "car")
        {
            target.release_balls();
        }
    };

    virtual void on_collision_end(Entity& other)
    {
        if (other.get_name() == "car")
        {
            target.stop();
        }
    };
};
