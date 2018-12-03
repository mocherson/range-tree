/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once
#include<vector>
#include "point.h"

class rangetreeFC
{
// constructor
public:
	rangetreeFC(void);
	rangetreeFC(vector<Point>& indata );
//destructor 
public:
	~rangetreeFC(void);
// member variable
public:
	Point key;
	vector<Point>  data;
	rangetreeFC* lchild;
	rangetreeFC* rchild;
	vector<size_t> lindex;   // data index in the left child data
	vector<size_t> rindex;   // data index in the righ child data
// member function
public:
	void sortdata(int d);
	size_t getsize();
	bool buildtree();
	void rangequery(Point from, Point to, vector<Point>& result);
	static rangetreeFC* find_split(Point& low, Point& high, rangetreeFC* node ); 
	void printtree();
	static void fcset(vector<Point>& A1, vector<Point>& A2, vector<size_t>& index,  CompFun less);   // set the index for fractional cascading
	static void intervalquery(vector<Point>& data,  Point from, Point to, size_t& lo, size_t& hi);  // interval query from the current node
	static size_t bsearch(Point P, vector<Point>& V);
	static void inserttoresult(rangetreeFC* datanode, size_t lo,size_t hi, vector<Point>& result);
	static void inserttoresult(rangetreeFC* datanode, size_t lo, Point to, vector<Point>& result);
	bool isleaf();  //whether this node is a leaf node
	static void indextransfer(vector<size_t>& index, size_t low, size_t high, size_t& newlow, size_t& newhigh);
};
