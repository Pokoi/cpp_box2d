/*
 * File: T2DPhysicCollider.cpp
 * File Created: 8th April 2020
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

#include <T2DPhysicCollider.hpp>
#include <T2DPhysicBody.hpp>


/**
@brief Creates a circular collider
@param body A reference to its owner body
@param local_position The local pivot coordinates
@param radius The radius of the collider
@param color The color to render
@param density The density of the collider
@param friction The friction of the collider
@param restitution The restitution of the collider
*/
T2DPhysicCollider::T2DPhysicCollider (
                                        class T2DPhysicBody & body, 
                                        glm::vec2 local_position,
                                        float radius,
                                        sf::Color color,
                                        float density,
                                        float friction,
                                        float restitution
                                        )
{
    render_color = color;

    fixture = std::make_shared<b2FixtureDef>();

    set_density(density);
    set_friction(density);
    set_restitution(restitution);
       
    shape.circular_shape.m_p.Set(local_position.x, local_position.y);
    shape.circular_shape.m_radius = radius;

    fixture->shape = &shape.circular_shape;
    this->type = collider_types::CIRCULAR;

    body.add_collider(*this);

}

/**
@brief Creates a box collider
@param body A reference to its owner body
@param local_position The local pivot coordinates
@param vertices The vertices coordinates of the box
@param color The color to render
@param density The density of the collider
@param friction The friction of the collider
@param restitution The restitution of the collider
*/
T2DPhysicCollider::T2DPhysicCollider (
                                        class T2DPhysicBody & body, 
                                        glm::vec2 local_position, 
                                        glm::vec2 vertices[4],
                                        sf::Color color,
                                        float density,
                                        float friction,
                                        float restitution
                                    )
{
    render_color = color;

    fixture = std::make_shared<b2FixtureDef>();

    set_density(density);
    set_friction(density);
    set_restitution(restitution);

    b2Vec2 parsed_vertices[4];
        
    parsed_vertices[0].Set(vertices[0].x, vertices[0].y);
    parsed_vertices[1].Set(vertices[1].x, vertices[1].y);
    parsed_vertices[2].Set(vertices[2].x, vertices[2].y);
    parsed_vertices[3].Set(vertices[3].x, vertices[3].y);                    

    
    shape.polygon_shape.Set(parsed_vertices, 4);    
        
    fixture->shape = &shape.polygon_shape;
    this->type = collider_types::POLYGON;

    body.add_collider(*this);

}

/**
@brief Creates a edge collider
@param body A reference to its owner body
@param local_position The local pivot coordinates
@param origin The origin coordinates of the edge
@param end The origin coordinates of the edge
@param color The color to render
@param density The density of the collider
@param friction The friction of the collider
@param restitution The restitution of the collider
*/
T2DPhysicCollider::T2DPhysicCollider (
                                        class T2DPhysicBody & body,
                                        glm::vec2 local_position,
                                        glm::vec2 origin,
                                        glm::vec2 end,
                                        sf::Color color,
                                        float density,
                                        float friction,
                                        float restitution
                                    )
{
    render_color = color;

    fixture = std::make_shared<b2FixtureDef>();

    set_density(density);
    set_friction(density);
    set_restitution(restitution);

    b2Vec2 parsed_vertices[2];

    parsed_vertices[0].Set(origin.x, origin.y);
    parsed_vertices[1].Set(end.x, end.y);     

    shape.edge_shape.Set(parsed_vertices[0], parsed_vertices[1]);

    fixture->shape = &shape.edge_shape;
    this->type = collider_types::EDGE;

    body.add_collider(*this);

}

/**
@brief Render the collider
@param window The render window context
@param body The T2DPhysicBody owner of this collider
*/
void T2DPhysicCollider::render(sf::RenderWindow& window, class T2DPhysicBody body)
{
    if (type == collider_types::CIRCULAR)
    {        

        sf::CircleShape circle;
        circle.setRadius(shape.circular_shape.m_radius);
        
        b2Vec2 center = b2Mul(body.get_body()->GetTransform(), shape.circular_shape.m_p);

        circle.setPosition({ center.x - circle.getRadius(), window.getSize().y - center.y - circle.getRadius() });
        circle.setFillColor(render_color);

        window.draw(circle);
    }

    else if (type == collider_types::POLYGON)
    {       

        sf::ConvexShape convex;
        convex.setPointCount(4);

        b2Vec2 first  = b2Mul(body.get_body()->GetTransform(), shape.polygon_shape.GetVertex(0));
        b2Vec2 second = b2Mul(body.get_body()->GetTransform(), shape.polygon_shape.GetVertex(1));
        b2Vec2 third  = b2Mul(body.get_body()->GetTransform(), shape.polygon_shape.GetVertex(2));
        b2Vec2 fourth = b2Mul(body.get_body()->GetTransform(), shape.polygon_shape.GetVertex(3));

        convex.setPoint(0, { first.x,  window.getSize().y - first.y  });
        convex.setPoint(1, { second.x, window.getSize().y - second.y });
        convex.setPoint(2, { third.x,  window.getSize().y - third.y  });
        convex.setPoint(3, { fourth.x, window.getSize().y - fourth.y });

        convex.setFillColor(render_color);
        window.draw(convex);
    }

    else if (type == collider_types::EDGE)
    {        
        
        b2Vec2 origin = b2Mul(body.get_body()->GetTransform(), shape.edge_shape.m_vertex1);
        b2Vec2 end    = b2Mul(body.get_body()->GetTransform(), shape.edge_shape.m_vertex2);
        
        sf::Vertex edge[] =
        {
            sf::Vertex(sf::Vector2f{ origin.x, window.getSize().y - origin.y}, render_color),
            sf::Vertex(sf::Vector2f{ end.x, window.getSize().y - end.y}, render_color)
        };

        window.draw(edge, 2, sf::Lines);        
    }
}

