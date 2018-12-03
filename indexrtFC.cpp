/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include<algorithm>
#include "indexrtFC.h"

vector<Point>  indexrtFC::data;

indexrtFC::indexrtFC(void)
{
	size_t n = data.size();

//	for (size_t i = 0; i < n; i++) dataindex[i] = i;
//	iota(dataindex.begin(), dataindex.end(), 0);
	dataindex=sort_index(data, xless);

	keypos = dataindex[!(n % 2) ? (n / 2 - 1) : (n - 1) / 2];
	lindex.resize(n + 1, -1);
	rindex.resize(n + 1, -1);  // an additional size_t to store the end, it would be the size of the subvector.
	lchild = NULL;
	rchild = NULL;
}

indexrtFC::indexrtFC(vector<size_t>& index)
{
	size_t n = index.size();

	dataindex = index;
	keypos = dataindex[!(n % 2) ? (n / 2 - 1) : (n - 1) / 2];
	lindex.resize(n + 1, -1);
	rindex.resize(n + 1, -1);  // an additional size_t to store the end, it would be the size of the subvector.
	lchild = NULL;
	rchild = NULL;
}

indexrtFC::indexrtFC(vector<Point>& indata)
{
	data = indata;
	new(this) indexrtFC();
}



indexrtFC::~indexrtFC(void)
{
	delete lchild;

	delete rchild;

}



bool indexrtFC::buildtree()
{
	size_t n = dataindex.size();
	if (n == 0)
		return false;

	//	cout<<"\ncurrent point:";
	//	key.display();
	//	cout<<endl;
	if (n == 1)
	{
		lchild = NULL;
		rchild = NULL;
	}
	else
	{
		size_t pos = !(n % 2) ? n / 2 - 1 : (n - 1) / 2;
		vector<size_t> left, right;
		left.assign(dataindex.begin(), dataindex.begin() + pos + 1);
		right.assign(dataindex.begin() + pos + 1, dataindex.end());

		//		cout<<"\nbuilding left tree..."<<endl;
		lchild = new indexrtFC(left);
		lchild->buildtree();

		//		cout<<"\nbuilding right tree..."<<endl;
		rchild = new indexrtFC(right);
		rchild->buildtree();

		sort_index(data,dataindex);
		//sort_index(data, left);
		//sort_index(data, right);
		
		fcset(dataindex, lchild->dataindex, lindex, yless);
		fcset(dataindex, rchild->dataindex, rindex, yless);
	}

	return true;
}

void indexrtFC::printtree()
{
	indexrtFC* T = this;
	if (T != NULL)
	{
		cout << "\nkey:";
		data[T->keypos].display();
		cout << "\ndata:";
		for_each(T->dataindex.begin(), T->dataindex.end(), displayint);
		cout << "\nlindex:";
		for_each(T->lindex.begin(), T->lindex.end(), displayint);
		cout << "\nrindex:";
		for_each(T->rindex.begin(), T->rindex.end(), displayint);
		cout << "L";
		T->lchild->printtree();
		cout << "R";
		T->rchild->printtree();
	}
}


//  A2  belong to A1
void indexrtFC::fcset(vector<size_t>& A1, vector<size_t>& A2, vector<size_t>& index, CompFun less)
{
	size_t n1 = A1.size();
	size_t n2 = A2.size();
	size_t i = 0, j = 0;

	for (; j<n2; j++)
	{
		for (; i<n1; i++)
		{
			if (!less(data[A2[j]], data[A1[i]])) index[i] = j;
			else break;
		}
	}

}

void indexrtFC::rangequery(Point& from, Point& to, vector<Point>& result)
{
	result.clear();
	indexrtFC* split = find_split(from, to);
	if (split == NULL) return;

	if (split->isleaf())
	{
        auto sp=data[split->keypos];
        if(sp.y>=from.y && sp.y<=to.y) result.push_back(sp);
//		inserttoresult(split, lowdex, to, result);
		return;
	}

	size_t lowdex; //the interval in split
	lowdex = bsearch(from, split->dataindex);
	if (lowdex == -1) return;
    
	////query point from
	indexrtFC*  s = split->lchild;
	size_t low;  // the lowindex and highindex in subsets
	low = split->lindex[lowdex];

	if (low != -1)
	{
		if (from.x <= XMIN)
		{
			inserttoresult(s, low, to, result);
		}
		else
		{
			while (s != NULL)
			{
				if (!xless(data[s->keypos], from))
				{
					if (s->lchild == NULL && s->rchild == NULL)
						inserttoresult(s, low, to, result);
					else
					{
						inserttoresult(s->rchild, s->rindex[low], to, result);
					}

					low = s->lindex[low];
					if (low == -1) break;
					s = s->lchild;
				}
				else
				{
					low = s->rindex[low];
					if (low == -1) break;
					s = s->rchild;
				}
			}
		}
	}

	//query point to
	s = split->rchild;
	//	indextransfer(split->rindex,lowdex,hidex,low,high);
	low = split->rindex[lowdex];
	if (low != -1)
	{
		if (to.x >= XMAX)
		{
			inserttoresult(s, low, to, result);
		}
		else
		{
			while (s != NULL)
			{
				if (!xless(to, data[s->keypos]))
				{
					if (s->lchild == NULL && s->rchild == NULL)
					{
						inserttoresult(s, low, to, result);
					}
					else
					{
						inserttoresult(s->lchild, s->lindex[low], to, result);

					}

					low = s->rindex[low];
					if (low == -1) break;
					s = s->rchild;
				}
				else
				{
					low = s->lindex[low];
					if (low == -1) break;
					s = s->lchild;
				}
			}
		}
	}
}

indexrtFC* indexrtFC::find_split(Point& low, Point& high)
{
	//  if low is greater than high, swap them
	if (xless(high, low) || yless(high, low))
	{
		return NULL;
	}

	// query
	indexrtFC* s = this;
	while (s != NULL)
	{
		if (xless(data[s->keypos], low))
		{
			s = s->rchild;
		}
		else if (xless(high, data[s->keypos]))
		{
			s = s->lchild;
		}
		else
		{
			return s;
		}
	}
	return NULL;
}

// interval query from the current node, lo and hi is the index
void indexrtFC::intervalquery(vector<Point>& data, Point from, Point to, size_t& lo, size_t& hi)
{
	//  if low is greater than high, swap them
	if (yless(to, from))
	{
		Point temp = from;
		from = to;
		to = temp;
	}

//	lo = bsearch(from, data);
//	hi = bsearch(to, data);


	//if (lo==-1)   // the from position exceeds the end
	//{
	//	hi=-1;
	//	return;
	//}
	//size_t n=data.size();
	//size_t i=lo;
	//for(;i<n && !yless(to,data[i]);i++);

	//hi=i; // if hi<lo, the to position prior to the begin.


}

// return the first position where the value is not less than the given point P. 
size_t indexrtFC::bsearch(Point& P, vector<size_t>& V)
{
	// binary search
	size_t n=V.size();
	size_t l = 0;
	size_t h = n - 1;
	size_t m = h;
	while (int(l) <= int(h)) {
//		Point tl=data[V[l]];
//		Point th = data[V[h]];
//
//		if (P.y < tl.y) return l;
//		if (th.y < P.y)  return h + 1;
//		if (tl.y == th.y) return l;
//
//		m= l+ (P.y- tl.y)*(h-l) /(th.y- tl.y);
		m = (l+h)/2;
		Point tm = data[V[m]];

		if (tm.y == P.y)
		{
            int i;
			for (i = m; int(i) >= 0; i--)    //  in case of some equal elements
			{
				if (data[V[i]].y != P.y) break;
			}
			return i + 1;
		}
		if (P.y < tm.y) h = m - 1;
		else l = m + 1;
	}
	if (h == m - 1) return m;
	else return m + 1<n ? m + 1 : -1;    // if the position exceeds, return -1.
}

void indexrtFC::inserttoresult(indexrtFC* datanode, size_t lo, Point& to, vector<Point>& result)
{

	if (datanode == NULL) return;
	if (lo == -1) return;

	vector<size_t>& V = datanode->dataindex;
	size_t i, n = V.size();


	//if (hi==-1) 
	//{
	//	result.insert(result.end(),V.begin()+lo, V.end());
	//	return;
	//}
	//if(to.y>=V[hi].y)
	//{
	//size_t i=hi;
	//for(; i<n && V[i].y==V[hi].y;i++);
	//hi=i;
	//}
	//result.insert(result.end(),V.begin()+lo, V.begin()+hi);

	//	if (hi==-1)  hi=n;


	//for(i=lo;i<hi;i++)
	//{
	//	result.push_back(V[i]);
	//} 

	for (i = lo; i<n && !yless(to, data[V[i]]); i++)
	{
		result.push_back(data[V[i]]);
	}


}

bool indexrtFC::isleaf()
{
	if (lchild == NULL && rchild == NULL) return true;

	return false;
}

void indexrtFC::indextransfer(vector<size_t>& index, size_t low, size_t high, size_t& newlow, size_t& newhigh)
{
	if (low == -1)
	{
		newlow = -1;
		return;
	}

	newlow = index[low];
	newhigh = (high == -1) ? -1 : index[high];


}

unsigned long long  indexrtFC::size()
{
	unsigned long long r = sizeof(*this);
	if (lchild != NULL) r += lchild->size();
	if (rchild != NULL) r += rchild->size();
	r += (lindex.capacity() + rindex.capacity() + dataindex.capacity()) * sizeof(size_t);
	return r;
}
