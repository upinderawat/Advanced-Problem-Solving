#include <bits/stdc++.h>
#define ll long long
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

typedef struct node{
	ll ht;//ht of node 
	ll num;//number of nodes in rooted subtree 
	ll val;
	struct node* left;
	struct node* right;
	node(ll val):val(val), left(nullptr), right(nullptr), ht(0), num(1){}
}node;

typedef struct AVL{	
	node* root;
	AVL():root(nullptr){}
	node* add_node(node*, ll);
	
	//return height of rooted subtree 
	ll find_ht(node*);
	
	//returns the number of nodes in subtree
	ll find_num(node*);
	
	ll kth_smallest(node*, ll);

	float find_median(node*);
	//types of rotation
	node* left_left(node*, node*, node* );
	node* left_right(node*, node*, node* );
	node* right_left(node*, node*, node* );
	node* right_right(node*, node*, node* );
}AVL;
node* AVL::add_node(node* root, ll val){
	if(root == nullptr){
		return new node(val);
	}
	else{	
		if(root->val <= val){
			root->right = add_node(root->right, val);
		}
		else {//if(root->val > val){
			root->left = add_node(root->left, val);	
		}
		root->ht = 1 + std::max(find_ht(root->left), find_ht(root->right));
		root->num = 1 + find_num(root->left) + find_num(root->right);
		ll bf;
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
			else if(y->val <= val){
				//L-R rot
				x = y->right;
				root = left_right(z, y, x);
			}
		}
		else if(bf < -1){
			y = z->right;
			if(y->val <= val){
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
ll AVL::find_ht(node* root){return root==nullptr ? -1 : root->ht;}

ll AVL::find_num(node* root){return root==nullptr ? 0 : root->num;}

ll AVL:: kth_smallest(node* root, ll k){
	//error checking to be done at handler side
	//check for nullptr and k > root->num
	node* tmp=root;
	ll smaller_than_k;
	smaller_than_k = 0;
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
	return -1;//non reachable; added to avoid warning
}

float AVL:: find_median(node* root){
	float med;
	ll n_nodes = find_num(root);
	ll a = kth_smallest(root, (n_nodes/2));
	ll b = kth_smallest(root, (n_nodes/2 + 1));
	if(n_nodes&1){
		med =  b;
	}
	else{
		med =  a +  (b-a)/2.0;
	}
	return med;
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
int main(int argc, char const *argv[])
{
	ll N;
	ll tmp;
	AVL tree;
	std::cin>>N;
	for(ll i=0;i<N;i++){
		std::cin>>tmp;
		tree.root = tree.add_node(tree.root, tmp);
		printf("%.1f\n", tree.find_median(tree.root));
	}
	std::cout<<"\n";
	return 0;
}