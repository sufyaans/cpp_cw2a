#include "Geometry.h"

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


// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) {
	// IMPLEMENT ME
}

float LineSegment::getXmin() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float LineSegment::getXmax() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float LineSegment::getYmin() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float LineSegment::getYmax() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float LineSegment::length() const {
	// IMPLEMENT ME
	return -999; // dummy
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(int d) {
	// IMPLEMENT ME
}

float TwoDShape::area() const {
	// IMPLEMENT ME
	return -999; // dummy
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

Circle::Circle(const Point& c, float r) {
	// IMPLEMENT ME
}

float Circle::getX() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Circle::getY() const {
	// IMPLEMENT ME
	return -999; // dummy
}

float Circle::getR() const {
	// IMPLEMENT ME
	return -999; // dummy
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
