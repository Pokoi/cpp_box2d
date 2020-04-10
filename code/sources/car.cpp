/*
 * File: car.cpp
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


#include "car.hpp"

Car::Car(size_t window_width, size_t window_height, T2DPhysicWorld& world)
    :
    chassis     { world, T2DPhysicBody::body_types::DYNAMIC, { int(0.07f * window_width * 0.5f ), int(0.03f * window_height * 0.5f) } },
    back_wheel  { world, T2DPhysicBody::body_types::DYNAMIC, { int(0.07f * window_width * 0.25f), 0} },
    front_wheel { world, T2DPhysicBody::body_types::DYNAMIC, { int(0.07f * window_width * 0.75f), 0} },
    trailer     { world, T2DPhysicBody::body_types::DYNAMIC, { int(0.07f * window_width * 0.5f ), int(0.06f * window_height)} }
{
    this->name = "car";
    glm::vec2 vertices[4];       
    
    start = { int(0.01f * window_width), int(0.31f * window_height) };

    // CHASSIS
    vertices[0] = { int(-0.07f * 0.5f * window_width), int(-0.03f * window_height * 0.5f) };
    vertices[1] = { int(0.07f * 0.5f * window_width), int(-0.03f * window_height * 0.5f) };
    vertices[2] = { int(0.07f * 0.5f * window_width), int(0.03f * window_height * 0.5f) };
    vertices[3] = { int(-0.07f * 0.5f * window_width), int(0.03f * window_height * 0.5f) };

    T2DPhysicCollider chassis_collider(chassis, glm::vec2{ 0,0 }, vertices, sf::Color::Magenta, 1.f, 0.f, 0.f);

    chassis.get_body()->SetUserData(this);
    chassis_offset = { chassis.get_body()->GetPosition().x, chassis.get_body()->GetPosition().y };
    bodies.push_back(new T2DPhysicBody(chassis));

    // BACK WHEEL
    T2DPhysicCollider back_wheel_collider(back_wheel, glm::vec2{ 0,0 }, 0.02f * window_height, sf::Color::Magenta, 10.f, 0.2f, 0.2f);
    
    back_wheel.get_body()->SetUserData(this);
    back_wheel_offset = { back_wheel.get_body()->GetPosition().x, back_wheel.get_body()->GetPosition().y };
    bodies.push_back(new T2DPhysicBody(back_wheel));

    b2RevoluteJointDef back_wheel_joint;
    back_wheel_joint.bodyA = chassis.get_body();
    back_wheel_joint.bodyB = back_wheel.get_body();
    back_wheel_joint.collideConnected = false;
    back_wheel_joint.localAnchorA.Set(-20, -10);
    back_wheel_joint.localAnchorB.Set(0, 0);
    back_wheel_joint.enableMotor = true;
    back_wheel_joint.maxMotorTorque = 100000;
    back_wheel_joint.referenceAngle = 0;

   back_wheel_motor = dynamic_cast<b2RevoluteJoint*>(world.create_joint(back_wheel_joint));


    // FRONT WHEEL
    T2DPhysicCollider front_wheel_collider(front_wheel, glm::vec2{ 0,0 }, 0.02f * window_height, sf::Color::Magenta, 10.f, 0.2f, 0.2f);

    front_wheel.get_body()->SetUserData(this);
    front_wheel_offset = { front_wheel.get_body()->GetPosition().x, front_wheel.get_body()->GetPosition().y };
    bodies.push_back(new T2DPhysicBody(front_wheel));

    b2RevoluteJointDef front_wheel_joint;
    front_wheel_joint.bodyA = chassis.get_body();
    front_wheel_joint.bodyB = front_wheel.get_body();
    front_wheel_joint.collideConnected = false;
    front_wheel_joint.localAnchorA.Set(20, -10);
    front_wheel_joint.localAnchorB.Set(0, 0);
    front_wheel_joint.enableMotor = true;
    front_wheel_joint.maxMotorTorque = 100000;
    front_wheel_joint.referenceAngle = 0;

    front_wheel_motor = dynamic_cast<b2RevoluteJoint*>(world.create_joint(front_wheel_joint));

    // TRAILER
    vertices[0] = { int(-0.07f * 0.5f * window_width), int(-0.034f * window_height) };
    vertices[1] = { int(0.07f * 0.5f * window_width), int(-0.034f * window_height) };
    vertices[2] = { int(0.07f * 0.5f * window_width), int(-0.03f * window_height) };
    vertices[3] = { int(-0.07f * 0.5f * window_width), int(-0.03f * window_height) };

    T2DPhysicCollider trailer_base_collider(trailer, { 0,0 }, vertices, sf::Color::Magenta, 1.f, 0.f, 0.f);

    vertices[0] = { int(-0.07f * 0.5f * window_width), int(-0.034f * window_height) };
    vertices[1] = { int(-0.066f * 0.5f * window_width), int(-0.034f * window_height) };
    vertices[2] = { int(-0.066f * 0.5f * window_width), int(0.03f * window_height) };
    vertices[3] = { int(-0.07f * 0.5f * window_width), int(0.03f * window_height) };

    T2DPhysicCollider trailer_back_wall_collider(trailer, { 0,0 }, vertices, sf::Color::Magenta, 1.f, 0.f, 0.f);

    vertices[0] = { int(0.066f * 0.5f * window_width), int(-0.034f * window_height) };
    vertices[1] = { int(0.07f * 0.5f * window_width), int(-0.034f * window_height) };
    vertices[2] = { int(0.07f * 0.5f * window_width), int(0.03f * window_height) };
    vertices[3] = { int(0.066f * 0.5f * window_width), int(0.03f * window_height) };

    T2DPhysicCollider trailer_front_wall_collider(trailer, { 0,0 }, vertices, sf::Color::Magenta, 1.f, 0.f, 0.f);

    trailer.get_body()->SetUserData(this);
    trailer_offset = { trailer.get_body()->GetPosition().x, trailer.get_body()->GetPosition().y };
    bodies.push_back(new T2DPhysicBody(trailer));

    b2RevoluteJointDef trailer_joint;
    trailer_joint.bodyA = chassis.get_body();
    trailer_joint.bodyB = trailer.get_body();
    trailer_joint.collideConnected = false;
    trailer_joint.localAnchorA.Set(0, 20);
    trailer_joint.localAnchorB.Set(0, 0);
    trailer_joint.enableMotor = true;
    trailer_joint.maxMotorTorque = 10000000;
    trailer_joint.referenceAngle = 0;

    trailer_motor = dynamic_cast<b2RevoluteJoint*>(world.create_joint(trailer_joint));

    reset_position();
}

void Car::reset_position()
{
    chassis.set_position({ start.x + chassis_offset.x, start.y + chassis_offset.y });
    front_wheel.set_position({ start.x + front_wheel_offset.x, start.y + front_wheel_offset.y });
    back_wheel.set_position({ start.x + back_wheel_offset.x, start.y + back_wheel_offset.y });
    trailer.set_position({ start.x + trailer_offset.x, start.y + trailer_offset.y });
}

void Car::update(float delta)
{
    float speed = 9500.f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {        
        back_wheel_motor->SetMotorSpeed(speed);
        front_wheel_motor->SetMotorSpeed(speed);
    }
    else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {        
        back_wheel_motor->SetMotorSpeed(-speed);
        front_wheel_motor->SetMotorSpeed(-speed);
    }    
    else {
        
        back_wheel_motor->SetMotorSpeed(0.f);
        front_wheel_motor->SetMotorSpeed(0.f);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        trailer_motor->SetMotorSpeed(10000.f);
    }
    else
    {
        trailer_motor->SetMotorSpeed(0.f);
    }
 
}
