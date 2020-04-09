/*
 * File: T2DPhysicBody.hpp
 * File Created: 31st March 2020
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

#include <T2DPhysicCollider.hpp>  // For the collider list

#include <Box2D/Box2D.h>

#include <list>
#include <memory>


    class T2DPhysicBody 
    {
    public:
        enum body_types {STATIC, DYNAMIC, KINEMATIC};

    private:
        b2Body * body;
        b2BodyDef body_definition;
        b2MassData mass_data;

        std::list <T2DPhysicCollider> colliders;

    public:
        T2DPhysicBody(class T2DPhysicWorld & world, body_types type, glm::vec2 offset);    
         
        float get_mass()    { return body->GetMass(); }

        bool is_dynamic()   { return body->GetType() == b2BodyType::b2_dynamicBody;     }

        bool is_static()    { return body->GetType() == b2BodyType::b2_staticBody;      }

        bool is_kinematic() { return body->GetType() == b2BodyType::b2_kinematicBody;   }

        void set_dynamic()   { body->SetType(b2_dynamicBody);   }

        void set_static()    { body->SetType(b2_staticBody);    }

        void set_kinematic() { body->SetType(b2_kinematicBody); }

        void set_mass(float mass)
        {
            mass_data.mass = mass;
            body->SetMassData(&mass_data);
            body->ResetMassData();
        }

        void set_position(glm::vec2 new_position)
        {
            body->SetTransform(b2Vec2{ new_position.x, new_position.y }, 0);
        }

        void activate()
        {
            body->SetActive(true);
        }

        void inactivate()
        {
            body->SetActive(false);
        }
        void add_collider(T2DPhysicCollider& collider)
        {
            colliders.push_back(collider);
            body->CreateFixture(&collider.get_fixture());
        }
        
        std::list<T2DPhysicCollider>& get_colliders()
        {
            return colliders;
        }

        void render(sf::RenderWindow & window)
        {
            for (auto& collider : colliders)
            {
                collider.render(window, *this);
            }
        }

        b2Body* get_body()
        {
            return body;
        }

    };
