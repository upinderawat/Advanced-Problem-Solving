#define ll long long


typedef struct node{
	int ht;//ht of node 
	ll val;
	struct node* left;
	struct node* right;
	node(int val):val(val), left(nullptr), right(nullptr), ht(0){}
}node;

typedef struct AVL{	
	node* root;
	AVL():root(nullptr){}
	node* add_node(node*, ll);
	node* remove_node(node*, ll);
	node* find_node(node*, ll);
	ll find_ht(node*);
	node* find_closest(node*, ll);
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