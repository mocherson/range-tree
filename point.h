/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once

#include<iostream>
#include<vector>
#include <fstream>
#include<string>
#include<float.h>
#include<algorithm>
#include<numeric>  //std::iota

#define XMIN 0
#define XMAX DBL_MAX
#define YMIN 0
#define YMAX DBL_MAX



using namespace std;

class Point
{
public:
	double x;  // x-coordinate
	double y;  // y-coordinate

public:

	Point() : x(0), y(0) { }

	Point(double i) : x(i), y(i) { }

	Point(double a, double b): x(a),y(b){}

	~Point() {  }

	void put_value(double x_, double y_) 
	{
		x = x_; 
		y = y_;
	}

	double get_value(int d) 
	{
		switch (d){
		  case 1: return x; break;
		  case 2: return y; break;
		  default: return -1;
		}
	}

	void  display()
	{
		cout<<"("<<x<<","<<y<<")";
	}

	friend ostream& operator << (ostream& output, Point& P)
	{
		output << "(" << P.x << "," << P.y << ")";
		return output;
	}

	bool operator==(const Point& P ) const
	{
		return this->y==P.y;
	}

	bool operator<(const Point& P) const
	{
		return this->y < P.y;
	}


	static void rangequery(vector<Point>& data, Point from, Point to, vector<Point>& result )
	{
		result.clear();
		size_t i, n=data.size();
		for(i=0;i<n;i++)
		{
			if(data[i].x>=from.x && data[i].x<=to.x && data[i].y>=from.y && data[i].y<=to.y)
				result.push_back(data[i]);
		}
	}
};


static void display(Point& p)
{
	p.display();
}

static void displayint(size_t p)
{

	cout<<p<<",";
}




static bool xless(const Point& l, const Point& r) 
{
	return l.x < r.x;
}

static bool yless(const Point& l, const Point& r) 
{
	return l.y < r.y;
}

static bool xequal(const Point& l, const Point& r) 
{
	return l.x == r.x;
}

static bool yequal(const Point& l, const Point& r) 
{
	return l.y == r.y;
}

typedef bool (*CompFun)(const Point&, const Point&);


static bool issorted(const vector<Point>& V, CompFun comp)
{
	int i;
//	cout<<int(V.size()-1)<<endl;
	for(i=0; i< int(V.size()-1) ;i++)
	{
		if( comp(V[i+1],V[i]) )  return false;
	}
	return true;
}

static vector<Point> readfile(const string& filename)
{
	vector<Point> origin;
	ifstream indata; 

	indata.open(filename.data()); // opens the file
		if(!indata) 
		{ // file couldn't be opened
			cerr << "Error: file " << filename << " could not be opened" << endl;
			exit(1);
		}
		cout<<"file "<<filename<<" is opened."<<endl; 


	double xin,yin;
	Point t;
	while ( indata >>xin>>yin ){
		t.put_value(xin, yin);
        origin.push_back(t);
    };
    indata.close();
	return origin;
}

/*
struct node
{
	Point key;
	size_t index;
	bool operator<(const node& K)
	{
		return yless(key, K.key);
	}
};
static vector<size_t> sort_index(const vector<Point>& data)
{	
	size_t n = data.size();
	vector<node> consdata(n);
	for (size_t i = 0; i < n; i++)
	{
		consdata[i].key = data[i];
		consdata[i].index = i;
	}
	sort(consdata.begin(), consdata.end());

	vector<size_t> outindex(n);
	for (size_t i = 0; i < n; i++)
	{
		outindex[i] = consdata[i].index;
	}
	return outindex;
}

static vector<size_t> sort_index(const vector<Point>& data, const vector<size_t>& index)
{
	size_t n = index.size();
	vector<node> consdata(n);
	for (size_t i = 0; i < n; i++)
	{
		consdata[i].key = data[index[i]];
		consdata[i].index = index[i];
	}
	sort(consdata.begin(), consdata.end());

	vector<size_t> outindex(n);
	for (size_t i = 0; i < n; i++)
	{
		outindex[i] = consdata[i].index;
	}
	return outindex;
}
*/

template <typename T>
vector<size_t> sort_index(const vector<T> &v, bool (*comp)(const T&,const T&)) {

	// initialize original index locations
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);
//    for(int i=0;i<v.size();i++)  idx[i]=i;


	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),[&v,&comp](size_t i1, size_t i2) {return (*comp)(v[i1] , v[i2]); });

	return idx;
}

template <typename T>
vector<size_t> sort_index(const vector<T> &v,  vector<size_t>& idx) {
	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

template <typename T>
vector<size_t> sort_index(const vector<T> &v, vector<size_t>& idx, bool(*comp)(const T&, const T&)) {
	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(), [&v,&comp](size_t i1, size_t i2) {return (*comp)(v[i1], v[i2]); });

	return idx;
}

