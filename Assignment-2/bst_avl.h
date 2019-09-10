#define ll long long
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#define DEBUG_MSG_VAL_HT(val, height) do { std::cout<<"Node: "<<val<<" Height: "<<height<<"\n"; } while(false)
#else
#define DEBUG_MSG(str) do { } while ( false )
#define DEBUG_MSG_VAL_HT(val, height) do { } while(false)
#endif

//Define courtsey 
//https://stackoverflow.com/questions/3371540/c-enable-disable-debug-messages-of-stdcouts-on-the-fly

//test cases build from 
//https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct
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
	void preorder(node *);
	void postorder(node *);
	void inorder(node *);
	ll find_ht(node*);
	node* left_left(node*, node*, node* );
	node* left_right(node*, node*, node* );
	node* right_left(node*, node*, node* );
	node* right_right(node*, node*, node* );
}AVL;