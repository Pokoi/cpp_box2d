/*
 * File: T2DPhysicBody.cpp
 * File Created: 8th January 2020
 * 末末末末末末末末末末末末
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * 末末末末末末末末末末末末
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

#include <T2DPhysicBody.hpp>
#include <T2DPhysicWorld.hpp>

/**
@brief Creates a T2DPhysicBody instance
@param world A reference to the physic world this entity belongs to
@param type The type of body
@param offset The pivot coordinates of the body
*/
T2DPhysicBody::T2DPhysicBody(class T2DPhysicWorld& world, body_types type, glm::vec2 offset)
{     

    if (type == body_types::DYNAMIC) body_definition.type = b2_dynamicBody;    
    else if (type == body_types::STATIC) body_definition.type = b2_staticBody;
    else if (type == body_types::KINEMATIC  ) body_definition.type = b2_kinematicBody;
    
    body_definition.position.Set(offset.x, offset.y);

    body = world.create_body(body_definition);    
    
    activate();
}

