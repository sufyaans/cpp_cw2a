#include <math.h>
#include <map>
#include "Geometry.h"


inline void swap(float& x, float& y) { 
    float temp { x };
    x = y;
    y = temp;
}

// ============ Shape class =================

Shape::Shape(int d) {
    if (d < 0)
        throw std::invalid_argument("Negative depth not allowed!");
    
    depth = d;
}

bool Shape::setDepth(int d) {
    if (d < 0)
        return false;
    
    depth = d;
    return true;
}

int Shape::getDepth() const {
    return depth;
}


int Shape::dim() const {
	// IMPLEMENT ME
	return -999; // dummy
}

void Shape::translate(float x, float y) {
	// IMPLEMENT ME
}

void Shape::rotate() {
	// IMPLEMENT ME
}

void Shape::scale(float f) {
	// IMPLEMENT ME
}

bool Shape::contains(const Point& p) const {
	// IMPLEMENT ME
	return false; // dummy
}

// =============== Point class ================

Point::Point(float x, float y, int d) : Shape(d) {
    this->distX = x;
    this->distY = y;
}

float Point::getX() const {
    return distX;
}


float Point::getY() const {
    return distY;
}

int Point::dim() const {
    return 0;
}

void Point::translate(float x, float y) {
    // Increment/Decrement point's coordinate by x and y
    this->distX += x;
    this->distY += y;
}

void Point::rotate() {} // Rotation of a point has no effect

void Point::scale(float f) { //no effect on POINT
    if (f <= 0)
        throw std::invalid_argument("Negative scale factor"); 
}

bool Point::contains(const Point& p) const {
	bool res = false;
	if(p.getX() == distX && p.getY() == distY){
		res = true;
	}
	return res;
}


// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) : Shape(0) { // Call Shape() ctor to set depth temporarily as 0
    // Exceptions
    if (p.getDepth() != q.getDepth())
        throw std::invalid_argument("Points depth mismatch");
    else if (p.getX() != q.getX() && p.getY() != q.getY())
        throw std::invalid_argument("Line is not axis-aligned");
    else if (p.getX() == q.getX() && p.getY() == q.getY())
        throw std::invalid_argument("Points conincide");

    // Set depth as the points are valid
    setDepth(p.getDepth());

    if (p.getX() != q.getX()) { // Line parallel to Y-axis
        y1 = y2 = p.getY();
        
        x1 = std::min(p.getX(), q.getX());
        x2 = std::max(p.getX(), q.getX());
    }
    else {                      // Line parallel to X-axis
        x1 = x2 = p.getX();
        
        y1 = std::min(p.getY(), q.getY());
        y2 = std::max(p.getY(), q.getY());
    }
}

float LineSegment::getXmin() const {
    return x1;
}

float LineSegment::getXmax() const {
    return x2;
}

float LineSegment::getYmin() const {
    return y1;
}

float LineSegment::getYmax() const {
    return y2;
}

float LineSegment::length() const {
    // Distance formula
	float ans = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
	return ans;
}

int LineSegment::dim() const {
    // A line segment is 1 dimensional
    return 1;
}

void LineSegment::translate(float x, float y) {
    // Increment/Decrement both the point's coordinates by x and y
    x1 += x;
	y1 += y;
    x2 += x; 
	y2 += y;
}

void LineSegment::rotate() {
    float midX, midY;
    float tempX, tempY;
    
    if (x1 == x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    
    midX = (x1 + x2) / 2;
    midY = (y1 + y2) / 2;

    x1 -= midX; 
	y1 -= midY;
    x2 -= midX; 
	y2 -= midY;

    tempX = x1 ; 
	tempY = y1;
    
	x1 =- tempY; 
	y1 = tempX; 

    tempX = x2; 
	tempY = y2;
    
	x2 =- tempY; 
	y2 = tempX; 

    x1 += midX; 
	y1 += midY;
    
	x2 += midX; 
	y2 += midY;
}

void LineSegment::scale(float f) {
    float midX, midY;
    
    if (f <= 0)
        throw std::invalid_argument("Negative scale factor");
    
    midX = (x1 + x2) / 2;
    midY = (y1 + y2) / 2;

    x1 -= midX; 
	y1 -= midY;

    x2 -= midX; 
	y2 -= midY;
    
    x1 *= f; 
	y1 *= f;

    x2 *= f; 
	y2 *= f;
    
    x1 += midX; 
	y1 += midY;

    x2 += midX; 
	y2 += midY;
}

bool LineSegment::contains(const Point& p) const {
    if (x1 != x2) 
        return (p.getY() == y1 && p.getX() >= std::min(x1, x2) && p.getX() <= std::max(x1, x2));
    else     
        return (p.getX() == x1 && p.getY() >= std::min(y1, y2) && p.getY() <= std::max(y1, y2));
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(int d) : Shape(d) {}

int TwoDShape::dim() const {
    return 2;
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
	// IMPLEMENT ME
}

float Rectangle::getXmin() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Rectangle::getYmin() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Rectangle::getXmax() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Rectangle::getYmax() const {
	// IMPLEMENT ME
	return -999; // dummy
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) : TwoDShape(0) {
    if (r <= 0)
        throw std::invalid_argument("Invalid argument!");
    
    setDepth(c.getDepth());
    
    x = c.getX();
    y = c.getY();
    
    radius = r;
}

float Circle::getX() const {
    return x;
}

float Circle::getY() const {
    return y;
}

float Circle::getR() const {
    return radius;
}

// ================= Scene class ===================

Scene::Scene() {
	// IMPLEMENT ME
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	// IMPLEMENT ME
}

void Scene::setDrawDepth(int depth) {
	// IMPLEMENT ME
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	// IMPLEMENT ME
	return out;
}
