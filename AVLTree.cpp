/**
 * AVLTree.cpp
 * Created by Zander Little 11/08/2025
 * DESCRIPTION HERE
 */

#include "AVLTree.h"

#include <ios>
#include <string>

// constructor
AVLTree::AVLTree() {}

/**
 * Creates a deep copy of an AVLTree.
 *
 * @param other the AVLTree being copied
 */
AVLTree::AVLTree(const AVLTree& other) {}

/**
 * Insert a new key-value pair into the tree. After a successful insert, the tree is rebalanced if necessary.
 * Duplicate keys and values are disallowed
 *
 * @param key the key being inserted
 * @param value the value being inserted
 * @return returns true if the insertion is successful, returns false otherwise.
 */
bool AVLTree::insert(const std::string& key, size_t value) {
	// check for duplicate keys
	if (contains(key)) {
		return false;
	}
	std::string nonConstKey = key;

	// try to insert key-value pair. Will fail if the value is already in the AVLTree.
	if (insertNode(nonConstKey, value, root)) {
		// TODO: rebalance root.
		return true;
	}
	return false;
}

/**
 * Recursive helper method of insert.
 *
 * Base case occurs when insertNode reaches a nullptr,
 * this means it is where the new value should be inserted.
 *
 * @param val the value being added to the AVLTree
 * @param current the current node
 * @return returns true if the key-value pair was inserted. Returns false otherwise.
 */
bool AVLTree::insertNode(std::string& key, size_t val, AVLNode *&current) {
	// base case: current is nullptr. Insert here. //
	if (current == nullptr) {
		current = new AVLNode(key, val);
		return true;
	}

	// if value > currValue, continue down right subtree, and vise versa.
	if (val > current->getValue()) { // right subtree
		if (insertNode(key, val, current->getRight())) {
			return true;}
	}
	else if (val < current->getValue()) {
		// left subtree
		if (insertNode(key, val, current->getLeft())) {
			return true;}
	}
	return false;
}

/**
 * If the key is in the tree, remove() will delete the key-value pair from the tree. The memory allocated
 * for the node that is removed will be released. After removing the key-value pair, the tree is
 * rebalanced if necessary.
 *
 * @param key the key being removed from the AVLTree
 * @return returns true if the key was found and removed, returns false otherwise.
 */
bool AVLTree::remove(const std::string& key) {
	// variables //
	std::string nonConstKey = key;
	std::optional<size_t> value = get(key);

	// if a value associated with the key can be found, try to remove.
	if (value.has_value()) {
		if (remove(root, nonConstKey, value.value())) {
			size_t height = getHeight();
			if (height > 1 || height < -1) {
				// TODO: rebalance
			}
			return true;
		}
	}
	return false;
}
/**
 * recursive and overloaded helper method of remove.
 *
 * @param current the current node being checked
 * @param key the key of the node being removed.
 * @return
 */
bool AVLTree::remove(AVLNode *&current, KeyType key, size_t value) {
	// BASE CASE 1: nullptr, key not in tree //
	if (current == nullptr) {
		return false;
	}
	// BASE CASE 2: key found //
	if (current->getKey() == key) {
		if (removeNode(current)) {
			return true;
		}
		return false; // shouldn't be reached in theory
	}

	// Recurse down right subtree
	if (value > current->getValue()) {
		if (remove(current->getRight(), key, value)) {
			return true;
		}
	}
	// Recurse down left subtree
	return false;
}


std::optional<size_t> AVLTree::get(const string& key) const {
	return 1;
}

/**
 *
 * @param node the node being balanced.
 */
void AVLTree::balanceNode(AVLNode *&node) {
	// Update height of Node and calculate balance factor
	updateHeight(node);
	size_t balanceFactor = getBalanceFactor(node);

	// BALANCE FACTOR > 1: Left heavy  //
	if (balanceFactor > 1) {
		// left-left (single rotation)
		if ((node->getLeft()->getLeft()->getNodeHeight()) >= (node->getLeft()->getRight()->getNodeHeight())) {
			rotateRight(node);
		}
		else { // Left-right (double rotation)
			rotateLeftRight(node);
		}
	}
	// BALANCE FACTOR < -1: Left heavy //
	if (balanceFactor < -1) {
		// right-right (single rotation)
		if (node->getRight()->getRight()->getHeight() >= (node->getRight()->getLeft()->getHeight())) {
			rotateLeft(node);
		}
		else { // right-left (double rotation)
			rotateLeftRight(node);
		}
	}
}

/**
 * Updates the height of a node by checking the height of the right and left subtree.
 * Requires the height of left and right to be accurate
 * @param node the node being updated
 */
void AVLTree::updateHeight(AVLNode*& node) {
	if (!node) return;

	// get heights of both subtrees, set to -1 if null.
	int leftHeight, rightHeight, height;

	if (node->left != nullptr) {
		leftHeight = node->left->getHeight();
	}
	else {leftHeight = -1;}

	if (node->right != nullptr) {
		rightHeight = node->right->getHeight();
	}
	else {rightHeight = -1;}

	// check which subtree is larger, use the largest to calculate height.
	if (rightHeight >= leftHeight) {
		height = rightHeight + 1;
	} else {
		height = leftHeight + 1;
	}
}

void AVLTree::updateAllHeights() {

}

size_t AVLTree::getBalanceFactor(AVLNode*& node) {
	if (!node) return 0;

	// get heights of both subtrees, set to -1 if null.
	int leftHeight, rightHeight;

	if (node->left != nullptr) {
		leftHeight = node->left->getHeight();
	} else {leftHeight = -1;}

	if (node->right != nullptr) {
		rightHeight = node->right->getHeight();
	} else {rightHeight = -1;}

	return leftHeight - rightHeight;
}

AVLTree::AVLNode* AVLTree::rotateRight(AVLNode *&node) {
	// get right node and left node of right node
	// then perform rotation
	AVLNode *left = node->left;
	AVLNode *subtree = node->getRight();

	node->right = node;
	node->left = subtree;

	updateHeight(node);
	updateHeight(left);

	node = left;
	return node;
}

AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode *&node) {
	// get right node and left node of right node
	// then perform rotation
	AVLNode *right = node->right;
	AVLNode *subTree = right->left;

	right->left = node;
	node->right = subTree;

	updateHeight(node);
	updateHeight(right);

	node = right;
	return node;
}

AVLTree::AVLNode* AVLTree::rotateLeftRight(AVLNode *&node) {
	// left rotate node->left, then right rotate node
	rotateLeft(node->left);
	return rotateRight(node);
}

AVLTree::AVLNode* AVLTree::rotateRightLeft(AVLNode *&node) {
	// right rotate node->right, then left rotate node
	rotateRight(node->right);
	return rotateLeft(node);
}


/**
 * removeNode is a helper method for remove which contains all logic for  removing the nodes.
 *
 * @param current the node being removed
 * @return returns true if current was removed, returns false otherwise.
 */
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key, smallestInRight->value); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

/**
 * Checks the height of the AVLTree by checking the left and right subtrees of root
 * recursively and returning the higher value
 * @return returns the height of the AVLTree
 */
size_t AVLTree::getHeight() const {
	return height(root);
}

/**
 * recursively gets the height of both subtrees via inorder traversal.
 *
 * @param current the current node being visited
 * @return returns the height of the AVLTree.
 */
size_t AVLTree::height(AVLNode* current) const {
	// BASE CASE: if nullptr, return empty list
	if (current == nullptr) {
		return 0;
	}
	// get the height of both subtrees, and return 1 + the larger subtree as the height
	size_t leftHeight = height(current->left);
	size_t rightHeight = height(current->right);
	if (leftHeight > rightHeight) {
		return 1 + leftHeight;
	}
	return 1 + rightHeight;
}

/*
=================
= AVLNode Class =
= ------------- =================================================
= The AVLNode class defines the nodes which make up an AVLTree. =
================================================================= */
AVLTree::AVLNode::AVLNode() {
	this->key = "";
	this->value = 0;
	this->left = nullptr;
	this->right = nullptr;
	height = 0;
}
AVLTree::AVLNode::AVLNode(std::string &key, size_t value) {
	this->key = key;
	this->value = value;
	this->left = nullptr;
	this->right = nullptr;
	height = 0;
}

void AVLTree::AVLNode::load(std::string &key, size_t value) {
	this->key = key;
	this->value = value;
}

AVLTree::AVLNode* AVLTree::AVLNode::insertRight(AVLNode* rightChild) {
	this->right = rightChild;
}

AVLTree::AVLNode* AVLTree::AVLNode::insertLeft(AVLNode* leftChild) {
	this->right = leftChild;
}

void AVLTree::AVLNode::setHeight(int height) {
	this->height = height;
}


// ACCESSORS //
std::string AVLTree::AVLNode::getKey() {
	return this->key;
}

size_t AVLTree::AVLNode::getValue() {
	return this->value;
}

size_t &AVLTree::AVLNode::getValueRef() {
	return this->value;
}

AVLTree::AVLNode *&AVLTree::AVLNode::getLeft() {
	return this->left;
}

AVLTree::AVLNode *&AVLTree::AVLNode::getRight() {
	return this->right;
}

int AVLTree::AVLNode::getNodeHeight() {
	return this->height;
}

/**
 * @return returns the number of children the AVLNode has (always 0, 1, or 2)
 */
int AVLTree::AVLNode::getNumChildren() {
	if (this->left != nullptr && this->right != nullptr) {
		return 2;
	}
	if (this->left != nullptr || this->right != nullptr) {
		return 1;
	}
	return 0;
}

bool AVLTree::AVLNode::isLeaf() {
	return this->left == nullptr && this->right == nullptr;
}




