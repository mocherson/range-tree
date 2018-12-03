/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once
#include<string>
#include"point.h"

class Interval:public Point
{
public:
	Interval(void);
	Interval(double i) ;
	Interval(double a, double b);
	Interval(Point Po);
public:
	~Interval(void);
//public:
//	double x;  // the begin point
//	double y;  // the end point

public:
	//void put_value(double x_, double y_);
	void put_value(Point Po);
	void transform(string op, Point& from, Point& to);  //transform the interval query to point query using range tree
	 bool operator< (const Interval& I );
	 bool operator> (const Interval& I);
};
