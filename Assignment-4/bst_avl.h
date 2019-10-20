#define ll long long

template <class K, class V>
struct node{
	K key;
	V val;
	int ht;
	node<K,V>* left;
	node<K,V>* right;
	node():left(nullptr), right(nullptr),ht(0){};
	node(K key, V val):key(key), val(val), left(nullptr), right(nullptr), ht(0){}
};

template <class K, class V>
struct AVL{	
	node <K,V>* root;
	AVL<K,V>():root(nullptr){}
	node <K,V>* add_node(node <K,V>*, K key, V val);
	node <K,V>* remove_node(node <K,V>*, K key);

	//search utility
	node <K,V>* find_node(node <K,V>*, K);

	ll find_ht(node <K,V>*);

	//types of traversals
	void preorder(node <K,V> *);
	void postorder(node <K,V> *);
	void inorder(node <K,V> *);
	
	//types of rotation
	node <K,V>* left_left(node <K,V>*, node <K,V>*, node <K,V>* );
	node <K,V>* left_right(node <K,V>*, node <K,V>*, node <K,V>* );
	node <K,V>* right_left(node <K,V>*, node <K,V>*, node <K,V>* );
	node <K,V>* right_right(node <K,V>*, node <K,V>*, node <K,V>* );
};