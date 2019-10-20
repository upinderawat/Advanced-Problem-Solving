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
template <class K, class V>
node <K,V>* AVL<K,V>::add_node(node <K,V>* root, K key, V val){
	if(root == nullptr){
		return new node <K,V>(key, val);
	}
	else{	
		if(root->key == key){
			return root;
		}
		else if(root->key < key){
			root->right = add_node(root->right, key, val);
		}
		else{
			root->left = add_node(root->left, key, val);	
		}
		root->ht = 1 + std::max(find_ht(root->left), find_ht(root->right));
		int bf;
		bf = find_ht(root->left) - find_ht(root->right);
		node <K,V> *z, *y, *x;
		z = root;
		if(bf> 1){
			y = z->left;
			if(y->key > key){
				//L-L rot
				x = y->left;
				root = left_left(z, y, x);
			}
			else if(y->key < key){
				//L-R rot
				x = y->right;
				root = left_right(z, y, x);
			}
		}
		else if(bf < -1){
			y = z->right;
			if(y->key < key){
				//RR rot
				x = y->right;
				root = right_right(z, y, x);
			}
			else if(y->key > key){
				//R-L rot
				x = y->left;
				root = right_left(z, y, x);
			}
		}
	}
	return root;
}
template <class K, class V> node <K,V>* AVL<K,V>::remove_node(node <K,V>* root, K key){
	if(root->key == key){
		if(root->left && root->right){
			node <K,V> *tmp = root->left;
			while(tmp->right){
				tmp = tmp->right;
			}
			root->key = tmp->key;
			root->val = tmp->val;
			root->left = remove_node(root->left, tmp->key);
		}
		else if(root->left){
			node <K,V> * tmp = root->left;
			free(root);
			return tmp;
		}
		else if(root->right){
			node <K,V>* tmp = root->right;
			free(root);
			return tmp;
		}
		else{
			free(root);
			return nullptr;
		}
	}
	else if(root->key < key){
		root->right = remove_node(root->right, key);
	}
	else{
		root->left = remove_node(root->left, key);
	}
	root->ht = 1 + std::max(find_ht(root->left), find_ht(root->right));
	int bf = find_ht(root->left) - find_ht(root->right);
	node<K,V>* x, *y, *z;
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
template <class K, class V>
ll AVL<K,V>::find_ht(node <K,V>* root){return root==nullptr ? -1 : root->ht;}

template <class K, class V>
node <K,V>* AVL<K,V>::find_node(node <K,V>* root, K key){
	if(root == nullptr)
		return nullptr;
	else{
		if(root->key == key) return root;
		if(root->key < key) return find_node(root->right, key);
		else return find_node(root->left, key);
	}
}
template <class K, class V>
void AVL<K,V>::preorder(node <K,V> *root){
	if(!root) return;
	std::cout<<root->val<<" ";
	DEBUG_MSG_VAL_HT(root->val, root->ht);
	preorder(root->left);
	preorder(root->right);
}

template <class K, class V>
void AVL<K,V>::postorder(node <K,V> *root){
	if(!root) return;
	postorder(root->left);
	postorder(root->right);
	std::cout<<root->val<<" ";
	DEBUG_MSG_VAL_HT(root->val, root->ht);
}

template <class K, class V>
void AVL<K,V>::inorder(node <K,V> *root){
	if(!root) return;
	inorder(root->left);
	std::cout<<root->val<<" ";
	DEBUG_MSG_VAL_HT(root->val, root->ht);
	inorder(root->right);
}

template <class K, class V>
node <K,V>* AVL<K,V>::left_left(node <K,V>* n, node <K,V>* c, node <K,V>* gc){
	//node <K,V>, child and grandchild ->(z,y,x)
	DEBUG_MSG("left left\n");
	n->left = c->right;
	c->right = n;
	//order is imp here; as c becomes the parent now, height of gc, n must be avail first
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));

	return c;
}
template <class K, class V>
node <K,V>* AVL<K,V>::left_right(node <K,V>* n, node <K,V>* c, node <K,V>* gc){
	//node <K,V>, child and grandchild ->(z,y,x)
	DEBUG_MSG("left right\n");
	c->right = gc->left;
	n->left = gc->right;
	gc->left = c;
	gc->right = n;

	//order is imp here; as gc becomes the parent now, height of c, n must be avail first
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));

	return gc;
}

template <class K, class V>
node <K,V>* AVL<K,V>::right_left(node <K,V>* n, node <K,V>* c, node <K,V>* gc){
	//node <K,V>, child and grandchild ->(z,y,x)
	DEBUG_MSG("right left\n");
	
	c->left = gc->right;
	n->right = gc->left;
	gc->right = c;
	gc->left = n;
	//order is imp here; as gc becomes the parent now, height of c, n must be avail first
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));

	return gc;	
}
template <class K, class V>
node <K,V>* AVL<K,V>::right_right(node <K,V>* n, node <K,V>* c, node <K,V>* gc){
	//node, child and grandchild ->(z,y,x)
	DEBUG_MSG("right right\n");
	
	n->right = c->left;
	c->left = n;

	//order is imp here; as n becomes the parent now, height of gc, n must be avail first
	gc->ht = 1 + std::max(find_ht(gc->left), find_ht(gc->right));
	n->ht = 1 + std::max(find_ht(n->left), find_ht(n->right));
	c->ht = 1 + std::max(find_ht(c->left), find_ht(c->right));
	return c;
}

