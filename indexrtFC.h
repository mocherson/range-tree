/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once
#include<vector>
#include "point.h"

class indexrtFC
{
	// constructor
public:
	indexrtFC(void);
	indexrtFC(vector<size_t>& index);
	indexrtFC(vector<Point>& indata);
	//destructor 
public:
	~indexrtFC(void);
	// member variable
public:
	size_t keypos;

	indexrtFC* lchild;
	indexrtFC* rchild;
	vector<size_t> lindex;   // data index in the left child data
	vector<size_t> rindex;   // data index in the righ child data
	vector<size_t> dataindex;   //the difference to rangetreeFC,  y order index

	static	vector<Point>  data;  //
	// member function
public:
//	void sortdata(int d);
//	size_t getsize();
	bool buildtree();
	void rangequery(Point& from, Point& to, vector<Point>& result);
	indexrtFC* find_split(Point& low, Point& high);
	void printtree();
	static void fcset(vector<size_t>& A1, vector<size_t>& A2, vector<size_t>& index, CompFun less);   // set the index for fractional cascading
	static void intervalquery(vector<Point>& data, Point from, Point to, size_t& lo, size_t& hi);  // interval query from the current node
	static size_t bsearch(Point& P, vector<size_t>& V);
//	static void inserttoresult(indexrtFC* datanode, size_t lo, size_t hi, vector<Point>& result);
	static void inserttoresult(indexrtFC* datanode, size_t lo, Point& to, vector<Point>& result);
	bool isleaf();  //whether this node is a leaf node
	static void indextransfer(vector<size_t>& index, size_t low, size_t high, size_t& newlow, size_t& newhigh);
	unsigned long long size();
//	vector<Point> indextodata(vector<size_t> index);
	 
};

