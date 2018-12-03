/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include<algorithm>
#include<iostream>
#include"rangetree.h"


using namespace std;

int rangetree::dim=1;
vector<Point>  rangetree::data;

rangetree::rangetree():lchild(NULL),rchild(NULL),yroot(NULL)
{
	vector<size_t> idx = sort_index(data,xless);
	size_t n = idx.size();
	keypos = idx[!(n % 2) ? n / 2 - 1 : (n - 1) / 2];
}

rangetree::rangetree(vector<Point>& indata) : lchild(NULL), rchild(NULL), yroot(NULL)
{
	data=indata;
	new(this) rangetree();
}

rangetree::rangetree(size_t pos) : keypos(pos), lchild(NULL), rchild(NULL), yroot(NULL)
{
}

rangetree::rangetree(vector<size_t>& idx, int di) : lchild(NULL), rchild(NULL), yroot(NULL)
{
	if (di==1 )
	{		
		sort_index(data,idx,xless);
	}
	else if (di==2)
	{
		sort_index(data, idx, yless);
	}
	size_t n = idx.size();
	keypos=idx[!(n % 2) ? n / 2 - 1 : (n - 1) / 2];
}

rangetree::~rangetree()
{
	delete lchild;
	delete rchild;
	if(yroot!=this) delete yroot;
}

void rangetree::sortdata(int d)
{
	switch (d)
	{
	case 1:
		sort(data.begin(),data.end(),xless);
		break;
	case 2:
		sort(data.begin(),data.end(),yless);
		break;
	default:
		cerr<<"invalid parameter of function sort()."<<endl;
		exit(-1);
	}

}



bool rangetree::build(vector<size_t>& idx)
{

	size_t n=idx.size();
	if (n==0)
		return false;

	size_t pos = !(n % 2) ? n / 2 - 1 : (n - 1) / 2;
//	cout<<"current node:";
//	p->key.display();

	if(n==1)
	{
		this->lchild=NULL;
		this->rchild=NULL;
		this->yroot=this;
	}
	else
	{
		vector<size_t> left,right;
		left.assign(idx.begin(),idx.begin()+pos+1);
		right.assign(idx.begin()+pos+1,idx.end());
		this->lchild= new rangetree(left,dim);
		this->rchild= new rangetree(right,dim);

//		cout<<"\nbuilding left tree"<<endl;
		this->lchild->build(left);
//		cout<<"\nbuilding right tree"<<endl;
		this->rchild->build(right);
		
		// if in the first dimension, build y-tree.
		if (dim==1)
		{
			dim++;
			this->yroot= new rangetree(idx,dim);
//			cout<<"\nbuilding ytree"<<endl;
			this->yroot->build(idx);
			dim--;
		}
	}

	return true;
}

bool rangetree::buildtree()
{
char a;
	vector<size_t> idx = sort_index(data, xless);
	build(idx);
	return true;
}

void rangetree::printtree()
{
		cout<<data[keypos]<<endl;
		cout<<"L";
		if (lchild!=NULL)	lchild->printtree();
		cout<<"R";
		if(rchild!=NULL)    rchild->printtree();


}

void  rangetree::rangequery(Point from, Point to, vector<Point>& result)
{
	result.clear();
	rangetree* split = find_split(from,to,1);
	if (split==NULL) return;

	if (split->isleaf())  // if split is leaf node, add it to the results
	{
		split->yroot->intervalquery(from,to,result,2);
		return;
	}

	//query point from
	rangetree*  s=split->lchild;
	if(from.x<=XMIN) 
	{
		s->yroot->intervalquery(from,to, result,  2);
	}
	else
	{
		while( s!=NULL )
		{
			if( !xless(data[s->keypos],from) )
			{
				if(s->isleaf())     // leaf node
				{
					s->yroot->intervalquery(from,to,result, 2);
				}
				else
				{
					s->rchild->yroot->intervalquery(from,to,result, 2);
				}
				s=s->lchild;
			}
			else
			{
				s=s->rchild;
			}
		}
	}

	//query point to
	s=split->rchild;
	if (to.x>=XMAX) 
	{
		s->yroot->intervalquery(from,to, result,  2);
	}
	else
	{
		while( s!=NULL )
		{
			if( !xless(to,data[s->keypos]) )
			{
				if(s->isleaf())  //leaf node
				{
					s->yroot->intervalquery(from,to,result, 2);
				}
				else
				{
					s->lchild->yroot->intervalquery(from,to,result, 2);
				}

				s=s->rchild;
			}
			else
			{
				s=s->lchild;
			}
		}
	}


}

rangetree* rangetree::find_split(Point& low, Point& high, int d) 
{	
	CompFun less = (d==1) ? xless : yless;
	rangetree* s=this;
	

	//  if low is greater than high, swap them
	if ( less(high,low))
	{
		return NULL;
	}

	// query
	while (s!=NULL)
	{
		if( less(data[s->keypos],low) )
		{
			//			cout<<"\nsplit on right tree."<<endl;
			s=s->rchild;
		}
		else if ( less(high,data[s->keypos]) )
		{
			//			cout<<"\nsplit on left tree."<<endl;
			s=s->lchild;
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

void rangetree::intervalquery(Point from, Point to, vector<Point>& result, int d)
{
	rangetree* split = find_split(from,to,d);
	if (split==NULL) return;

	if (split->isleaf())  // if split is leaf node, add it to the results
	{
		split->traversal_inorder(result);
		return;
	}

	CompFun less;
	bool ismin,ismax;
	if(d==1)
	{
		less=xless;
		ismin = from.x<=XMIN;
		ismax = to.x>=XMAX;
	}
	else if(d==2)
	{
		less=yless;
		ismin = from.y<=YMIN;
		ismax = to.y>=YMAX;
	}

	//query point from
	rangetree*  s=split->lchild;
	if(ismin) 
		s->traversal_inorder( result);
	else
	{
		while( s!=NULL )
		{
			if( !less(data[s->keypos],from) )
			{
				if(s->isleaf()) s->traversal_inorder(result);
				else s->rchild->traversal_inorder( result);
				s=s->lchild;
			}
			else
			{
				s=s->rchild;
			}
		}
	}

	//query point to
	s=split->rchild;
	if (ismax) 
		s->traversal_inorder( result);
	else
	{
		while( s!=NULL )
		{
			if( !less(to,data[s->keypos]) )
			{
				if(s->isleaf())  s->traversal_inorder(result);
				else s->lchild->traversal_inorder( result);
				s=s->rchild;
			}
			else
			{
				s=s->lchild;
			}
		}
	}

}

void rangetree::traversal_inorder(vector<Point>& result)
{
	rangetree* root = this;
	if(root!=NULL)
	{
	    if(root->isleaf()) result.push_back(data[root->keypos]);
	    else
	    {
		if(root->lchild!=NULL) root->lchild->traversal_inorder(result);
		if(root->rchild!=NULL) root->rchild->traversal_inorder(result);
		}
	}

}

bool rangetree::isleaf()
{
	return lchild == NULL && rchild == NULL;
}
