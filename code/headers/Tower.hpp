/*
 * File: Tower.hpp
 * File Created: 10th April 2020
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

#include "Entity.h"
#include "glm/glm.hpp"

#include <T2DPhysicWorld.hpp>
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"


class Tower : public Entity
{

    glm::vec2 initial_position;

public:

    Tower(size_t window_width, size_t window_height, T2DPhysicWorld& world)
    {
        this->name = "balls tower";

        initial_position.x = int(0.83f * window_width);
        initial_position.y = int(0.40f * window_height);

        T2DPhysicBody tower(world, T2DPhysicBody::body_types::KINEMATIC, initial_position);
    
        //GEOMETRY        
        {
            glm::vec2 vertices[4]
            {
                {initial_position.x - int(0.83f * window_width), int(0.40f * window_height) - initial_position.y},
                {initial_position.x - int(0.91f * window_width), int(0.52f * window_height) - initial_position.y},
                {initial_position.x - int(0.90f * window_width), int(0.55f * window_height) - initial_position.y},
                {initial_position.x - int(0.82f * window_width), int(0.42f * window_height) - initial_position.y}
            };


            T2DPhysicCollider rigth_limit(
                                            tower,
                                            glm::vec2{ 0,0 },
                                            vertices,
                                            sf::Color(126, 190, 255),
                                            200.f,
                                            0.2f,
                                            0.f
                                            );

            vertices[0] = { initial_position.x - int(0.75f * window_width), int(0.52f * window_height) - initial_position.y };
            vertices[1] = { initial_position.x - int(0.83f * window_width), int(0.40f * window_height) - initial_position.y };
            vertices[2] = { initial_position.x - int(0.84f * window_width), int(0.42f * window_height) - initial_position.y };
            vertices[3] = { initial_position.x - int(0.76f * window_width), int(0.55f * window_height) - initial_position.y };


            T2DPhysicCollider left_limit(
                                            tower,
                                            glm::vec2{ 0,0 },
                                            vertices,
                                            sf::Color(126, 190, 255),
                                            200.f,
                                            0.2f,
                                            0.f
                                            );
        }

        tower.get_body()->SetUserData(this);
        bodies.push_back(new T2DPhysicBody(tower));

    }


    void release_balls() 
    {
        bodies[0]->get_body()->SetAngularVelocity(-0.75f);
    }

    void stop()
    {
        bodies[0]->get_body()->SetAngularVelocity(0);
    }

    glm::vec2 get_position()
    {
        return initial_position;
    }

    virtual void update(float delta) 
    {
        if (glm::abs(bodies[0]->get_body()->GetAngle()) > 0.78f)
        {
            bodies[0]->get_body()->SetAngularVelocity(0);
        }
    };

    virtual void on_collision_begin(Entity& other) {};

    virtual void on_collision_end(Entity& other) {};

};