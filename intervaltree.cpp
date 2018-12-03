/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include"intervaltree.h"
#include<algorithm>


void intervaltree::Insert(Interval interv)
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
		else if (key>index->key)
		{
			index = index->right;
		}
		else
		{
			index->data.equkey.push_back(interv);
			return ;
		}
	}
	RB_Node* insert_node = new RB_Node();
	insert_node->key = key;
	insert_node->data.equkey.push_back(interv);
	insert_node->data.maxvalue = interv.y;
	insert_node->RB_COLOR = RED;
	insert_node->right = m_nullNode;
	insert_node->left = m_nullNode;
	if (insert_point == m_nullNode) //����������һ�ſ���
	{
		m_root = insert_node;
		m_root->parent = m_nullNode;
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
		insert_node->parent = insert_point;
	}

	InsertFixUp(insert_node);    //����InsertFixUp�޸���������ʡ�
}

void intervaltree::InsertFixUp(RB_Node* node)
{
	while (node->parent->RB_COLOR == RED)
	{
		if (node->parent == node->parent->parent->left)   //
		{
			RB_Node* uncle = node->parent->parent->right;
			if (uncle->RB_COLOR == RED)   //�������1��z������y�Ǻ�ɫ�ġ�
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)  //�������2��z������y�Ǻ�ɫ�ģ���
			{
				if (node == node->parent->right) //��z���Һ���
				{
					node = node->parent;
					RotateLeft(node);
				}
				else                 //�������3��z������y�Ǻ�ɫ�ģ���z�����ӡ�
				{
					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateRight(node->parent->parent);
				}
			}
		}
		else //�ⲿ�������Ϊ�������1�У�z�ĸ���������Ϊ�游���Һ����˵��������д�ġ�
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
					RotateRight(node);     //������������ȣ�������Ϊ����
				}
				else
				{
					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateLeft(node->parent->parent);   //������Ϊ���������ɡ�
				}
			}
		}
	}
	m_root->RB_COLOR = BLACK;
}

void intervaltree::buildtree(vector<Interval>& data)
{
	for (size_t i = 0; i < data.size(); i++)
		Insert(data[i]);
}

void intervaltree::buildtree(vector<Point>& data)
{
	for (size_t i = 0; i < data.size(); i++)
		Insert(Interval(data[i]));
}

void intervaltree::printtree(RB_Node* node)
{
	if (node != m_nullNode)
	{
		for_each(node->data.equkey.begin(), node->data.equkey.end(),display);
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

void intervaltree::printtree()
{
	printtree(m_root);
}

bool intervaltree::RotateLeft(RB_Node* node)
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
	Interval M = *max_element(node->data.equkey.begin(), node->data.equkey.end(), yless);
	node->data.maxvalue = max(max(node->left->data.maxvalue, node->right->data.maxvalue), double(M.y));
	return true;
}

bool intervaltree::RotateRight(RB_Node* node)
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
	Interval M = *max_element(node->data.equkey.begin(), node->data.equkey.end(), yless);
	node->data.maxvalue = max(max(node->left->data.maxvalue, node->right->data.maxvalue), double(M.y));
	return true;
}

void intervaltree::InOrderTraverse(RB_Node* node, vector<Interval>& result)
{
	if (node == m_nullNode)
	{
		return;
	}

		InOrderTraverse(node->left,result);

		for (size_t j = 0; j < node->data.equkey.size(); j++)
		{
				result.push_back(node->data.equkey[j]);
		}

		InOrderTraverse(node->right,result);

}

void intervaltree::search_o(RB_Node* node,Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue <= i.x) return;

	if (node->key >= i.x)
	{
		search_o(node->left, i, result);
		return;
	}

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t > i.x && t < i.y)
			result.push_back(node->data.equkey[j]);
	}

	search_o(node->left, i, result);
	search_o(node->right, i, result);
}

void intervaltree::search_oi(RB_Node* node, Interval i, vector<Interval>& result)
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

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t > i.y)
			result.push_back(node->data.equkey[j]);
	}

	search_oi(node->left, i, result);
	search_oi(node->right, i, result);
}

void intervaltree::search_d(RB_Node* node, Interval i, vector<Interval>& result)
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

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t < i.y)
			result.push_back(node->data.equkey[j]);
	}

	search_d(node->left, i, result);
	search_d(node->right, i, result);
}

void intervaltree::search_di(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue <= i.y) return;

	if (node->key >= i.x)
	{
		search_di(node->left, i, result);
		return;
	}

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t > i.y)
			result.push_back(node->data.equkey[j]);
	}

	search_di(node->left, i, result);
	search_di(node->right, i, result);
}

void intervaltree::search_p(RB_Node* node, Interval i, vector<Interval>& result)
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

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t < i.x)
			result.push_back(node->data.equkey[j]);
	}

	search_p(node->left, i, result);
	search_p(node->right, i, result);
}

void intervaltree::search_pi(RB_Node* node, Interval i, vector<Interval>& result)
{
	RB_Node* index = node;
	while (index != m_nullNode)
	{
		if (i.y >= index->key)
			index = index->right;
		else
		{
			for (size_t j = 0; j < index->data.equkey.size(); j++)
			{
					result.push_back(index->data.equkey[j]);
			}
			InOrderTraverse(index->right, result);
			index = index->left;
		}
	}
}

void intervaltree::search_s(RB_Node* nd, Interval i, vector<Interval>& result)
{
	RB_Node* node = find(i.x);
	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t < i.y)
			result.push_back(node->data.equkey[j]);
	}
}

void intervaltree::search_si(RB_Node* nd, Interval i, vector<Interval>& result)
{
	RB_Node* node = find(i.x);
	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t > i.y)
			result.push_back(node->data.equkey[j]);
	}
}

void intervaltree::search_f(RB_Node* node, Interval i, vector<Interval>& result)
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

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t == i.y)
			result.push_back(node->data.equkey[j]);
	}

	search_f(node->left, i, result);
	search_f(node->right, i, result);
}

void intervaltree::search_fi(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.y) return;

	if (node->key >= i.x)
	{
		search_fi(node->left, i, result);
		return;
	}

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t == i.y)
			result.push_back(node->data.equkey[j]);
	}

	search_fi(node->left, i, result);
	search_fi(node->right, i, result);
}

void intervaltree::search_m(RB_Node* node, Interval i, vector<Interval>& result)
{
	if (node == m_nullNode) return;
	if (node->data.maxvalue < i.x) return;

	if (node->key > i.x)
	{
		search_m(node->left, i, result);
		return;
	}

	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t == i.x)
			result.push_back(node->data.equkey[j]);
	}

	search_m(node->left, i, result);
	search_m(node->right, i, result);
}

void intervaltree::search_mi(RB_Node* nd, Interval i, vector<Interval>& result)
{
	RB_Node* node = find(i.y);
	result = node->data.equkey;
	//for (size_t j = 0; j < node->data.equkey.size(); j++)
	//{
	//		result.push_back(node->data.equkey[j]);
	//}
}

void intervaltree::search_e(RB_Node* nd, Interval i, vector<Interval>& result)
{
	RB_Node* node = find(i.x);
	for (size_t j = 0; j < node->data.equkey.size(); j++)
	{
		double t = node->data.equkey[j].y;
		if (t == i.y)
			result.push_back(node->data.equkey[j]);
	}
}

unsigned long long  intervaltree::size(RB_Node* node)
{
	if (node == m_nullNode)
	{
		return 0;
	}

	unsigned long long r = sizeof(*node);
	r+=size(node->left);
	r += size(node->right);
	r += node->data.equkey.capacity() * sizeof(Interval);
	return r;
}
