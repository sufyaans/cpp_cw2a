#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <iostream>
#include <memory>


class Point; // forward declaration

class Shape {

public:
	// Default constructor, just to make this release version compilable.
	// If your implementation is correct this should be removed
	Shape();

	// Constructor specifying the depth of the object.
	// If d is negative, throw a std::invalid_argument exception.
	Shape(int d);

	// Set depth of object to d. If d is negative, return false and
	// do not update depth. Otherwise return true
	bool setDepth(int d);

	// Return the depth of object
	int getDepth() const;

	// Return the dimension of the object (0, 1 or 2)
	//int dim() const;
    
    // Get object dimension
	virtual int  dim() const = 0;

	// Translate the object horizontally by x and vertically by y
	//void translate(float x, float y);

    // Translate the object by x and y
	virtual void translate(float x, float y) = 0;

	// Rotate the object 90 degrees around its centre
	virtual void rotate() = 0;  

	// Scale the object by a factor f relative to its centre.
	// If f is zero or negative, throw a std::invalid-argument exception.
	virtual void scale(float f) = 0;

	// Return true if the object contains p and false otherwise.
	// Depths are ignored for purpose of comparison
	virtual bool contains(const Point& p) const = 0; 

	// the constant pi
	static constexpr double PI = 3.1415926;

protected:
private:
	// add any protected/private member variables you need

    //Object depth
    int depth;
};



class Point : public Shape {

public:
	// Constructor. Depth defaults to 0
	Point(float x, float y, int d=0);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;

    // Override
    //SetDepth n GetDepth
    int  dim() const override;
    void translate(float x, float y) override;
    void rotate() override;
    void scale(float f) override;
    bool contains(const Point& p) const override;

private:
	// add any member variables you need
    
    // Coordinates of the point
    float distX, distY;
};

class LineSegment : public Shape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x- and
	// y-coordinate, or if the line is not axis-aligned, throw a
	// std::invalid_argument exception
	LineSegment(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;

	// Return the length of the line segment
	float length() const;

    // Override
    int  dim() const override;
    void translate(float x, float y) override;
    void rotate() override;
    void scale(float f) override;
    bool contains(const Point& p) const override;

private:
	// add any member variables you need

    // End-points coordinates
    float x1, y1 , x2, y2;
};



// Abstract class
class TwoDShape : public Shape {

public:
	TwoDShape(int d);

    // All 2DShapes are 2 dimensioned, So, no further inheritance required.
	int dim() const override final;
    
    // Both rectangle and circle has an area attribute, hence area() declared as virtual to be overriden.
    virtual float area() const = 0;
};


class Rectangle : public TwoDShape {

public:
	Rectangle(const Point& p, const Point& q);

	// Get corner coordinates
	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;

    // Overrides
    void  translate(float x, float y) override;
    void  rotate() override;
    void  scale(float f) override;
    bool  contains(const Point& p) const override;
    float area() const override;

private:
    float x1, y1, x2, y2, x3, y3, x4, y4;

    float *xCoorArray[4] = { &x1, &x2, &x3, &x4 }, *yCoorArray[4] = { &y1, &y2, &y3, &y4 };
};


class Circle : public TwoDShape {

public:
	// Constructor.
	// If r is zero or negative, throw a std::invalid-argument exception.
	Circle(const Point& c, float r);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	float getR() const;

    //Overrides
    void  translate(float x, float y) override;
    void  rotate() override;
    void  scale(float f) override;
    bool  contains(const Point& p) const override;
	float area() const override;

private:
	// add any member variables you need
    float x, y, radius;
};


class Scene {

public:
	// Constructor
	Scene();

	// Add the pointer to the collection of pointers stored
	void addObject(std::shared_ptr<Shape> ptr);

	// Set the drawing depth to d
	void setDrawDepth(int d);

	// Constants specifying the size of the drawing area
	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;

private:
	// add any member variables you need

	// Draw objects as specified in the assignment page
friend std::ostream& operator<<(std::ostream& out, const Scene& s);
};

#endif /* GEOMETRY_H_ */