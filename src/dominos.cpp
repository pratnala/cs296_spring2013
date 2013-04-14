/*
 * Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

#define PI 3.14159

#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
    //These represent the global left and right shifts. These shifts act on all systems in sequence of the animation until before the pulley system 
    double gright = 0.0 ;
    double gup = 50.0 ; 
    //These are the shifts for the top most system of the animation, including the slide system and the first set of dominos and pendulum
    double height = 40.0 + gup;
    double rightshift = 30.0 + gright;
    
    //Top horizontal shelf, where the dominos are kept
    {
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.25f);//The dimensions
      b2Body* spherebody;
      
      //The small circular ball kept at the end of the dominoes      
      b2CircleShape circle;
      circle.m_radius = 0.5;
      
      //The properties of the small ball
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      //density, friction and restitution
      ballfd.density = 100.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      
      b2BodyDef bd;
      //coordinates of placing the shelf
      bd.position.Set(rightshift + -31.0f, height + 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      
      //coordinates of placing the ball
      ballbd.position.Set(rightshift +-24.0f, height + 31.0f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
      
      
    }
    
    //Dominos
    {
      b2PolygonShape shape;
      //Dimensions (Half Lengths) of the dominoes
      shape.SetAsBox(0.1f, 1.0f);
      
      b2FixtureDef fd;
      fd.shape = &shape;
      //Density and friction
      fd.density = 20.0f;
      fd.friction = 0.1f;
      
      //Making 10 dominos and placing them in the world      
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  //The position of the ith domino
	  bd.position.Set(rightshift +-35.5f + 1.0f * i, 31.25f + height);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    
    
    //The slide system
    //The angle for the slides (18 degrees), PI has been defined as a macro
    double angle = PI/10;
    {
      //The second slope from the top
      b2PolygonShape shape;
      //Dimensions and angle; This is an acute angled slope. All slopes are initialized similarly
      shape.SetAsBox(10.0f, 0.25f, b2Vec2(-15.f,20.f), angle);
      
      b2BodyDef bd;
      //Coordinates
      bd.position.Set(rightshift +6.0f, 0.0f + height);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    
    {
      //The last slope from the top
      b2PolygonShape shape;
      //This is an acute angle slope
      shape.SetAsBox(10.0f, 0.25f, b2Vec2(-15.f,20.f), angle);
      
      b2BodyDef bd;
      bd.position.Set(rightshift +6.0f, -14.0f + height);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    
    {
      //The first slope from the top
      b2PolygonShape shape;
      //This is an obtuse angled slope
      shape.SetAsBox(10.0f, 0.25f, b2Vec2(-15.f,20.f), PI - angle);
      
      b2BodyDef bd;
      bd.position.Set(rightshift +1.5f, 6.8f + height);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    {
      //The Third slope from the top
      b2PolygonShape shape;
      //This is an obtuse angled slope
      shape.SetAsBox(10.0f, 0.25f, b2Vec2(-15.f,20.f), PI -angle);
      
      b2BodyDef bd;
      bd.position.Set(rightshift +1.5f, -7.0f + height);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      //The vertical boundary of the system on the right hand side
      b2PolygonShape shape;
      //The angle is a strict vertical, and dimensions are different from the horizontal sloop
      shape.SetAsBox(12.f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
      
      b2BodyDef bd;
      bd.position.Set(rightshift +21.0f, -3.0f + height);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    {
      //The vertical boundary of the system on the left hand side
      b2PolygonShape shape;
      //The angle is a strict vertical again.
      shape.SetAsBox(12.f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
      
      b2BodyDef bd;
      bd.position.Set(rightshift +-3.0f, -3.0f + height);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    
    
    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      //The small vertical bar at the bottom that acts as an anchor
      {
	b2PolygonShape shape;
	//The dimensions of the bar
	shape.SetAsBox(0.25f, 1.5f);
	
	b2BodyDef bd;
	//The coordinates
	bd.position.Set(rightshift +-36.5f, 28.0f + height);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
      
      //The small square that acts as the pendulum which knocks the dominoes off
      b2Body* b4;
      {
	b2PolygonShape shape;
	//The dimensions of the pendulum
	shape.SetAsBox(0.25f, 0.25f);
	
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	//The coordinates
	bd.position.Set(rightshift +-40.0f, 33.0f + height);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
      //The defintion of the pivot
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      //The coordinates of the pivot point
      anchor.Set(rightshift +-37.0f, 40.0f + height);
      //The exact definition of the pendulum joint
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
    
    
    
    
    
    
    //The second set of dominos
    {
      //The shifts for the second set of dominos along with the shelf
      double height = -11.0 + gup;
      double rightshift = 69.2 + gright;
      
      //Top horizontal shelf
      {//The shelf
	b2PolygonShape shape;
	//Dimenstions
	shape.SetAsBox(6.0f, 0.25f);
	b2Body* spherebody;
	//The circle which falls into the pulley
	b2CircleShape circle;
	//The radius of the circle
	circle.m_radius = 0.5;
	
	b2FixtureDef ballfd;
	ballfd.shape = &circle;
	//Properties of the circle
	ballfd.density = 20.0f;
	ballfd.friction = 0.0f;
	ballfd.restitution = 0.0f;
	
	b2BodyDef bd;
	//Location of the shelf
	bd.position.Set(rightshift + -30.0f, height + 30.0f);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shape, 0.0f);
	
	//The ball 
	b2BodyDef ballbd;
	ballbd.type = b2_dynamicBody;
	//Location of the ball
	ballbd.position.Set(rightshift +-24.0f, height + 31.0f);
	spherebody = m_world->CreateBody(&ballbd);
	spherebody->CreateFixture(&ballfd);
	
	
      }
      
      //Dominos
      {
	//Dimensions of each domino
	b2PolygonShape shape;
	shape.SetAsBox(0.1f, 1.0f);
	
	b2FixtureDef fd;
	//Properties of the dominoes
	fd.shape = &shape;
	fd.density = 10.0f;
	fd.friction = 0.1f;
	//Setting the location of the dominoes
	for (int i = 0; i < 10; ++i)
	  {
	    b2BodyDef bd;
	    bd.type = b2_dynamicBody;
	    //Coordinates of the ith domino
	    bd.position.Set(rightshift +-35.5f + 1.0f * i, 31.25f + height);
	    b2Body* body = m_world->CreateBody(&bd);
	    body->CreateFixture(&fd);
	  }
      }   
    }
    
    //The pulley system 
    {
      //The global shift variables for the pulley system
      double pulleyright = 19.0 ;
      double pulleyup = -20.0 ;
      //The pulley system
      {   
	b2BodyDef *bd = new b2BodyDef;
	bd->type = b2_dynamicBody;
	bd->position.Set(-10.0 + 40.0 + pulleyright, 15+ pulleyup);
	bd->fixedRotation = true;
	
	//The open box
	b2FixtureDef *fd1 = new b2FixtureDef;
	//Properties of the open box
	//The horizontal bar
	fd1->density = 10.0;
	fd1->friction = 0.5;
	fd1->restitution = 0.f;
	fd1->shape = new b2PolygonShape;
	b2PolygonShape bs1;
	//Dimensions of the horizontal bar
	bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
	fd1->shape = &bs1;
	b2FixtureDef *fd2 = new b2FixtureDef;
	//Properties of the right vertical bar
	fd2->density = 10.0;
	fd2->friction = 0.5;
	fd2->restitution = 0.f;
	fd2->shape = new b2PolygonShape;
	b2PolygonShape bs2;
	//Dimensions of the right vertical bar
	bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
	fd2->shape = &bs2;
	b2FixtureDef *fd3 = new b2FixtureDef;
	//Properties of the left vertical bar
	fd3->density = 10.0;
	fd3->friction = 0.5;
	fd3->restitution = 0.f;
	fd3->shape = new b2PolygonShape;
	b2PolygonShape bs3;
	//Dimensions of the left vertical bar
	bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
	fd3->shape = &bs3;
	
	b2Body* box1 = m_world->CreateBody(bd);
	box1->CreateFixture(fd1);
	box1->CreateFixture(fd2);
	box1->CreateFixture(fd3);
	
	//The bar on the other side used to turn the platform to topple the ball onto the floor
	//The coordinates
	bd->position.Set(10 + pulleyright,15 + pulleyup);	
	fd1->density = 34.0;
	//The density      
	b2Body* box2 = m_world->CreateBody(bd);
	box2->CreateFixture(fd1);
	
	// The pulley joint
	b2PulleyJointDef* myjoint = new b2PulleyJointDef();
	//This is the left anchor point for the pulley
	b2Vec2 worldAnchorGround1(-10.0 + 40.0 + pulleyright, 20.0 + pulleyup); // Anchor point for ground 1 in world axis
	//This is the right anchor point for the pulley
	b2Vec2 worldAnchorGround2(10.0 + pulleyright, 20.0 + pulleyup); // Anchor point for ground 2 in world axis
	float32 ratio = 1.0f; // Define ratio
	myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
	m_world->CreateJoint(myjoint);
      }
      
      //The revolving horizontal platform
      {
	b2PolygonShape shape;
	//The dimensions of the platform
	shape.SetAsBox(2.2f, 0.2f);
	
	b2BodyDef bd;
	//The coordinates of the horizontal platform
	bd.position.Set(14.0f + pulleyright, 14.0f + pulleyup);
	bd.type = b2_dynamicBody;
	b2Body* body = m_world->CreateBody(&bd);
	b2FixtureDef *fd = new b2FixtureDef;
	//properties of the platform. Note that unlike other bodies, this platform is dynamic as it can rotate.
	fd->density = 1.f;
	fd->shape = new b2PolygonShape;
	fd->shape = &shape;
	body->CreateFixture(fd);
	
	//body used for the revolute joint
	b2BodyDef bd2;
	bd2.position.Set(6.0f + pulleyright, 16.0f + pulleyup);
	b2Body* body2 = m_world->CreateBody(&bd2);
	
	//The revolute joint for the anchor
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.bodyB = body2;
	//The pivot is one and the same, unlike the pulley system
	jointDef.localAnchorA.Set(0,0);
	jointDef.localAnchorB.Set(0,0);
	jointDef.collideConnected = false;
	m_world->CreateJoint(&jointDef);
      }
      
      //The heavy sphere on the platform
      {
	b2Body* sbody;
	b2CircleShape circle;
	//The radius of the heavy sphere
	circle.m_radius = .5;
	
	b2FixtureDef ballfd;
	ballfd.shape = &circle;
	//The properties of the heavy sphere
	ballfd.density = 50.0f;
	ballfd.friction = 0.0f;
	ballfd.restitution = 0.0f;
	b2BodyDef ballbd;
	ballbd.type = b2_dynamicBody;
	//The coordinates of the sphere, right on top of the revolving platform
	ballbd.position.Set(6.0 + pulleyright, 17.0f + pulleyup);
	sbody = m_world->CreateBody(&ballbd);
	sbody->CreateFixture(&ballfd);
      }
    }
    
    
    //  The (first) see-saw system to the left
    {
      //The shift parameters for the see saw system
      double shiftup = 20.0 + gup ;
      double shiftright = -45.0 + gright;
      
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      //This polygon is defined by its vertices, not dimensionally as it is a proper triangle
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      //Properties of the wedge
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      //The position of the wedge
      wedgebd.position.Set(30.0f + shiftright, 0.0f + shiftup);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
      
      //The plank on top of the wedge
      b2PolygonShape shape;
      //The dimensions of the plank atop the wedge
      shape.SetAsBox(10.0f, 0.2f);
      b2BodyDef bd2;
      //The position of the plank
      bd2.position.Set(30.0f + shiftright, 1.5f + shiftup);
      //Note that the plank is dynamic
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      //Properties of the plank (only friction is specified)
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
      
      //Definition of the revolute joint
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      //setting of the anchor position
      anchor.Set(30.5f + shiftright, 1.5f + shiftup);
      //The bodies used for the see saw are the wedge and the plack
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      
      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      //Dimensions of the box
      shape2.SetAsBox(1.2f, 1.2f);
      b2BodyDef bd3;
      //The location of the box
      bd3.position.Set(21.5f + shiftright, 2.0f + shiftup);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      //The properties of the box
      //A superficial friction is used for the purposes of our simulation, else the box will fall off very quickly.
      fd3->friction =25000.0;
      fd3->density = 10.0f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
      
      //The small horizontal shelf below the see saw system to give support to the see saw
      
      b2PolygonShape shelf;
      //Dimensions of the shelf
      shelf.SetAsBox(1.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
      
      b2BodyDef bd;
      //Location of the shelf
      bd.position.Set(50.0f + shiftright, -19.50f + shiftup);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shelf, 0.0f);
    }
    
    
    //  The (second) see-saw system to the right	
    {
      //The shift values for the second see saw system
      //The remaining documentation for this section is identical to the system just above this
      double shiftup = 0.0 + gup ;
      double shiftright = -11.0 + gright ;
      
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f + shiftright, 0.0f + shiftup);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
      
      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f + shiftright, 1.5f + shiftup);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
      
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.5f + shiftright, 1.5f + shiftup);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      
      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(1.2f, 1.2f);
      b2BodyDef bd3;
      //Notice that the light box now is kept on the opposite end of the plank. This is the major difference from the first see saw, apart from positioning.
      bd3.position.Set(38.5f + shiftright, 2.0f + shiftup);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->friction =25000.0;
      fd3->density = 5.0f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
      
      //The shelf beneath inorder to support the plank
      
      b2PolygonShape shelf;
      shelf.SetAsBox(1.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
      
      b2BodyDef bd;
      bd.position.Set(50.0f + shiftright, -19.15f + shiftup);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shelf, 0.0f);
    }
    
    
    //The steps system at the bottom
    { 
      //The global shift parameters for the step system towards the bottom
      double stepright = -53.5 ;
      double stepup = -30.0 ; 
      
      //The first horizontal bar
      {
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(2.0f, 0.05f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(50.0f + stepright, -19.50f + stepup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
	
      }
      //The first vertical bar   
      { 
	b2PolygonShape shelf;
	//Dimensions and angle
	shelf.SetAsBox(2.0f, 0.05f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	//Postion
	bd.position.Set(48.0f + stepright, -21.5f + stepup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      //The second horizontal bar
      {
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(2.0f, 0.05f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(46.0f + stepright, -23.50f + stepup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      //The second vertical bar
      { 
	b2PolygonShape shelf;
	//Dimensions and angle
	shelf.SetAsBox(2.0f, 0.05f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(44.0f + stepright, -25.50f + stepup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      //The third horizontal bar
      {
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(2.0f, 0.05f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(42.0f + stepright, -27.50f + stepup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      //The third vertical bar
      { 
	b2PolygonShape shelf;
	//Dimensions and angle
	shelf.SetAsBox(2.0f, 0.05f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(40.0f + stepright, -29.50f + stepup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      //The three balls on the steps
      {
	//The first ball
	b2Body* sbody;
	b2CircleShape circle;
	//radius
	circle.m_radius = .5;
	
	b2FixtureDef ballfd;
	ballfd.shape = &circle;
	//other properties
	ballfd.density = 50.0f;
	ballfd.friction = 0.0f;
	ballfd.restitution = 0.0f;
	b2BodyDef ballbd;
	ballbd.type = b2_dynamicBody;
	//position
	ballbd.position.Set(29.5 + stepright, 13.0f + stepup);
	sbody = m_world->CreateBody(&ballbd);
	sbody->CreateFixture(&ballfd);
      }
      
      {
	//The second ball
	b2Body* sbody;
	b2CircleShape circle;
	//radius
	circle.m_radius = .5;
	
	b2FixtureDef ballfd;
	ballfd.shape = &circle;
	//other properties
	ballfd.density = 50.0f;
	ballfd.friction = 0.0f;
	ballfd.restitution = 0.0f;
	b2BodyDef ballbd;
	ballbd.type = b2_dynamicBody;
	//Position
	ballbd.position.Set(25.5 + stepright, 13.0f + stepup);
	sbody = m_world->CreateBody(&ballbd);
	sbody->CreateFixture(&ballfd);
      }
      
      {
	//The third ball
	b2Body* sbody;
	b2CircleShape circle;
	//Radius
	circle.m_radius = .5;
	
	b2FixtureDef ballfd;
	ballfd.shape = &circle;
	//Other properties
	ballfd.density = 50.0f;
	ballfd.friction = 0.0f;
	ballfd.restitution = 0.0f;
	b2BodyDef ballbd;
	ballbd.type = b2_dynamicBody;
	//Position
	ballbd.position.Set(21.5 + stepright, 13.0f + stepup);
	sbody = m_world->CreateBody(&ballbd);
	sbody->CreateFixture(&ballfd);
      }
    }
    
    //The floor system at the bottom
    //This has a hole which must be first filled in by one of the balls above, whichwill allow the second ball to pass through
    {// The global shift parameters for the floor system
      double floorright = -70.0 ;
      double floorup = -60.0 ;
      
      {
	//The right floor
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(50.0f + floorright, -19.50f + floorup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {  //The left floor
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(36.0f + floorright, -19.50f + floorup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      {	//The tiny floor between the floors above
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(0.7f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(43.0f + floorright, -20.50f + floorup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      {//The elastic ball
	b2Body* sbody;
	b2CircleShape circle;
	//radius
	circle.m_radius = .5;
	
	b2FixtureDef ballfd;
	ballfd.shape = &circle;
	//other properties
	ballfd.density = 130.0f;
	ballfd.friction = 0.0f;
	//It is this restitution which allows the ball to jump high, and make the floor appear like a trampoline
	ballfd.restitution = 1.1f;
	b2BodyDef ballbd;
	ballbd.type = b2_dynamicBody;
	//Position
	ballbd.position.Set(31 + floorright, 1.0f + floorup);
	sbody = m_world->CreateBody(&ballbd);
	sbody->CreateFixture(&ballfd);
      }
    }
    
//The Trampoline Floor
    
    {
      b2PolygonShape shelf;
      //Dimensions
      shelf.SetAsBox(25.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
      
      b2BodyDef bd;
      //Position
      bd.position.Set(-66.5f, -99.50f );
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shelf, 0.0f);
    }   
    
    //The Last Box
    {//Shift paramaters for the last box
      double lastright = -155.0 ;
      double lastup = -65.0 ;
      
      {//The lower bar
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(55.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(5.0f + lastright, -19.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The upper bar
	b2PolygonShape shelf;
	//Dimensions: This bar is slightly smaller than the lower bar
	shelf.SetAsBox(50.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	//Position: This bar is slight shifted to the left than the lower bar
	bd.position.Set(0.0f + lastright, -7.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {
	//The Right Vertical Bar
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(60.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {	//The Left Vertical Bar
	b2PolygonShape shelf;
	//Dimensions
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	//Position
	bd.position.Set(-50.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
    }
    
    //Dead Object Containers: #1; Each of them consists of an open box, which as horizontal bar at the bottom, a vertical bar to the left, and another vertical bar to the right.
    {
      //The shift parameters for this container
      double lastright = -65.0 ;
      double lastup = 30.0 ;
      
      {//The horizontal bar
	b2PolygonShape shelf;
	shelf.SetAsBox(5.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	bd.position.Set(50.0f + lastright, -19.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The right vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(55.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The left vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(45.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
    }
    
    //Dead Object Containers: #2
    {
      //The shift parameters for this container
      double lastright = -35.0 ;
      double lastup = 10.0 ;
      
      {//The lower horizontal bar
	b2PolygonShape shelf;
	shelf.SetAsBox(5.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	bd.position.Set(50.0f + lastright, -19.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The right vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(55.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The left vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(45.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
    }
    
    //Dead Object Containers: #3
    {//The overall shift parameters for the third container
      double lastright = 0.0;
      double lastup = 10.0;
      
      {//The lower horizontal bar
	b2PolygonShape shelf;
	shelf.SetAsBox(5.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	bd.position.Set(50.0f + lastright, -19.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The right vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(55.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The left vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(45.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
    }
    
    //Dead Object Containers: #4
    {//The overall shift parameters for the fourth container
      double lastright = 40.0 ;
      double lastup = -10.0 ;
      
      {//The lower horizontal bar
	b2PolygonShape shelf;
	shelf.SetAsBox(5.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	b2BodyDef bd;
	bd.position.Set(50.0f + lastright, -19.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The right vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(55.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
      {//The left vertical bar
	b2PolygonShape shelf;
	shelf.SetAsBox(6.0f, 0.25f, b2Vec2(-20.f,20.f), PI/2);
	
	b2BodyDef bd;
	bd.position.Set(45.0f + lastright, -13.50f + lastup);
	b2Body* ground = m_world->CreateBody(&bd);
	ground->CreateFixture(&shelf, 0.0f);
      }
      
    }
    
//The conveyor belt
    
    //The idea is to make a rectangular chain
    //Then, we insert rotating discs "in" the chain
    //We keep a very high friction between these discs and the chain
    //We give the discs a constant angular velocity, due to which the conveyor belt rotates
    //Idea courtesy : Rohith Kishan
    {
      //overall shift parameters for the entire conveyor belt system
      double conveyorleft = -15.0;
       double conveyorup = -20.0;
       //The number of links in the conveyor belt system either above or below.
       //The total number of links will be 2*links + 4 (2 links also on either side)
       int links = 20; //This number must be divisible by 4 and > 20 so that 5 well spaced disks which rotate and drive the pulley can be layed out
       
       double speed = PI/3; //This is the speed at which the conveyor belts' driving wheels rotate
       
       //The links are made as follows.
       //First, we make the lower chain.
       //Then, we make the upper chain
       //Then, we make the two links which join these two chains on the left hand side
       //Then, we make the two links which join these two chains on the right hand side	
       b2Body* leftup; //this is the body which is the top left link
       b2Body* rightup; //this is the body which is the top right link
       b2Body* leftdown; //this is the body which is the bottom left link
       b2Body* rightdown; //this is the body which is the bottom right link
       //Note that these four special links are required because they are used specifically to connect the upper and lower chains
       
       //here we initialize them to default initial values
       leftup = NULL;
       rightup = NULL;
       leftdown = NULL;
       rightdown = NULL;
       //Making the upper part of the conveyor belt
       
       {
	 //defining each piece of the chain, along with the shape, size, fixture and relevant properties
	 b2BodyDef bd;
	 //The body is a dynamic body
	 bd.type = b2_dynamicBody;
	 bd.position.Set(conveyorleft, conveyorup);
	 b2Body* ground = m_world->CreateBody(&bd);
	 b2PolygonShape chainpiece;
	 //Dimensions
	 chainpiece.SetAsBox(1, 0.2); 
	 b2FixtureDef chainfix;
	 //Properties
	 chainfix.density = 50;
	 chainfix.friction = 0.5;
	 chainfix.restitution = 0.5;
	 chainfix.shape = &chainpiece;
	 //Defining a revolute joint for our purpose
	 b2Body *lastLink = ground;
	 b2RevoluteJointDef chainJoint;
	 //If the bodies are connected in the Box 2D world, then they should not collide. This is why this line is needed.
	 chainJoint.collideConnected = false;
    
	 for(int32 i = 0; i < links; i++)
	   {
	     double cons = 2.0;//This is the difference in length in between two anchors
	     b2BodyDef bd;
	     bd.type = b2_dynamicBody;
	     bd.position.Set(i*cons + conveyorleft, 0.0 + conveyorup);//setting up a new dynamic chain link
	     b2Body* nextLink = m_world->CreateBody(&bd);
	     nextLink->CreateFixture(&chainfix);
	     b2Vec2 anchor(i*cons - 1.0  + conveyorleft, 0.0 + conveyorup);//The anchor is set exactly at the meeting point of two chain links
	     if(i > 0)//We should not define a link for the first piece alone. We need atleast two pieces to begin linking
	       {
		 chainJoint.Initialize(lastLink, nextLink, anchor);
		 m_world->CreateJoint(&chainJoint);
	       }
	     //Updating the current link
	     lastLink = nextLink;
	     //assignment to the last link. The last link will essentially be rightdown, once we exit this loop
	     rightdown = nextLink;
	     //for the first link, we need to set leftdown, which is supposed to point to that link (body)
	     if(i == 0)
	       {
		 leftdown = nextLink;
	       }
	   }
       }
       //here we make the lower part of the conveyor belt chain
       {
	 double shiftup = 4.0;//this denotes the height to which we shift up the upper part of the chain
	 // The rest of the process is identical to the first part except that everything is shifted up
	 b2BodyDef bd;
	 bd.type = b2_dynamicBody;
	 bd.position.Set(conveyorleft, conveyorup + shiftup);
	 b2Body* ground = m_world->CreateBody(&bd);
	 b2PolygonShape chainpiece;
	 chainpiece.SetAsBox(1, 0.2);
	 b2FixtureDef chainfix;
	 chainfix.density = 50;
	 chainfix.friction = 0.5;
       chainfix.restitution = 0.5;
       chainfix.shape = &chainpiece;
       b2Body *lastLink = ground;
       b2RevoluteJointDef chainJoint;
       chainJoint.collideConnected = false;
       
       for(int32 i = 0; i < links; i++)
	 {
	   double cons = 2.0;
	   b2BodyDef bd;
	   bd.type = b2_dynamicBody;
	   bd.position.Set(i*cons + conveyorleft, shiftup + conveyorup);
	   b2Body* nextLink = m_world->CreateBody(&bd);
	   nextLink->CreateFixture(&chainfix);
	   b2Vec2 anchor(i*cons - 1.0 + conveyorleft, shiftup + conveyorup);
	   if(i > 0)
	     {
	       chainJoint.Initialize(lastLink, nextLink, anchor);
	       m_world->CreateJoint(&chainJoint);
	     }
	   lastLink = nextLink;
	   rightup = nextLink;//"rightup" is updated to the right most link in the top part of the chain in every iteration
	   if(i == 0)
	     {
	       leftup = nextLink;//"leftup" stores information about the topleft link
	       //More Precisely, it stores a link to the body of the upper left link
	     }
       }
       }
       
       //Now, we make the two links on the left hand side which connect the upper and lower halves of the chain
       {
	 b2BodyDef bd;
	 bd.type = b2_dynamicBody;//Note that this is a dynamic body
	 //Position
	 bd.position.Set(-1.0 + conveyorleft, conveyorup + 1.0);
	 b2Body* ground = m_world->CreateBody(&bd);
	 b2PolygonShape chainpiece;
	 //Dimensions. Note that the dimensions are reversed, so that this is a vertical link, while the earlier one was a horizontal link
	 chainpiece.SetAsBox(0.2, 1, b2Vec2(0.0,0.0),0.0);
	 
	 //Again defining a fixture for the chain
	 b2FixtureDef chainfix;
	 //Chain Properties
	 chainfix.density = 50;
	 chainfix.friction = 0.5;
	 chainfix.restitution = 0.5;
	 chainfix.shape = &chainpiece;
	 //Creating the first vertical link on the left
	 ground->CreateFixture(&chainfix);
	 
	 bd.position.Set(-1.0 + conveyorleft, conveyorup + 3.0);
	 //Creating the second vertical link on the left
	 b2Body*groundnew = m_world->CreateBody(&bd);
	 groundnew->CreateFixture(&chainfix);
	 
	 //defining the revolute joint to connect links up
	 b2RevoluteJointDef chainJoint;
	 chainJoint.collideConnected = false;
	 b2Vec2 anchor( conveyorleft - 1.0, conveyorup);
	 //Connecting the lower left horizontal link and the lower vertical link
	 chainJoint.Initialize(leftdown, ground, anchor);
	 m_world->CreateJoint(&chainJoint);
	 
	 b2RevoluteJointDef chainJoint2;
	 chainJoint2.collideConnected = false;
	 b2Vec2 anchor2( conveyorleft - 1.0, 2.0 + conveyorup);
	 //Connecting the lower and upper vertical links
	 chainJoint2.Initialize(ground, groundnew, anchor2);
	 m_world->CreateJoint(&chainJoint2);
	 
	 b2RevoluteJointDef chainJoint3;
	 chainJoint3.collideConnected = false;
	 b2Vec2 anchor3( conveyorleft - 1.0, 4.0 + conveyorup);
	 //Connecting the upper vertical link and the top left horizontal link
	 chainJoint3.Initialize(groundnew, leftup, anchor3);
	 m_world->CreateJoint(&chainJoint3);
       }
       
       //Now again we connect the top and bottom portions of the conveyor belt, this time at the right end.
       {
       b2BodyDef bd;
       bd.type = b2_dynamicBody;
       //Note that the position is shifted towards the rights by a number proportional to the number of links in the chain
       bd.position.Set(2.0 * links - 1.0+ conveyorleft, conveyorup + 1.0);
       b2Body* ground = m_world->CreateBody(&bd);
       b2PolygonShape chainpiece;
       chainpiece.SetAsBox(0.2, 1, b2Vec2(0.0,0.0),0.0);
       //Defining the links and setting properties
       b2FixtureDef chainfix;
       chainfix.density = 50;
       chainfix.friction = 0.5;
       chainfix.restitution = 0.5;
       chainfix.shape = &chainpiece;
       //Making the lower vertical RHS link
       ground->CreateFixture(&chainfix);
     //Making the upper vertical RHS link
       bd.position.Set(2.0* links - 1.0+ conveyorleft, conveyorup + 3.0);
       b2Body*groundnew = m_world->CreateBody(&bd);
       groundnew->CreateFixture(&chainfix);
//Defining the revolute joint
       b2RevoluteJointDef chainJoint;
       chainJoint.collideConnected = false;
       b2Vec2 anchor( 2.0 * links - 1.0 + conveyorleft, 0.0 + conveyorup);
       //Joining the right most link of the lower chain and the lower vertical link on the right
       chainJoint.Initialize(rightdown, ground, anchor);
       m_world->CreateJoint(&chainJoint);
       
       b2RevoluteJointDef chainJoint2;
       chainJoint2.collideConnected = false;
       b2Vec2 anchor2( 2.0 * links - 1.0+ conveyorleft, 2.0 + conveyorup);
       //Joining the lower and upper right vertical links
       chainJoint2.Initialize(ground, groundnew, anchor2);
       m_world->CreateJoint(&chainJoint2);
       
       b2RevoluteJointDef chainJoint3;
       chainJoint3.collideConnected = false;
       b2Vec2 anchor3( 2.0 * links - 1.0+ conveyorleft, 4.0 + conveyorup);
       //joining the upper right vertical link with the top right horizontal link
       chainJoint3.Initialize(groundnew, rightup, anchor3);
       m_world->CreateJoint(&chainJoint3);
       }
       //Now, we create the rotating high friction discs
       //
       //The parameters are similar for all the discs, except that they are all translated along the x axis
//
//
//
//The left most Disc:
       {
	 b2BodyDef bd;
   bd.type = b2_kinematicBody;//This disc is a kinematic body
   bd.position.Set(conveyorleft + 0.0, conveyorup + 2.0);//Position
   bd.angle = 0;//starts rotating at angle 0
   b2Body* body = m_world->CreateBody(&bd);
   b2CircleShape circle;//shape of body = circular
   circle.m_radius = 2.0;//radius of disc used (same as the rectangular length of the boxes)
   
   b2FixtureDef fd;
   //properties of the disc
   fd.shape = &circle;
   fd.density = 100;
   fd.friction = 1;//Note the friction. It is set as 1!
   body->CreateFixture(&fd);
   body->SetAngularVelocity(speed);
   
       }
       
       //The last disc (right most disc)
       {
	 b2BodyDef bd;
	 bd.type = b2_kinematicBody;
	 //Note the shift in position from the earlier disc
	 bd.position.Set(links * 2.0 + conveyorleft + -2.0, conveyorup + 2.0);
	 bd.angle = 0;
	 b2Body* body = m_world->CreateBody(&bd);
	 b2CircleShape circle;
	 circle.m_radius = 2.0;
	 
	 b2FixtureDef fd;
	 fd.shape = &circle;
	 fd.density = 100;
	 fd.friction = 1;
	 body->CreateFixture(&fd);
	 body->SetAngularVelocity(speed);
       }
       
       //The second disc from the left hand side
       {
	 b2BodyDef bd;
	 bd.type = b2_kinematicBody;
	 //Note the position
	 bd.position.Set(links/4 * 2.0 + 1.0 + conveyorleft + -2.0, conveyorup + 2.0);
	 bd.angle = 0;
	 b2Body* body = m_world->CreateBody(&bd);
	 b2CircleShape circle;
	 circle.m_radius = 2.0;
	 
	 b2FixtureDef fd;
	 fd.shape = &circle;
	 fd.density = 100;
	 fd.friction = 1;
	 body->CreateFixture(&fd);
	 body->SetAngularVelocity(speed);
       }
       
       //The third disc from the left hand side
       {
	 b2BodyDef bd;
	 bd.type = b2_kinematicBody;
	 //Note the position
	 bd.position.Set(links/2 * 2.0 + 1.0 + conveyorleft + -2.0, conveyorup + 2.0);
	 bd.angle = 0;
	 b2Body* body = m_world->CreateBody(&bd);
	 b2CircleShape circle;
	 circle.m_radius = 2.0;
	 
	 b2FixtureDef fd;
	 fd.shape = &circle;
	 fd.density = 100;
	 fd.friction = 1;
	 body->CreateFixture(&fd);
	 body->SetAngularVelocity(speed);
       }
       
       //The fourth disc from the left hand side
{
  b2BodyDef bd;
  bd.type = b2_kinematicBody;
  //Note the position
  bd.position.Set(3 * links/4 * 2.0 + 1.0 + conveyorleft + -2.0, conveyorup + 2.0);
  bd.angle = 0;
  b2Body* body = m_world->CreateBody(&bd);
  b2CircleShape circle;
  circle.m_radius = 2.0;
  
  b2FixtureDef fd;
  fd.shape = &circle;
  fd.density = 100;
  fd.friction = 1;
  body->CreateFixture(&fd);
  body->SetAngularVelocity(speed);
 }
 
 
    }

    
  }
  

  
  
  sim_t *sim = new sim_t("By Ayush, Pratyush and Bhargava", dominos_t::create);
}
