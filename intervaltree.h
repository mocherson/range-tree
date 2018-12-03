/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#pragma once

#include <vector>
#include "RBtree.h"
#include "interval.h"

using namespace std;

struct extinfo
{
	vector<Interval> equkey;  // interval with equal begins.
	double maxvalue;     // the max value in the subtree.

	extinfo() 
	{
		equkey.clear();
		maxvalue = 0;
	}
};

class intervaltree: public RB_Tree<double,extinfo>
{
public:
	void Insert(Interval interv);
	void InsertFixUp(RB_Node* node);
	void buildtree(vector<Interval>& data);
	void buildtree(vector<Point>& data);
	void printtree(RB_Node* node);
	void printtree();
	unsigned long long  size(RB_Node* node);
	bool RotateLeft(RB_Node* node);
	bool RotateRight(RB_Node* node);
	void InOrderTraverse(RB_Node* node, vector<Interval>& result);
	void search_o(RB_Node* node, Interval i, vector<Interval>& result);
	void search_oi(RB_Node* node, Interval i, vector<Interval>& result);
	void search_d(RB_Node* node, Interval i, vector<Interval>& result);
	void search_di(RB_Node* node, Interval i, vector<Interval>& result);
	void search_p(RB_Node* node, Interval i, vector<Interval>& result);
	void search_pi(RB_Node* node, Interval i, vector<Interval>& result);
	void search_s(RB_Node* node, Interval i, vector<Interval>& result);
	void search_si(RB_Node* node, Interval i, vector<Interval>& result);
	void search_f(RB_Node* node, Interval i, vector<Interval>& result);
	void search_fi(RB_Node* node, Interval i, vector<Interval>& result);
	void search_m(RB_Node* node, Interval i, vector<Interval>& result);
	void search_mi(RB_Node* node, Interval i, vector<Interval>& result);
	void search_e(RB_Node* node, Interval i, vector<Interval>& result);
};
