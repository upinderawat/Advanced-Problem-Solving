#include <bits/stdc++.h>
#include "bst_avl.h"
using namespace std;

int main(int argc, char const *argv[]){
	AVL<int, int> tree;
	//{20, 4}
	//{20, 4, 26, 3, 9}
	//{20, 4, 26, 3, 9, 21, 30, 2, 7, 11}
	std::vector<pair<int, int>> v=	{{1,5}, {2,2}, {3,8}, {4,1}, {5,3}, {6,7}, {7,10}, {8,4}, {9,6}, {10,9}, {11,11}, {12,12}};//{1, 3, 2};;
//delete test cases
	//{5, 2, 8, 1, 3, 7, 10, 4, 6, 9, 11, 12};//{1, 3, 2};
	for(auto u : v)
		tree.root = tree.add_node(tree.root, u.first, u.second);

	// root = tree.add_node(root, 15);
	// root = tree.remove_node(root, 1);
		// tree.root = tree.add_node(tree.root, 5);
	// tree.preorder(tree.root);
	// std::cout<<"\n";
	// for(int i=1; i<13; i++){
	// 	std::cout<<tree.nth_largest(root, i)<<" ";
	// }
	// std::cout<<tree.elements_in_range(root, 7, 2);
//	std::cout<<"\n";
	// tree.find_node(root, 3) == nullptr ? std::cout<<"Not found": std::cout<<"found";
	// tree.postorder(root);
	// 	std::cout<<"\n";
//	tree.inorder(root);
	return 0;
}