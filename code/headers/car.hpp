/*
 * File: car.hpp
 * File Created: 9th January 2020
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

#include "T2DPhysicWorld.hpp"
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"
#include <iostream>

#include "glm/glm.hpp"

#include "Entity.h"


class Car : public Entity
{
    
    T2DPhysicBody chassis;
    T2DPhysicBody front_wheel;
    T2DPhysicBody back_wheel;
    T2DPhysicBody trailer;

    glm::vec2 start             { 0,0 };
    glm::vec2 chassis_offset    { 0,0 };
    glm::vec2 front_wheel_offset{ 0,0 };
    glm::vec2 back_wheel_offset { 0,0 };
    glm::vec2 trailer_offset    { 0,0 };

    b2RevoluteJoint * back_wheel_motor;
    b2RevoluteJoint * front_wheel_motor;
    b2RevoluteJoint * trailer_motor;



public:

    Car(size_t window_width, size_t window_height, T2DPhysicWorld& world);
    
    void reset_position();

    virtual void update(float delta) override;
    

    virtual void on_collision_begin(Entity& other) 
    {
        if (other.get_name() == "reset")
        {
            reset_position();
        }
    };

    virtual void on_collision_end(Entity& other) {};

};