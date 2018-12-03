/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include<algorithm>
#include<iostream>
#include"rangetree2d.h"


using namespace std;


vector<Point>  rangetree1d::data;
vector<Point>  rangetree2d::data;

rangetree1d::rangetree1d() :keypos(0), lchild(NULL), rchild(NULL)
{
}

rangetree1d::rangetree1d(const vector<Point>& indata) : lchild(NULL), rchild(NULL)
{
	data = indata;
}

rangetree1d::rangetree1d(size_t pos) : keypos(pos), lchild(NULL), rchild(NULL)
{
}

rangetree1d::rangetree1d(const vector<size_t>& idx) : lchild(NULL), rchild(NULL)
{
	size_t n = idx.size();
	keypos = idx[!(n % 2) ? n / 2 - 1 : (n - 1) / 2];
}

rangetree1d::~rangetree1d()
{
	delete lchild;
	delete rchild;
}

void rangetree1d::sortdata(int d)
{
	switch (d)
	{
	case 1:
		sort(data.begin(), data.end(), xless);
		break;
	case 2:
		sort(data.begin(), data.end(), yless);
		break;
	default:
		cerr << "invalid parameter of function sort()." << endl;
		exit(-1);
	}

}



bool rangetree1d::build(vector<size_t>& idx)
{
	size_t n = idx.size();
	if (n == 0)
		return false;

	size_t pos = !(n % 2) ? n / 2 - 1 : (n - 1) / 2;
	keypos = idx[pos];


	if (n == 1)
	{
		this->lchild = NULL;
		this->rchild = NULL;
	}
	else
	{
		vector<size_t> left, right;
		left.assign(idx.begin(), idx.begin() + pos + 1);
		right.assign(idx.begin() + pos + 1, idx.end());
		this->lchild = new rangetree1d();
		this->rchild = new rangetree1d();

		//		cout<<"\nbuilding left tree"<<endl;
		lchild->build(left);
		//		cout<<"\nbuilding right tree"<<endl;
		rchild->build(right);
	}


	return true;
}

bool rangetree1d::buildtree()
{
	vector<size_t> idx = sort_index(data, yless);
	build(idx);
	return true;
}

void rangetree1d::printtree()
{
	cout << data[keypos] << endl;
	cout << "L";
	if (lchild != NULL)	lchild->printtree();
	cout << "R";
	if (rchild != NULL)    rchild->printtree();


}


template<typename Tree>
Tree* rangetree1d::find_split(Tree* root, Point& low, Point& high, int d)
{
	CompFun less = (d == 1) ? xless : yless;
	Tree* s = root;
	//int h = 0; //height

	//  if low is greater than high, swap them
	if (less(high, low))
	{
		return NULL;
	}

	// query
	while (s != NULL)
	{
		if (less(data[s->keypos], low))
		{
			//			cout<<"\nsplit on right tree."<<endl;
			s = s->rchild;
		}
		else if (less(high, data[s->keypos]))
		{
			//			cout<<"\nsplit on left tree."<<endl;
			s = s->lchild;
		}
		else
		{
			//			cout<<"\ncurrent split.";
			//			s->key.display();
			return s;
		}

	}
	return NULL;
}

void rangetree1d::rangequery(Point from, Point to, vector<Point>& result, int d)
{
	rangetree1d* split = find_split(this,from, to, d);
	if (split == NULL) return;

	if (split->isleaf())  // if split is leaf node, add it to the results
	{
		split->traversal_inorder(result);
		return;
	}

	CompFun less;
	bool ismin, ismax;
	if (d == 1)
	{
		less = xless;
		ismin = from.x <= XMIN;
		ismax = to.x >= XMAX;
	}
	else if (d == 2)
	{
		less = yless;
		ismin = from.y <= YMIN;
		ismax = to.y >= YMAX;
	}

	//query point from
	rangetree1d*  s = split->lchild;
	if (ismin)
		s->traversal_inorder(result);
	else
	{
		while (s != NULL)
		{
			if (!less(data[s->keypos], from))
			{
				if (s->isleaf()) s->traversal_inorder(result);
				else s->rchild->traversal_inorder(result);
				s = s->lchild;
			}
			else
			{
				s = s->rchild;
			}
		}
	}

	//query point to
	s = split->rchild;
	if (ismax)
		s->traversal_inorder(result);
	else
	{
		while (s != NULL)
		{
			if (!less(to, data[s->keypos]))
			{
				if (s->isleaf())  s->traversal_inorder(result);
				else s->lchild->traversal_inorder(result);
				s = s->rchild;
			}
			else
			{
				s =s->lchild;
			}
		}
	}


}

void rangetree1d::traversal_inorder(vector<Point>& result)
{
	rangetree1d* root = this;
	if (root != NULL)
	{
		if (root->isleaf()) result.push_back(data[root->keypos]);
		else
		{
			if (root->lchild != NULL) root->lchild->traversal_inorder(result);
			if (root->rchild != NULL) root->rchild->traversal_inorder(result);
		}
	}
}

bool rangetree1d::isleaf()
{
	return lchild == NULL && rchild == NULL;
}


rangetree2d::rangetree2d() : ytree(NULL)
{
}

rangetree2d::rangetree2d(const vector<Point>& indata) : ytree(NULL)
{
	data = indata;
	rangetree1d::data = indata;
}

rangetree2d::~rangetree2d()
{
	delete lchild;
	delete rchild;
	delete ytree;
}

bool rangetree2d::build(vector<size_t>& idx)
{
	size_t n = idx.size();
	if (n == 0)
		return false;

	size_t pos = !(n % 2) ? n / 2 - 1 : (n - 1) / 2;
	keypos = idx[pos];


	if (n == 1)
	{
		this->lchild = NULL;
		this->rchild = NULL;
	}
	else
	{
		vector<size_t> left, right;
		left.assign(idx.begin(), idx.begin() + pos + 1);
		right.assign(idx.begin() + pos + 1, idx.end());
		this->lchild = new rangetree2d();
		this->rchild = new rangetree2d();

		//		cout<<"\nbuilding left tree"<<endl;
		lchild->build(left);
		//		cout<<"\nbuilding right tree"<<endl;
		rchild->build(right);
	}
		// build y-tree.

			this->ytree = new rangetree1d();
			sort_index(data, idx, yless);
			this->ytree->build(idx);



	return true;
}

bool rangetree2d::buildtree()
{
	vector<size_t> idx = sort_index(data, xless);
	build(idx);
	return true;
}

void  rangetree2d::rangequery(Point from, Point to, vector<Point>& result)
{
	result.clear();
	rangetree2d* split = rangetree1d::find_split(this, from, to, 1);
	if (split == NULL) return;

	if (split->isleaf())  // if split is leaf node, add it to the results
	{
		split->ytree->rangequery(from, to, result, 2);
		return;
	}

	//query point from
	rangetree2d*  s = split->lchild;
	if (from.x <= XMIN)
	{
		s->ytree->rangequery(from, to, result, 2);
	}
	else
	{
		while (s != NULL)
		{
			if (!xless(data[s->keypos], from))
			{
				if (s->isleaf())     // leaf node
				{
					s->ytree->rangequery(from, to, result, 2);
				}
				else
				{
					s->rchild->ytree->rangequery(from, to, result, 2);
				}
				s = (s->lchild);
			}
			else
			{
				s = (s->rchild);
			}
		}
	}

	//query point to
	s = (split->rchild);
	if (to.x >= XMAX)
	{
		s->ytree->rangequery(from, to, result, 2);
	}
	else
	{
		while (s != NULL)
		{
			if (!xless(to, data[s->keypos]))
			{
				if (s->isleaf())  //leaf node
				{
					s->ytree->rangequery(from, to, result, 2);
				}
				else
				{
					s->lchild->ytree->rangequery(from, to, result, 2);
				}

				s = s->rchild;
			}
			else
			{
				s = s->lchild;
			}
		}
	}

}

void rangetree2d::printtree()
{
	cout << data[keypos] << endl;
	cout << "L";
	if (lchild != NULL)	lchild->printtree();
	cout << "R";
	if (rchild != NULL)   rchild->printtree();
	cout << "Y";
	ytree->printtree();

}

bool rangetree2d::isleaf()
{
	return lchild == NULL && rchild == NULL;
}

unsigned long long  rangetree2d::size()
{
	unsigned long long r = sizeof(*this);
	if (lchild != NULL) r += lchild->size();
	if (rchild != NULL) r += rchild->size();
	if (ytree != NULL) r += ytree->size();
	return r;
}

unsigned long long  rangetree1d::size()
{
	unsigned long long r = sizeof(*this);
	if (lchild != NULL) r += lchild->size();
	if (rchild != NULL) r += rchild->size();
	return r;
}
