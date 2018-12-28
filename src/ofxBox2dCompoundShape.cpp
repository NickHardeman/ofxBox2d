//
//  ofxBox2dCompoundShape.cpp
//
//  Created by Nick Hardeman on 12/28/18.
//

#include "ofxBox2dCompoundShape.h"

//--------------------------------------------------------------
void ofxBox2dCompoundShape::setup(b2World* aworld, glm::vec2 aworldPos ) {
    if(aworld == NULL) {
        ofLog(OF_LOG_NOTICE, "- must have a valid world -");
        return;
    }
    
    b2BodyDef bodyDef;
    if(density == 0.f) bodyDef.type    = b2_staticBody;
    else               bodyDef.type    = b2_dynamicBody;
    bodyDef.position.Set(aworldPos.x/OFX_BOX2D_SCALE, aworldPos.y/OFX_BOX2D_SCALE);
    
    body = aworld->CreateBody(&bodyDef);
}

//--------------------------------------------------------------
void ofxBox2dCompoundShape::addRect( ofxBox2dCompoundShape::Rectangle aLocalRect ) {
    if(body == NULL) {
        ofLog(OF_LOG_NOTICE, "- ofxBox2dCompoundShape :: must call setup first. -");
        return;
    }
    
    b2World* tworld = getWorld();
    auto rect = make_shared<ofxBox2dCompoundShape::Rectangle>(aLocalRect);
//    rect->width /= 2.f;
//    rect->height /= 2.f;
    
    b2PolygonShape shape;
    // polygon2.SetAsBox((tw*0.5f)/OFX_BOX2D_SCALE, (th/2.f)/OFX_BOX2D_SCALE, b2Vec2( 0.0f, -(th*2)/OFX_BOX2D_SCALE), 0. );
    shape.SetAsBox((rect->width/2.f)/OFX_BOX2D_SCALE, (rect->height/2.f)/OFX_BOX2D_SCALE,
                   b2Vec2( rect->x/OFX_BOX2D_SCALE, rect->y/OFX_BOX2D_SCALE), 0.f );
    
    fixture.shape       = &shape;
    fixture.density     = density;
    fixture.friction    = friction;
    fixture.restitution = bounce;
    
    body->CreateFixture(&fixture);
    
    mShapes.push_back( rect );
    
    alive = true;
}

//--------------------------------------------------------------
void ofxBox2dCompoundShape::addRect(ofRectangle aLocalRect ) {
    addRect( ofxBox2dCompoundShape::Rectangle( aLocalRect.x, aLocalRect.y, aLocalRect.width, aLocalRect.height ));
}

//--------------------------------------------------------------
void ofxBox2dCompoundShape::addRect( float ax, float ay, float aw, float ah ) {
    addRect( ofxBox2dCompoundShape::Rectangle( ax, ay, aw, ah ));
}

//--------------------------------------------------------------
void ofxBox2dCompoundShape::addCircle( ofxBox2dCompoundShape::Circle acircle ) {
    if(body == NULL) {
        ofLog(OF_LOG_NOTICE, "- ofxBox2dCompoundShape :: must call setup first. -");
        return;
    }
    
    b2World* tworld = getWorld();
    auto circle = make_shared<ofxBox2dCompoundShape::Circle>(acircle);
    
    // these are used to create the shape
    b2CircleShape shape;
    
    shape.m_p.Set( circle->x / OFX_BOX2D_SCALE, circle->y / OFX_BOX2D_SCALE );
    shape.m_radius      = circle->radius / OFX_BOX2D_SCALE;
    
    fixture.shape       = &shape;
    fixture.density     = density;
    fixture.friction    = friction;
    fixture.restitution = bounce;
    
    body->CreateFixture(&fixture);
    
    mShapes.push_back( circle );
    
    alive = true;
}

//--------------------------------------------------------------
void ofxBox2dCompoundShape::addCircle( float ax, float ay, float aradius ) {
    addCircle( ofxBox2dCompoundShape::Circle(ax, ay, aradius ));
}

//--------------------------------------------------------------
void ofxBox2dCompoundShape::draw() {
    if(!isBody()) return;
    
    ofPushMatrix(); {
        ofTranslate(getPosition().x, getPosition().y, 0);
        ofRotateDeg(getRotation(), 0, 0, 1);
        
        ofPushStyle(); {
            ofNoFill();
            for( auto& shape : mShapes ) {
                if( shape->getType() == ofxBox2dCompoundShape::Shape::SHAPE_TYPE_CIRCLE ) {
                    auto circle = dynamic_pointer_cast<ofxBox2dCompoundShape::Circle>(shape);
                    ofDrawCircle(circle->x, circle->y, circle->radius);
                } else {
                    auto rect = dynamic_pointer_cast<ofxBox2dCompoundShape::Rectangle>(shape);
                    ofDrawRectangle( -rect->width/2.f+rect->x, -rect->height/2.f+rect->y, rect->width, rect->height );
                }
            }
            
        } ofPopStyle();
    
    } ofPopMatrix();
}




