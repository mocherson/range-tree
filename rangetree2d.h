/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once

#include<vector>
#include"point.h"

class rangetree1d
{
public:
	size_t keypos;
	rangetree1d* lchild;
	rangetree1d* rchild;

	static vector<Point>  data;



public:
	rangetree1d();
	rangetree1d(const vector<Point>& indata);
	rangetree1d(size_t pos);
	rangetree1d(const vector<size_t>& idx);
	~rangetree1d();


public:
	bool buildtree();
	bool build(vector<size_t>& idx);
	void sortdata(int d);
//	void rangequery(Point from, Point to, vector<Point>& result);
	template<typename Tree>
	static Tree* find_split(Tree* root, Point& low, Point& high, int d);
	void rangequery(Point from, Point to, vector<Point>& result, int d);
	void traversal_inorder(vector<Point>& result);
	void printtree();
	bool isleaf();
    unsigned long long size();


};

class rangetree2d
{
public:
	size_t keypos;
	rangetree2d* lchild;
	rangetree2d* rchild;
	rangetree1d* ytree;
	static vector<Point>  data;

public:
	rangetree2d();
	rangetree2d(const vector<Point>& indata);
	~rangetree2d();

	bool buildtree();
	bool build(vector<size_t>& idx);
	void printtree();
	void rangequery(Point from, Point to, vector<Point>& result);
	bool isleaf();
	unsigned long long size();
};
