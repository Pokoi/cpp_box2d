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

        /**
        @brief Creates a T2DPhysicBody instance
        @param world A reference to the physic world this entity belongs to
        @param type The type of body
        @param offset The pivot coordinates of the body
        */
        T2DPhysicBody(class T2DPhysicWorld & world, body_types type, glm::vec2 offset);    
        
        /**
        @brief Gets the mass of the body
        @return The mass of the body
        */
        float get_mass()    { return body->GetMass(); }

        /**
        @brief Gets if the body is dynamic type
        @return True if the body is dynamic, false otherwise
        */
        bool is_dynamic()   { return body->GetType() == b2BodyType::b2_dynamicBody;     }

        /**
        @brief Gets if the body is static type
        @return True if the body is static, false otherwise
        */
        bool is_static()    { return body->GetType() == b2BodyType::b2_staticBody;      }

        /**
        @brief Gets if the body is kinematic type
        @return True if the body is kinematic, false otherwise
        */
        bool is_kinematic() { return body->GetType() == b2BodyType::b2_kinematicBody;   }

        /**
        @brief Set the body as dynamic       
        */
        void set_dynamic()   { body->SetType(b2_dynamicBody);   }

        /**
        @brief Set the body as static
        */
        void set_static()    { body->SetType(b2_staticBody);    }

        /**
        @brief Set the body as kinematic
        */
        void set_kinematic() { body->SetType(b2_kinematicBody); }

        /**
        @brief Set the mass of the body
        @param mass The mass
        */
        void set_mass(float mass)
        {
            mass_data.mass = mass;
            body->SetMassData(&mass_data);
            body->ResetMassData();
        }

        /**
        @brief Set the position of the body
        @param new_position The position to apply
        */
        void set_position(glm::vec2 new_position)
        {
            body->SetTransform(b2Vec2{ new_position.x, new_position.y }, 0);
        }

        /**
        @brief Activate the body
        */
        void activate()
        {
            body->SetActive(true);
        }

        /**
        @brief Inactivate the body
        */
        void inactivate()
        {
            body->SetActive(false);
        }

        /**
        @brief Add a collider to the collider collection
        @param collider The given collider to add
        */
        void add_collider(T2DPhysicCollider& collider)
        {
            colliders.push_back(collider);
            body->CreateFixture(&collider.get_fixture());
        }
        
        /**
        @brief Gets the collection of colliders attached to this body
        @return The collider collection
        */
        std::list<T2DPhysicCollider>& get_colliders()
        {
            return colliders;
        }

        /**
        @brief Render the colliders attached to this body
        @param window The render window context
        */
        void render(sf::RenderWindow & window)
        {
            for (auto& collider : colliders)
            {
                collider.render(window, *this);
            }
        }

        /**
        @brief Gets a pointer to the physic body of this object
        @return A pointer to the physic body
        */
        b2Body* get_body()
        {
            return body;
        }

    };
