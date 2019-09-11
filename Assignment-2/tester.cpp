#include <bits/stdc++.h>
#include "bst_avl.h"
int main(int argc, char const *argv[]){
	AVL tree;
	node* root=nullptr;
//insert test cases
	//{20, 4}
	//{20, 4, 26, 3, 9}
	//{20, 4, 26, 3, 9, 21, 30, 2, 7, 11}
	std::vector<int> v=	{10, 8, 12, 4};//{5, 2, 8, 1, 3, 7, 10, 4, 6,  11, 12};//{1, 3, 2};;
//delete test cases
	//{5, 2, 8, 1, 3, 7, 10, 4, 6, 9, 11, 12};//{1, 3, 2};
	for(auto u : v)
		root = tree.add_node(root, u);

	// root = tree.add_node(root, 8);
	// root = tree.add_node(root, 15);
	// root = tree.remove_node(root, 1);
	tree.preorder(root);
	std::cout<<"\n";
	std::cout<<"Closest: "<<tree.find_closest(root, 9);
	// for(int i=1; i<13; i++){
	// 	std::cout<<tree.nth_largest(root, i)<<" ";
	// }
//	std::cout<<"\n";
	// tree.find_node(root, 3) == nullptr ? std::cout<<"Not found": std::cout<<"found";
	// tree.postorder(root);
	// 	std::cout<<"\n";
//	tree.inorder(root);
	return 0;
}