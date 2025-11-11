//
// Created by zande on 11/10/2025.
//

#ifndef AVLTREE_BSTNODE_H
#define AVLTREE_BSTNODE_H
#include <string>


class BSTNode {
public:
	// variables
	std::string key;
	size_t value;
	BSTNode* left;
	BSTNode* right;
	int height;

	BSTNode();
	BSTNode(std::string &key, size_t value);

	void load(std::string &key, size_t value);
	BSTNode* insertRight(BSTNode* rightChild);
	BSTNode* insertLeft(BSTNode* leftChild);
	void setHeight(int height);

	std::string getKey();
	size_t getValue();
	size_t& getValueRef();
	BSTNode* getLeft();
	BSTNode* getRight();
	int getHeight();
	int getBalance();
	int getNumChildren();
	bool isLeaf();
};


#endif //AVLTREE_BSTNODE_H