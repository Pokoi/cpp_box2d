/*
 * File: T2DPhysicEvents.hpp
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

#include <Box2D/Box2D.h>
#include <Entity.h>


class T2DPhysicEvents : public b2ContactListener
{
public:

    /**
    @brief Creates a T2DPhysicEvents instance
    */
    T2DPhysicEvents() {}

    /**
    @brief Listener to begin contact events
    @param contact The contact of the collision    
    */
    void BeginContact(b2Contact* contact) override
    {
        Entity* entity_1 = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
        Entity* entity_2 = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

        if (entity_1 != nullptr && entity_2 != nullptr && entity_1 != entity_2)
        {
            entity_1->on_collision_begin(*entity_2);
            entity_2->on_collision_begin(*entity_1);
        }
    }

    /**
    @brief Listener to end contact events
    @param contact The contact of the collision
    */
    void EndContact(b2Contact* contact) override
    {
        Entity* entity_1 = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
        Entity* entity_2 = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

        if (entity_1 != nullptr && entity_2 != nullptr && entity_1 != entity_2)
        {
            entity_1->on_collision_end(*entity_2);
            entity_2->on_collision_end(*entity_1);
        }
    }


};