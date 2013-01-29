#pragma once

class Point
{
public:
	Point();
	~Point(void);

	Point& operator+= (const Point& addPoint);
	Point& operator+ (const Point& addPoint);

	void addToX(float x);
	void addToY(float y);
	void addToZ(float z);

	void floor(void);

	float getMaxValue(void);
	float getMinValue(void);
	float getX(void);
	float getY(void);
	float getZ(void);
	Point getGridCoords(void);
	Point getNormalCoords(void);

	void init(float loc_x, float loc_y, float loc_z = 0.0f, float lowValue = 0.0f, float hiValue = 100.0f);
	
	void setCoordsAsGridCoords(void);
	void setCoords(float loc_x, float loc_y, float loc_z = 0.0f);
	void setMaxValue(float value);
	void setMinValue(float value);
	void setX(float loc_x);
	void setY(float loc_y);
	void setZ(float loc_z);


protected:
	float x;
	float y;
	float z;

private:
	float maxValue;
	float minValue;

	float containCoord(float coord);
	void containCoords(float coords[]);
};