/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include "interval.h"
using namespace std;


Interval::Interval()
{ }

Interval::Interval(double i) : Point(i) 
{ }

Interval::Interval(double a, double b): Point(a,b)
{}

Interval::Interval(Point Po)
{
	x=Po.x;
	y=Po.y;
}

Interval::~Interval() {}

//void Interval::put_value(double x_, double y_) 
//{
//	x = x_; 
//	y = y_;
//}

void Interval::put_value(Point Po) 
{
	x=Po.x;
	y=Po.y;
}




void Interval::transform(string op, Point& from, Point& to)
{
	if(op=="o") { from.put_value(XMIN,x+0.5);  to.put_value(x-0.5,y-0.5); return; }          //    0<x'<x,  x<y'<y
	else if(op=="oi")  { from.put_value(x+0.5,y+0.5);  to.put_value(y-0.5,XMAX); return; }   //    
	else if(op=="d")   { from.put_value(x+0.5,x+0.5);  to.put_value(y-0.5,y-0.5); return; }
	else if(op=="di")  { from.put_value(XMIN,y+0.5);  to.put_value(x-0.5,XMAX); return; }
	else if(op=="m")   { from.put_value(XMIN,x);  to.put_value(x,x); return; }
	else if(op=="mi")  { from.put_value(y,y);  to.put_value(y,XMAX); return; }
	else if(op=="s")   { from.put_value(x,x);  to.put_value(x,y-0.5); return; }
	else if(op=="si")  { from.put_value(x,y+0.5);  to.put_value(x,XMAX); return; }
	else if(op=="f")   { from.put_value(x+0.5,y);  to.put_value(y,y); return; }
	else if(op=="fi")  { from.put_value(XMIN,y);  to.put_value(x-0.5,y); return; }
	else if(op=="<"||op=="p")   { from.put_value(XMIN,XMIN);  to.put_value(x-0.5,x-0.5); return; }
	else if(op==">"||op=="pi")   { from.put_value(y+0.5,y+0.5);  to.put_value(XMAX,XMAX); return; }
	else if(op=="="||op=="e")   { from.put_value(x,y);  to.put_value(x,y); return; }
	else{ cout<<"invalid relation"<<endl; }
}

bool Interval::operator< (const Interval& I)
{
	return x<I.x;
}

bool Interval::operator> (const Interval& I)
{
	return x>I.x;
}
