#define ll long long


typedef struct node{
	int ht;//ht of node 
	int num;//number of nodes in rooted subtree 
	ll val;
	struct node* left;
	struct node* right;
	node(int val):val(val), left(nullptr), right(nullptr), ht(0), num(1){}
}node;

typedef struct AVL{	
	node* root;
	AVL():root(nullptr){}
	node* add_node(node*, ll);
	node* remove_node(node*, ll);

	//search utility
	node* find_node(node*, ll);

	//return height of rooted subtree 
	ll find_ht(node*);
	
	//returns the number of nodes in subtree
	ll find_num(node*);
	
	//finds the closest value to a given value.
	//if multiple satisfy the constraint, it will return the first closest encountered 
	ll find_closest(node*, ll);
	
	ll kth_smallest(node*, ll);

	ll nth_largest(node* root, ll n);
	
	//types of traversals
	void preorder(node *);
	void postorder(node *);
	void inorder(node *);
	
	//types of rotation
	node* left_left(node*, node*, node* );
	node* left_right(node*, node*, node* );
	node* right_left(node*, node*, node* );
	node* right_right(node*, node*, node* );
}AVL;