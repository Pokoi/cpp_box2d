/*
 * File: T2DPhysicWorld.hpp
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

#include <glm/glm.hpp> 
#include <Box2D/Box2D.h>
#include <T2DPhysicBody.hpp>
#include <T2DPhysicEvents.hpp>
#include <memory>


class T2DPhysicWorld
{

    b2World * world = nullptr;
    T2DPhysicEvents events_listener;

public:

    /**
    @brief Creates a T2DPhysicWorld instance
    @param gravity The gravity of the physic world
    */
    T2DPhysicWorld(glm::vec2 gravity);
    
    /**
    @brief Releases the memory    
    */
    ~T2DPhysicWorld()
    {
        delete world;
    }

    /**
    @brief Creates a physic body object
    @param body_def A reference to the body definition
    @return A pointer to the created physic body 
    */
    b2Body * create_body(b2BodyDef & body_def);

    /**
    @brief Gets a pointer to the physic world object    
    @return A pointer to the physic world object
    */
    b2World* get_world() { return world; }

    /**
    @brief Creates a joint between two bodies
    @param joint_def A reference to the joint definition
    @return A pointer to the created joint
    */
    b2Joint* create_joint(b2JointDef& joint_def)
    {
        return world->CreateJoint(&joint_def);
    }
};
