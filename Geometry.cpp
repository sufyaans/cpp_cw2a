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

void Point::rotate() {} 
// Rotation of a point has no effect

void Point::scale(float f) { 
    

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

LineSegment::LineSegment(const Point& p, const Point& q) : Shape(0) { 
    

    // Exceptions
    if (p.getDepth() != q.getDepth())
        throw std::invalid_argument("Points depth mismatch");
    else if (p.getX() != q.getX() && p.getY() != q.getY())
        throw std::invalid_argument("Line is not axis-aligned");
    else if (p.getX() == q.getX() && p.getY() == q.getY())
        throw std::invalid_argument("Points conincide");

    // Set depth as the points are valid
    setDepth(p.getDepth());

    if (p.getX() != q.getX()) { 
        // Line parallel to Y-axis
        y1 = y2 = p.getY();
        
        x1 = std::min(p.getX(), q.getX());
        x2 = std::max(p.getX(), q.getX());
    }
    else {                      
        // Line parallel to X-axis
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

Rectangle::Rectangle(const Point& p, const Point& q) : TwoDShape(0) {
    if (p.getDepth() != q.getDepth())
        throw std::invalid_argument("Depth mismatch");
    else if (p.getX() == q.getX() || p.getY() == q.getY())
        throw std::invalid_argument("Lines coincide");
    
    setDepth(p.getDepth());
    
    if (p.getX() < q.getX() && p.getY() < q.getY()) {       
        // Px < Qx, Py < Qy
        x1 = p.getX(); y1 = p.getY();
        x3 = q.getX(); y3 = q.getY();
        
        x2 = q.getX(); y2 = p.getY();
        x4 = p.getX(); y4 = q.getY();
    }
    else if (p.getX() < q.getX() && p.getY() > q.getY()) {  
        // Px < Qx, Py > Qy
        x2 = q.getX(); y2 = q.getY();
        x4 = p.getX(); y4 = p.getY();
        
        x1 = p.getX(); y1 = q.getY();
        x3 = q.getX(); y3 = p.getY();
    }
    else if (p.getX() > q.getX() && p.getY() > q.getY()) {  
        // Px > Qx, Py > Qy
        x1 = q.getX(); y1 = q.getY();
        x3 = p.getX(); y3 = p.getY();
        
        x2 = p.getX(); y2 = q.getY();
        x4 = q.getX(); y4 = p.getY();
    }
    else {                                                  
        // Px > Qx, Py < Qy
        x2 = p.getX(); y2 = p.getY();
        x4 = q.getX(); y4 = q.getY();
        
        x1 = q.getX(); y1 = p.getY();
        x3 = p.getX(); y3 = q.getY();
    }
}

float Rectangle::getXmin() const {
    return x1;
}

float Rectangle::getYmin() const {
    return y1;
}

float Rectangle::getXmax() const {
    return x3;
}

float Rectangle::getYmax() const {
    return y3;
}

float Rectangle::area() const {
    return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2)) * sqrtf(powf(x3 - x2, 2) + powf(y3 - y2, 2));
}

void Rectangle::translate(float x, float y) {
    for (size_t i {0}; i < 4; i++) {
        *xCoorArray[i] += x;
        *yCoorArray[i] += y;
    }
}

void Rectangle::rotate() {
    float midX, midY, xTemp, yTemp;
    
    midX = (x1 + x2) / 2;
    midY = (y1 + y4) / 2;
    
    // Shift to origin
    for (size_t i {0}; i < 4; i++) {
        *xCoorArray[i] -= midX;
        *yCoorArray[i] -= midY;
    }
    
    for (size_t i {0}; i < 4; i++) {
        xTemp = *xCoorArray[i];
        yTemp = *yCoorArray[i];
        
        *xCoorArray[i] = (0 * xTemp) + (-1 * yTemp) + midX;
        *yCoorArray[i] = (1 * xTemp) + (0  * yTemp) + midY;
    }
    
    swap(x1, x4); swap(y1, y4);
    swap(x2, x3); swap(y2, y3);
    
    if (y1 != y2) {
        swap(x2, x4);
        swap(y2, y4);
    }
}


void Rectangle::scale(float f) {
    if (f <= 0)
        throw std::invalid_argument("Negative scale factor");

    float midX, midY;
    
    midX = (x1 + x2) / 2;
    midY = (y1 + y4) / 2;
    
    for (size_t i {0}; i < 4; i++) {
        *xCoorArray[i] -= midX;
        *yCoorArray[i] -= midY;
    }
    
    for (size_t i {0}; i < 4; i++) {
        *xCoorArray[i] *= f;
        *yCoorArray[i] *= f;
    }
    
    for (size_t i {0}; i < 4; i++) {
        *xCoorArray[i] += midX;
        *yCoorArray[i] += midY;
    }
}

bool Rectangle::contains(const Point& p) const {
    return (p.getX() >= x1 && p.getX() <= x3 && p.getY() >= y1 && p.getY() <= y3);
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


float Circle::area() const {
    // Area (Circle) = πr2
    return PI * (radius * radius);
}

void Circle::translate(float x, float y) {
    this->x += x;
    this->y += y;
}

void Circle::rotate() { } 

void Circle::scale(float f) {
    if (f <= 0)
        throw std::invalid_argument("Negative scale factor");
    
    radius *= f;
}

bool Circle::contains(const Point& p) const {
    float dist;
    
    dist = sqrtf(powf(p.getX() - x, 2) + powf(p.getY() - y, 2));
    
    return (dist <= radius);
}

// ================= Scene class ===================

Scene::Scene() {
    hasCustomDepth = false;
    
    drawDepth = -1;
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
    int depth = ptr->getDepth();
    
    if (objectList.find(depth) != objectList.end()) {
        objectList[depth].push_back(ptr);
    }
    else {
        objectList[depth] = std::vector<std::shared_ptr<Shape>>(1, ptr);
    }
}

void Scene::setDrawDepth(int depth) {
	if (depth < 0)
        throw std::invalid_argument("Negative depth!");
    
    hasCustomDepth = true;
    
    drawDepth = depth;
}

bool CheckEmpty(const Scene& s, const Point& p) {
   
    for (auto P: s.objectList) {
        for (auto listItem: P.second) {
        
            if (s.hasCustomDepth && s.drawDepth < listItem->getDepth())
                    return false;
        
            if (listItem->contains(p))
                return true;
        }
    }
    
    return false;
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
    for (int a {0}; a < s.HEIGHT; a++) {
        for (int b {0}; b < s.WIDTH; b++) {
            
            Point currentPosition (b, s.HEIGHT - a - 1);
            
            if (CheckEmpty(s, currentPosition))
                out << '*';
            else
                out << ' ';
        }
        out << std::endl;
    }
    
	return out;
}
