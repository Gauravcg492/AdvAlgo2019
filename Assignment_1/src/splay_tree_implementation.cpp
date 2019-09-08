#include "../include/splay_tree.hpp"

using namespace std;

class node
{
	private:
		int key;
		node *left;
		node *right;
		
	public:
		static int num_nodes;
	
		node(int key)
		{
			set_key(key);
			set_right(NULL);
			set_left(NULL);
			num_nodes++;
		}
		
		int get_key()
		{
			return key;
		}
		
		void set_key(int key)
		{
			this->key = key;
		}
		
		node* get_left()
		{
			return left;
		}
		
		void set_left(node *left)
		{
			this->left = left;
		}
		
		node* get_right()
		{
			return right;
		}
		
		void set_right(node *right)
		{
			this->right = right;
		}
		
		~node()
		{
			delete left;
			delete right;
			num_nodes--;
		}
};

int node::num_nodes = 0;



class splay_tree_implementation : public splay_tree
{
	private:
		node *root;
	
	public:
		splay_tree_implementation();
		int get_num_nodes();
		node* zig(node*);
		node* zag(node*);
		node* splay(node*,int);
		int find(int);
		node* bst_insert(node*,int);
		void insert(int);
		node* bst_remove(node*,int);		
		void remove(int);
		void rec_post(node*,vector<int>);
		vector<int> post_order();
		void rec_pre(node*,vector<int>);
		vector<int> pre_order();
		~splay_tree_implementation();
};


splay_tree_implementation :: splay_tree_implementation()
{
	root = NULL;
}

int splay_tree_implementation :: get_num_nodes()
{
	return (root == NULL)? 0 : (root)->num_nodes;
}

node* splay_tree_implementation :: zig(node *p)
{
	node *c = p->get_left();
	p->set_left(c->get_right());
	c->set_right(p);
	return c;
}

node* splay_tree_implementation :: zag(node *p)
{
	node *c = p->get_right();
	p->set_right(c->get_left());
	c->set_left(p);
	return c;
}

node* splay_tree_implementation :: splay(node *root,int ele)
{
	if(root == NULL || root->get_key() == ele) return root;
	node *temp;
	if(root->get_key() > ele)		//Enter left subtree
	{
		if(root->get_left() == NULL) return root;
		//Zig-Zig 
		if(root->get_left()->get_key() > ele)
		{
			temp = splay(root->get_left()->get_left(),ele);
			root->get_left()->set_left(temp);
			
			root = zig(root); //zig for g and p
		}
		else if(root->get_left()->get_key() < ele) //Zig-Zag
		{
			temp = splay(root->get_left()->get_right(),ele);
			root->get_left()->set_right(temp);
			
			if(root->get_left()->get_right() != NULL) root = zag(root->get_right()); //zag for p and x
		}
		
		return (root->get_left() == NULL)? root : zig(root); 	
	}
	else if(root->get_key() < ele)
	{
		if(root->get_right() == NULL) return root;
		//Zag-Zag
		if(root->get_right()->get_key() < ele)
		{
			temp = splay(root->get_right()->get_right(),ele);
			root->get_right()->set_right(temp);
			
			root = zag(root);	//Zag for g and p
		}
		else if(root->get_right()->get_key() > ele)	//Zag-Zid
		{
			temp = splay(root->get_right()->get_left(),ele);
			root->get_right()->set_left(temp);
			
			if(root->get_right()->get_left() != NULL) root = zig(root->get_right()); //Zig for p and x
		}		 
		return (root->get_right() == NULL)? root : zag(root);
	}
	return root;
}

int splay_tree_implementation :: find(int ele)
{
	root = splay(root,ele);
	if((root)->get_key() == ele) return 1;
	else return 0;
}

node* splay_tree_implementation :: bst_insert(node *root,int ele)
{
	if(root == NULL) return new node(ele);
	
	node *temp;
	
	if(root->get_key() > ele)
	{
		temp = bst_insert(root->get_left(),ele);
		root->set_left(temp);
	}
	else if(root->get_key() < ele)
	{
		temp = bst_insert(root->get_right(),ele);
		root->set_right(temp);
	}
	
	return root;
}

void splay_tree_implementation :: insert(int ele)
{	
	root = bst_insert(root,ele);
	find(ele);	
	return;
}

node* splay_tree_implementation :: bst_remove(node *root,int ele)
{
	node *curr, *prev, *temp, *p, *q;
	
	curr = root;
	prev = NULL;
	
	while(curr != NULL && curr->get_key() != ele)
	{
		prev = curr;
		if(curr->get_key() < ele) curr = curr->get_right();
		else curr = curr->get_left();
	}
	// no element present
	if(curr == NULL)
	{
		if(prev != NULL) find(prev->get_key());
		return root;
	}
	
	// check for subtress
	if(curr->get_left() == NULL || curr->get_right() == NULL)
	{
		if(curr->get_left() != NULL) q = curr->get_left();
		else q = curr->get_right();
		
		// check if the elemnt is in root
		if(prev == NULL)
		{
			delete curr;
			return q;
		}
		
		if(curr == prev->get_left()) prev->set_left(q);
		else prev->set_right(q);
		delete curr;
	}
	else
	{
		p = curr;
		temp = curr->get_right();
		while(temp->get_left() != NULL)
		{
			p = temp;
			temp = temp->get_left();
		}
		
		if(p != curr)
		{
			p->set_left(temp->get_right());
		}
		else
		{
			curr->set_right(temp->get_right());
		}
		curr->set_key(temp->get_key());
		delete temp;
	}
	
	if(prev != NULL)
	{
		find(prev->get_key());
	}
	
	return root;
}

void splay_tree_implementation :: remove(int ele)
{
	root = bst_remove(root,ele);
	return;
}

void splay_tree_implementation :: rec_post(node *root,vector<int> vect)
{
	if(root != NULL)
	{		
		rec_post(root->get_left(),vect);		
		rec_post(root->get_right(),vect);
		vect.push_back(root->get_key());
	}
}

vector<int> splay_tree_implementation :: post_order()
{
	vector<int> vect;
	rec_post(root,vect);
	return vect;
}

void splay_tree_implementation :: rec_pre(node *root,vector<int> vect)
{
	if(root != NULL)
	{
		vect.push_back(root->get_key());
		rec_pre(root->get_left(),vect);		
		rec_pre(root->get_right(),vect);
	}
}

vector<int> splay_tree_implementation :: pre_order()
{
	vector<int> vect;
	rec_post(root,vect);
	return vect;
}

splay_tree_implementation :: ~splay_tree_implementation()
{
	delete root;
}

