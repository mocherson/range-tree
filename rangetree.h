/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once

#include<vector>
#include"point.h"

class rangetree
{
public:
	size_t keypos;
	rangetree* lchild;
	rangetree* rchild;
	rangetree* yroot;
	static int dim;
	static vector<Point>  data;
	vector<size_t> idx;

public:
	rangetree();
	rangetree(vector<Point>& indata);
	rangetree(size_t pos);
	rangetree(vector<size_t>& idx, int d);
	~rangetree();


public:
	bool buildtree();
	bool build(vector<size_t>& idx);
	void sortdata(int d);
	void rangequery(Point from, Point to, vector<Point>& result);
	rangetree* find_split(Point& low, Point& high, int d);
	void intervalquery(Point from, Point to, vector<Point>& result, int d);
	void traversal_inorder( vector<Point>& result);
	void printtree();
	bool isleaf();



};

