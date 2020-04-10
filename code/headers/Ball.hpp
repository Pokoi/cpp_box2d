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

#include <T2DPhysicWorld.hpp>
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"


class Ball : public Entity
{
    T2DPhysicBody sphere;

public:

    Ball(glm::vec2 position, T2DPhysicWorld & world) : sphere{ world, T2DPhysicBody::body_types::DYNAMIC, position }
    {
        this->name = "ball";

        T2DPhysicCollider collider(sphere, glm::vec2{ 0,0 }, 7.f, sf::Color::Green, 0.5f, 0.2f, 0.4f);

        sphere.get_body()->SetUserData(this);        
        bodies.push_back(new T2DPhysicBody(sphere));
    }

    virtual void update(float delta) {};
    virtual void on_collision_begin(Entity& other) {};
    virtual void on_collision_end(Entity& other) {};

};

