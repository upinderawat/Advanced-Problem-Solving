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
		if(root->val == val){
			return root;
		}
		else if(root->val < val){
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
ll AVL::find_ht(node* root){return root==nullptr ? -1 : root->ht;}

ll AVL::find_num(node* root){return root==nullptr ? 0 : root->num;}

node* AVL::find_closest(node* root, ll val){
	//returns nullptr on empty tree
	node* closest_node = root;
	ll closest_dist = LLONG_MAX;
	node *tmp = root;
	while(tmp){
		if(tmp->val == val){
			return tmp;
		}
		if(abs(tmp->val - val) <= closest_dist){
			//choose the closest_node to be lower limit in case of equal closest_dist incident
			if((abs(tmp->val - val) < closest_dist) || (abs(tmp->val - val) == closest_dist) and tmp->val < closest_node->val){
				closest_dist = abs(tmp->val - val);
				closest_node = tmp;
			}
		}
		if(tmp->val < val){
			tmp = tmp->right;
		}
		else{
			tmp = tmp->left;
		}
	}
	return closest_node;
}
ll AVL:: kth_smallest(node* root, ll k){
	//error checking to be done at handler side
	//check for nullptr and k > root->num
	node* tmp=root;
	ll smaller_than_k, greater_than_k;
	smaller_than_k = greater_than_k = 0;
	while(tmp){
		if(smaller_than_k + find_num(tmp->left) + 1 == k){
			return tmp->val;
		}
		else if(smaller_than_k + find_num(tmp->left) + 1 < k){
			smaller_than_k = smaller_than_k + find_num(tmp->left) + 1;
			tmp = tmp->right;
		}
		else if(smaller_than_k + find_num(tmp->left) + 1 > k){
			tmp = tmp->left;
		}
	}
}
ll AVL:: nth_largest(node* root, ll n){
	//handle out of bound in handler
	ll k = root->num - n + 1;
	if( k >= 0){
		return kth_smallest(root, k);
	}
}
node* AVL::LCA(node* root, ll a, ll b){
	//return nullptr for empty tree
	node* tmp= root;
	while(tmp){
		if(tmp->val < a && tmp->val < b){
			tmp = tmp->right;
		}
		else if(tmp->val > a && tmp->val > b){
			tmp = tmp->left;
		}
		else{
			break;
		}
	}
	return tmp;
}
ll AVL::elements_ge_val(node* root, ll val){
	ll ans=0;
	node* tmp = root;
	while(tmp){
		if(tmp->val >= val){
			ans += find_num(tmp->right) + 1;
			tmp= tmp->left;
		}
		else if(tmp->val < val){
			tmp = tmp->right;
		}
	}
	return ans;
}
ll AVL::elements_le_val(node* root, ll val){
	ll ans=0;
	node* tmp = root;
	while(tmp){
		if(tmp->val <= val){
			ans += find_num(tmp->left) + 1;
			tmp= tmp->right;
		}
		else if(tmp->val > val){
			tmp = tmp->left;
		}
	}
	return ans;
}
ll AVL::elements_in_range(node* root, ll a, ll b){
	//error handling for empty root needs to be checked
	if( a > b ){
		return 0;
	}
	ll res=0;
	ll total_elements = find_num(root);
	node* ap = find_closest(root, a);
	node* bp = find_closest(root, b);
	ll elements_ge_ap = elements_ge_val(root, ap->val);
	ll elements_le_bp = elements_le_val(root, bp->val);
	res = elements_ge_ap + elements_le_bp - total_elements; 
	
	if(ap->val < a){
		res--;
	}
	if(bp->val > b){
		res--;
	}
	return res;
}
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

