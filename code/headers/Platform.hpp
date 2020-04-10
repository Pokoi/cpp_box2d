/*
 * File: Platform.hpp
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

#include <Entity.h>

#include <T2DPhysicWorld.hpp>
#include "T2DPhysicBody.hpp"
#include "T2DPhysicCollider.hpp"

class Platform : public Entity
{
    float max_height = 0.f;

    T2DPhysicBody body;
    glm::vec2 spawn_position;
    
    bool car_in_platform;

public:

    /**
    @brief Creates a platform instance
    @param window_width The width of the render window
    @param window_height The height of the render window
    @param world A reference to the physic world this entity belongs
    */
    Platform(size_t window_width, size_t window_height, T2DPhysicWorld& world)
        : body{
                world,
                T2DPhysicBody::body_types::KINEMATIC,
                { int(0.52f * window_width), int(-0.03f * window_height)} }
    {
        this->name = "platform";
        glm::vec2 vertices[4]
        {
            {int(-0.08f * window_width), int(-0.03 * window_height)},
            {int(0.10f  * window_width), int(-0.03 * window_height)},
            {int(0.10f  * window_width), int(0.03f * window_height)},
            {int(-0.08f * window_width), int(0.03f * window_height)}
        };

        T2DPhysicCollider collider  (
                                        body,
                                        glm::vec2{ 0,0 },
                                        vertices,
                                        sf::Color::Red,
                                        30.f,
                                        0.9f,
                                        0.f
                                    );
        max_height =   0.65f * window_height - 0.01f * window_height;

        spawn_position.x = int(0.52f * window_width);
        spawn_position.y = int(0.01f * window_height);        

        body.get_body()->SetUserData(this);
        bodies.push_back(new T2DPhysicBody(body));      

    }

    /**
    @brief Updates the entity behaviour
    @param delta The seconds between frames
    */
    virtual void update(float delta) 
    {
        if (car_in_platform == false)
        {
            if (body.get_body()->GetPosition().y > spawn_position.y)
            {            
                body.get_body()->SetLinearVelocity(b2Vec2_zero);
            }
        }
        else if (body.get_body()->GetPosition().y > max_height)
        {
            body.get_body()->SetLinearVelocity(b2Vec2_zero);
        }
    };
    
    /**
    @brief Event called when a collision begins
    @param other The other entity in the collision
    */
    virtual void on_collision_begin(Entity& other) 
    {
        if (other.get_name() == "car")
        {
            body.get_body()->SetLinearVelocity({ 0, 15.f }); 
            car_in_platform = true;
        }
    };

    /**
    @brief Event called when a collision ends
    @param other The other entity in the collision
    */
    virtual void on_collision_end(Entity& other) {};

    /**
    @brief Shows the platform    
    */
    virtual void show()
    {
        body.get_body()->SetLinearVelocity({ 0, 20.f });      
    }
};