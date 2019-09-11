#include <bits/stdc++.h>
#include "bst_avl.h"
#define ll long long
#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#define DEBUG_MSG_VAL_HT(val, height) do { std::cout<<"Node: "<<val<<" Height: "<<height<<"\n"; } while(false)
#define DEBUG_MSG_VAL_HT_NUM(val, height, num) do { std::cout<<"Node: "<<val<<" Height: "<<height<<" Number of Nodes: "<<num<<"\n"; } while(false)
#else
#define DEBUG_MSG(str) do { } while ( false )
#define DEBUG_MSG_VAL_HT(val, height) do { } while(false)
#define DEBUG_MSG_VAL_HT_NUM(val, height, num) do {} while(false)
#endif

//DEBUG courtsey 
//https://stackoverflow.com/questions/3371540/c-enable-disable-debug-messages-of-stdcouts-on-the-fly

//test cases build from 
//https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct
node* AVL::add_node(node* root, ll val){
	if(root == nullptr){
		return new node(val);
	}
	else{	
		if(root->val < val){
			root->right = add_node(root->right, val);
		}
		else{
			root->left = add_node(root->left, val);	
		}
		root->ht = 1 + std::max(find_ht(root->left), find_ht(root->right));
		root->num = 1 + find_num(root->left) + find_num(root->right);
		int bf;
		bf = find_ht(root->left) - find_ht(root->right);
		node *z, *y, *x;
		z = root;
		if(bf> 1){
			y = z->left;
			if(y->val > val){
				//L-L rot
				x = y->left;
				root = left_left(z, y, x);
			}
			else if(y->val < val){
				//L-R rot
				x = y->right;
				root = left_right(z, y, x);
			}
		}
		else if(bf < -1){
			y = z->right;
			if(y->val < val){
				//RR rot
				x = y->right;
				root = right_right(z, y, x);
			}
			else if(y->val > val){
				//R-L rot
				x = y->left;
				root = right_left(z, y, x);
			}
		}
	}
	return root;
}
node* AVL::remove_node(node* root, ll val){
	if(root->val == val){
		if(root->left && root->right){
			node *tmp = root->left;
			while(tmp->right){
				tmp = tmp->right;
			}
			root->val = tmp->val;
			root->left = remove_node(root->left, tmp->val);
		}
		else if(root->left){
			node * tmp = root->left;
			free(root);
			return tmp;
		}
		else if(root->right){
			node * tmp = root->right;
			free(root);
			return tmp;
		}
		else{
			free(root);
			return nullptr;
		}
	}
	else if(root->val < val){
		root->right = remove_node(root->right, val);
	}
	else{
		root->left = remove_node(root->left, val);
	}
	root->ht = 1 + std::max(find_ht(root->left), find_ht(root->right));
	root->num = 1 + find_num(root->left) + find_num(root->right);
	int bf = find_ht(root->left) - find_ht(root->right);
	node* x, *y, *z;
	//y is the bigger child of z, height of both sub tree can't be same. As we know z is imbalanced
	//x is the bigger child of x in terms of height, check y is left child or right
	
	z = root;
	if(abs(bf)>1){
		//Decide y
		if(bf > 1){//left child has greater height
			y = z->left;
			//decide x
			if(find_ht(y->right) > find_ht(y->left)){
				x = y->right;
				//L-R rot
				root = left_right(z, y, x);
			}
			//optimized step to avoid double rotation
			else if(find_ht(y->right) <= find_ht(y->left)){
				x = y->left;
				//L-L rot
				root = left_left(z, y, x);
			}
		}
		else if(bf < -1){
			y = z->right;
			//decide x
			if(find_ht(y->right) >= find_ht(y->left)){
				x = y->right;
				//R-R rot
				root = right_right(z, y, x);
			}
			else if(find_ht(y->right) < find_ht(y->left)){
				x = y->left;
				//R-L rot
				root = right_left(z, y, x);
			}
		}
	}

	return root;
}
node* AVL::find_node(node* root, ll val){
	if(root == nullptr)
		return nullptr;
	else{
		if(root->val == val) return root;
		if(root->val < val) return find_node(root->right, val);
		else return find_node(root->left, val);
	}
}
ll AVL::find_closest(node* root, ll val){
	ll closest_val = LLONG_MAX;
	ll closest_dist = LLONG_MAX;
	node *tmp = root;
	while(tmp){
		if(tmp->val == val){
			return tmp->val;
		}
		if(abs(tmp->val - val) < closest_dist){
			closest_dist = abs(tmp->val - val);
			closest_val = tmp->val;
		}
		if(tmp->val < val){
			tmp = tmp->right;
		}
		else{
			tmp = tmp->left;
		}
	}
	return closest_val;
}
node* AVL::left_left(node* n, node* c, node* gc){
	//node, child and grandchild ->(z,y,x)
	DEBUG_MSG("left left\n");
	n->left = c->right;
	c->right = n;
	//order is imp here; as n becomes the parent now, height of gc, n must be avail first
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));

	gc->num = 1 + find_num(gc->left) + find_num(gc->right);
	n->num = 1 + find_num(n->left) + find_num(n->right);
	c->num = 1 + find_num(c->left) + find_num(c->right);
	return c;
}
node* AVL::left_right(node* n, node* c, node* gc){
	//node, child and grandchild ->(z,y,x)
	DEBUG_MSG("left right\n");
	c->right = gc->left;
	n->left = gc->right;
	gc->left = c;
	gc->right = n;

	//order is imp here; as gc becomes the parent now, height of c, n must be avail first
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));

	n->num = 1 + find_num(n->left) + find_num(n->right);
	c->num = 1 + find_num(c->left) + find_num(c->right);
	gc->num = 1 + find_num(gc->left) + find_num(gc->right);

	return gc;
}
node* AVL::right_right(node* n, node* c, node* gc){
	//node, child and grandchild ->(z,y,x)
	DEBUG_MSG("right right\n");
	
	n->right = c->left;
	c->left = n;

	//order is imp here; as n becomes the parent now, height of gc, n must be avail first
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));

	gc->num = 1 + find_num(gc->left) + find_num(gc->right);
	n->num = 1 + find_num(n->left) + find_num(n->right);
	c->num = 1 + find_num(c->left) + find_num(c->right);
	return c;
}
node* AVL::right_left(node* n, node* c, node* gc){
	//node, child and grandchild ->(z,y,x)
	DEBUG_MSG("right left\n");
	
	c->left = gc->right;
	n->right = gc->left;
	gc->right = c;
	gc->left = n;
	//order is imp here; as gc becomes the parent now, height of c, n must be avail first
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));

	n->num = 1 + find_num(n->left) + find_num(n->right);
	c->num = 1 + find_num(c->left) + find_num(c->right);
	gc->num = 1 + find_num(gc->left) + find_num(gc->right);
	return gc;	
}

ll AVL::find_ht(node* root){return root==nullptr ? -1 : root->ht;}
ll AVL::find_num(node* root){return root==nullptr ? 0 : root->num;}
void AVL::preorder(node *root){
	if(!root) return;
	std::cout<<root->val<<" ";
	DEBUG_MSG_VAL_HT_NUM(root->val, root->ht, root->num);
	preorder(root->left);
	preorder(root->right);
}
void AVL::postorder(node *root){
	if(!root) return;
	postorder(root->left);
	postorder(root->right);
	std::cout<<root->val<<" ";
	DEBUG_MSG_VAL_HT_NUM(root->val, root->ht, root->num);
}
void AVL::inorder(node *root){
	if(!root) return;
	inorder(root->left);
	std::cout<<root->val<<" ";
	DEBUG_MSG_VAL_HT_NUM(root->val, root->ht, root->num);
	inorder(root->right);
}