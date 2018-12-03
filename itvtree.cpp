/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include "itvtree.h"



itvtree::itvtree()
{
}


itvtree::~itvtree()
{
}

void itvtree::Insert(Interval interv)
{
	double key = interv.x;
	RB_Node* insert_point = m_nullNode;
	RB_Node* index = m_root;
	while (index != m_nullNode)
	{
		insert_point = index;
		if (index->data.maxvalue < interv.y)
		{
			index->data.maxvalue = interv.y;
		}
		if (key<index->key)
		{
			index = index->left;
		}
		else
		{
			index = index->right;
		}
	}
	RB_Node* insert_node = new RB_Node();
	insert_node->key = key;
	insert_node->data.itv=interv;
	insert_node->data.maxvalue = interv.y;
	insert_node->RB_COLOR = RED;
	insert_node->right = m_nullNode;
	insert_node->left = m_nullNode;
	insert_node->parent = insert_point;
	if (insert_point == m_nullNode) //Èç¹û²åÈëµÄÊÇÒ»¿Å¿ÕÊ÷
	{
		m_root = insert_node;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		m_nullNode->parent = m_root;
	}
	else
	{
		if (key<insert_point->key)
		{
			insert_point->left = insert_node;
		}
		else
		{
			insert_point->right = insert_node;
		}
	}
	InsertFixUp(insert_node);    //µ÷ÓÃInsertFixUpÐÞ¸´ºìºÚÊ÷ÐÔÖÊ¡£
}

void itvtree::InsertFixUp(RB_Node* node)
{
	while (node->parent->RB_COLOR == RED)
	{
		if (node->parent == node->parent->parent->left)   //
		{
			RB_Node* uncle = node->parent->parent->right;
			if (uncle->RB_COLOR == RED)   //²åÈëÇé¿ö1£¬zµÄÊåÊåyÊÇºìÉ«µÄ¡£
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)  //²åÈëÇé¿ö2£ºzµÄÊåÊåyÊÇºÚÉ«µÄ£¬¡£
			{
				if (node == node->parent->right) //ÇÒzÊÇÓÒº¢×Ó
				{
					node = node->parent;
					RotateLeft(node);
				}
				else                 //²åÈëÇé¿ö3£ºzµÄÊåÊåyÊÇºÚÉ«µÄ£¬µ«zÊÇ×óº¢×Ó¡£
				{
					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateRight(node->parent->parent);
				}
			}
		}
		else //Õâ²¿·ÖÊÇÕë¶ÔÎª²åÈëÇé¿ö1ÖÐ£¬zµÄ¸¸Ç×ÏÖÔÚ×÷Îª×æ¸¸µÄÓÒº¢×ÓÁËµÄÇé¿ö£¬¶øÐ´µÄ¡£
			 //15 else (same as then clause with "right" and "left" exchanged)
		{
			RB_Node* uncle = node->parent->parent->left;
			if (uncle->RB_COLOR == RED)
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				uncle->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);     //ÓëÉÏÊö´úÂëÏà±È£¬×óÐý¸ÄÎªÓÒÐý
				}
				else
				{
					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateLeft(node->parent->parent);   //ÓÒÐý¸ÄÎª×óÐý£¬¼´¿É¡£
				}
			}
		}
	}
	m_root->RB_COLOR = BLACK;
}

void itvtree::buildtree(vector<Interval>& data)
{
	for (size_t i = 0; i < data.size(); i++)
		Insert(data[i]);
}

void itvtree::buildtree(vector<Point>& data)
{
	for (size_t i = 0; i < data.size(); i++)
		Insert(Interval(data[i]));
}

void itvtree::printtree(RB_Node* node)
{
	if (node != m_nullNode)
	{
		node->data.itv.display();
		cout << "color" << node->RB_COLOR << "  max" << node->data.maxvalue << endl;
		cout << "L";
		printtree(node->left);
		cout << "R";
		printtree(node->right);
	}
	else
	{
		cout << "leaf" << endl;
	}
}

void itvtree::printtree()
{
	printtree(m_root);
}

bool itvtree::RotateLeft(RB_Node* node)
{
	if (node == m_nullNode || node->right == m_nullNode)
	{
		return false;//can't rotate
	}
	RB_Node* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != m_nullNode)
	{
		lower_right->left->parent = node;
	}
	if (node->parent == m_nullNode) //rotate node is root
	{
		m_root = lower_right;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		//m_nullNode->parent = m_root;
	}
	else
	{
		if (node == node->parent->left)
		{
			node->parent->left = lower_right;
		}
		else
		{
			node->parent->right = lower_right;
		}
	}
	node->parent = lower_right;
	lower_right->left = node;

	lower_right->data.maxvalue = node->data.maxvalue;
	node->data.maxvalue = max(max(node->left->data.maxvalue, node->right->data.maxvalue), node->data.itv.y);
	return true;
}

bool itvtree::RotateRight(RB_Node* node)
{
	if (node == m_nullNode || node->left == m_nullNode)
	{
		return false;//can't rotate
	}
	RB_Node* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != m_nullNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == m_nullNode) //node is root
	{
		m_root = lower_left;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		//m_nullNode->parent = m_root;
	}
	else
	{
		if (node == node->parent->right)
		{
			node->parent->right = lower_left;
		}
		else
		{
			node->parent->left = lower_left;
		}
	}
	node->parent = lower_left;
	lower_left->right = node;

	lower_left->data.maxvalue = node->data.maxvalue;
	node->data.maxvalue = max(max(node->left->data.maxvalue, node->right->data.maxvalue), node->data.itv.y);
	return true;
}

void itvtree::InOrderTraverse(RB_Node* node, vector<Interval>& result)
{
	if (node == m_nullNode)
	{
		return;
	}

	InOrderTraverse(node->left, result);
	result.push_back(node->data.itv);
	InOrderTraverse(node->right, result);

}

void itvtree::search_o(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue <= i.x) return;

	if (node->key >= i.x)
	{
		search_o(node->left, i, result);
		return;
	}

	if (node->data.itv.y > i.x && node->data.itv.y < i.y)
		result.push_back(node->data.itv);

	search_o(node->left, i, result);
	search_o(node->right, i, result);
}

void itvtree::search_oi(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue <= i.y) return;

	if (node->key <= i.x)
	{
		search_oi(node->right, i, result);
		return;
	}
	if (node->key >= i.y)
	{
		search_oi(node->left, i, result);
		return;
	}

	if ( node->data.itv.y > i.y)
		result.push_back(node->data.itv);

	search_oi(node->left, i, result);
	search_oi(node->right, i, result);
}

void itvtree::search_d(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue <= i.x) return;
	if (node->key <= i.x)
	{
		search_d(node->right, i, result);
		return;
	}
	if (node->key >= i.y)
	{
		search_d(node->left, i, result);
		return;
	}

	if (node->data.itv.y > i.x && node->data.itv.y < i.y)
		result.push_back(node->data.itv);

	search_d(node->left, i, result);
	search_d(node->right, i, result);
}

void itvtree::search_di(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue <= i.y) return;

	if (node->key >= i.x)
	{
		search_di(node->left, i, result);
		return;
	}

	if (node->data.itv.y > i.y)
		result.push_back(node->data.itv);

	search_di(node->left, i, result);
	search_di(node->right, i, result);
}

void itvtree::search_p(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.x)
	{
		InOrderTraverse(node, result);
		return;
	}
	if (node->key >= i.x)
	{
		search_p(node->left, i, result);
		return;
	}

	if (node->data.itv.y < i.x)
		result.push_back(node->data.itv);

	search_p(node->left, i, result);
	search_p(node->right, i, result);
}

void itvtree::search_pi(RB_Node* node, Interval i, vector<Interval>& result)
{
	auto index = node;
	while (index != m_nullNode)
	{
		if (i.y >= index->key)
			index = index->right;
		else
		{
			result.push_back(index->data.itv);
			InOrderTraverse(index->right, result);
			index = index->left;
		}
	}
}

void itvtree::search_s(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.x) return;

	if (node->key < i.x)
	{
		search_s(node->right, i, result);
		return;
	}
	if (node->key > i.x)
	{
		search_s(node->left, i, result);
		return;
	}
    
    if (node->data.itv.y < i.y)
        result.push_back(node->data.itv);
    
    search_s(node->left, i, result);
    search_s(node->right, i, result);
}

void itvtree::search_si(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.x) return;

	if (node->key < i.x)
	{
		search_si(node->right, i, result);
		return;
	}
	if (node->key > i.x)
	{
		search_si(node->left, i, result);
		return;
	}
    
    if (node->data.itv.y > i.y)
        result.push_back(node->data.itv);
    
    search_si(node->left, i, result);
    search_si(node->right, i, result);
}

void itvtree::search_f(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.y) return;
	if (node->key <= i.x)
	{
		search_f(node->right, i, result);
		return;
	}
	if (node->key >= i.y)
	{
		search_f(node->left, i, result);
		return;
	}

	if (node->data.itv.y == i.y)
		result.push_back(node->data.itv);

	search_f(node->left, i, result);
	search_f(node->right, i, result);
}

void itvtree::search_fi(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.y) return;

	if (node->key >= i.x)
	{
		search_fi(node->left, i, result);
		return;
	}

	if (node->data.itv.y == i.y)
		result.push_back(node->data.itv);

	search_fi(node->left, i, result);
	search_fi(node->right, i, result);
}

void itvtree::search_m(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.x) return;

	if (node->key > i.x)
	{
		search_m(node->left, i, result);
		return;
	}

	if (node->data.itv.y == i.x)
		result.push_back(node->data.itv);

	search_m(node->left, i, result);
	search_m(node->right, i, result);
}

void itvtree::search_mi(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.y) return;

	if (node->key < i.y)
	{
		search_mi(node->right, i, result);
		return;
	}
	if (node->key > i.y)
	{
		search_mi(node->left, i, result);
		return;
	}

    result.push_back(node->data.itv);
    
    search_mi(node->left, i, result);
	search_mi(node->right, i, result);
}

void itvtree::search_e(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.x) return;

	if (node->key < i.x)
	{
		if (node->key == i.x && node->data.itv.y==i.y)
			result.push_back(node->data.itv);
		search_e(node->right, i, result);
		return;
	}
	if (node->key > i.x)
	{
		search_e(node->left, i, result);
		return;
	}
    
    if (node->data.itv.y==i.y)
        result.push_back(node->data.itv);
    
    search_e(node->left, i, result);
	search_e(node->right, i, result);
}

