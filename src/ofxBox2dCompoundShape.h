//
//  ofxBox2dCompoundShape.h
//
//  Created by Nick Hardeman on 12/28/18.
//

#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"

class ofxBox2dCompoundShape : public ofxBox2dBaseShape {
public:
    
    class Shape {
    public:
        Shape() {}
        ~Shape() {}
        enum Type {
            SHAPE_TYPE_RECT=0,
            SHAPE_TYPE_CIRCLE
        };
        virtual Type getType() { return SHAPE_TYPE_RECT;}
        
        float x = 0; float y = 0;
    };
    
    class Rectangle : public Shape {
    public:
        Rectangle() {}
        Rectangle(float ax, float ay, float aw, float ah ) { width=aw; height=ah; x=ax; y=ay; }
        ~Rectangle() {}
        
        Type getType() override { return SHAPE_TYPE_RECT;}
        
        float width = 10; float height = 10.f;
        
    };
    
    class Circle : public Shape {
    public:
        Circle() {}
        Circle(float ax, float ay, float aradius) { radius=aradius;x=ax;y=ay; }
        ~Circle() {}
        
        Type getType() override { return SHAPE_TYPE_CIRCLE;}
        
        float radius = 10; 
    };
    
    void setup( b2World* aworld, glm::vec2 aworldPos );
    void setup( b2World* aworld, glm::vec2 aworldPos, vector<ofxBox2dCompoundShape::Shape> ashapes );
    void addRect( ofxBox2dCompoundShape::Rectangle aLocalRect );
    void addRect( ofRectangle aLocalRect );
    void addRect( float ax, float ay, float aw, float ah );
    void addCircle( ofxBox2dCompoundShape::Circle acircle );
    void addCircle( float ax, float ay, float aradius );
    
    void draw() override;
    
protected:
    vector< shared_ptr<Shape> > mShapes;
};
