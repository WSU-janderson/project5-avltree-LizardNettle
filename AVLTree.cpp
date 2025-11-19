/**
 * AVLTree.cpp
 * Created by Zander Little 11/08/2025
 * A basic AVLTree with automatic rebalancing via single and double rotations.
 */

#include "AVLTree.h"

#include <charconv>
#include <optional>
#include <ios>
#include <iostream>
#include <string>

// The default constructor of AVLTree.
AVLTree::AVLTree() : root(nullptr) {}

/**
 * Recursively destroys all key-pair values in the AVLTree and resets root.
 */
AVLTree::~AVLTree() {
	destroy(root);
	root = nullptr;
}

/**
 * Recursively creates a deep copy of an AVLTree.
 *
 * @param other the AVLTree being copied
 */
AVLTree::AVLTree(const AVLTree& other) : root(nullptr) {
	createDeepCopy(other.getRoot());
}


size_t& AVLTree::operator[](const std::string& key) {
	AVLNode* node = getNodeRef(key, root);
	if (node != nullptr) {
		return node->value;
	}
	size_t zero = 0;
	return zero;
}


void AVLTree::operator=(const AVLTree& other) {
}

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
		return true;
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
		return (remove(root, nonConstKey, value.value()));
	}
	return false;
}

bool AVLTree::contains(const string& key) const {
	return containsRecursive(root, key);
}

bool AVLTree::containsRecursive(AVLNode* current, const string& key) const {
	// BASE CASE: if null, key not in tree
	if (current == nullptr) {
		return false;
	}
	// visit current
	if (current->getKey() == key) {
		return true;
	}
	// recurse left, then right
	if (containsRecursive(current->left, key)) {
		return true;
	}
	if (containsRecursive(current->right, key)) {
		return true;
	}
	return false;
}

/**
 * Recursively searches for the value associated with the given key.
 * @param key the key associated with the return value.
 * @return returns the value associated with the key, if it is in the tree, otherwise returns null.
 */
std::optional<size_t> AVLTree::get(const string& key) const {
	return get(key, root);
}


vector<std::string> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {}

vector<std::string> AVLTree::keys() const {
	vector<string> keys;
	keys = getAllKeys(root, keys);
	return keys;
}

vector<std::string> AVLTree::getAllKeys(AVLNode* current, vector<string>& keys) const {
	// BASE CASE: nullptr, no more nodes on this branch.
	if (current == nullptr) {
		return keys;
	}
	// recurse left
	getAllKeys(current->left, keys);

	// get current key
	keys.push_back(current->getKey());

	// recurse right
	getAllKeys(current->right, keys);

	return keys;
}

size_t AVLTree::size() const {}
/**
 * Checks the height of the AVLTree by checking the left and right subtrees of root
 * recursively and returning the higher value
 * @return returns the height of the AVLTree
 */
size_t AVLTree::getHeight() const {
	return height(root);
}

std::ostream& operator<<(ostream& os, const AVLTree& AVLTree) {
	AVLTree.printTree(os, AVLTree.root, 0);
	return os;
}

void AVLTree::printTree(ostream& os, AVLNode* current, size_t depth) const {
	// BASE CASE: no more to print down this subtree if current == nullptr.
	if (current == nullptr) {
		return;
	}
	// recurse down right subtree
	printTree(os, current->right, depth + 1);

	// print current
	for (int i = 0; i < depth; i++) {
		os << "    ";
	}
	os << "{" << current->getKey() << ": " << current->getValue() << "}" << std::endl;

	// recurse down left subtree
	printTree(os, current->left, depth + 1);
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
	this->left = leftChild;
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

size_t AVLTree::AVLNode::getHeight() {
	return this->height;
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

AVLTree::AVLNode *AVLTree::getRoot() const {
	return root;
}


/**
 * Checks the balance of node, and performs necessary rotations if
 * the balance factor is less than -1, or greater than 1.
 * @param node the node being balanced.
 */
void AVLTree::balanceNode(AVLNode *&node) {
	// Update height of Node and calculate balance factor. Abort if !node.
	if (!node) return;
	updateHeight(node);
	int balanceFactor = getBalanceFactor(node);

	// CASE 1: LEFT HEAVY (balanceFactor > 1)
	if (balanceFactor > 1) {
		// compute heights, and ensure nodes are not nullptr
		int leftLeftHeight = -1;
		int leftRightHeight = -1;

		if (node->left != nullptr) {
			if (node->left->left != nullptr) {
				leftLeftHeight = node->left->left->getHeightInteger();
			}
			if (node->left->right != nullptr) {
				leftRightHeight = node->left->right->getHeightInteger();
			}
		}
		// LL case
		if (leftLeftHeight >= leftRightHeight) {
			rotateRight(node);
		// LR case
		} else {
			rotateLeft(node->left);
			rotateRight(node);
		}
	}

	// CASE 2: RIGHT HEAVY (balanceFactor < -1).
	if (balanceFactor < -1) {
		//compute height, and ensure nodes are not nullptr
		int rightRightHeight = -1;
		int rightLeftHeight = -1;

		if (node->right != nullptr) {
			if (node->right->right != nullptr) {
				rightRightHeight = node->right->right->getHeightInteger();
			}
			if (node->right->left != nullptr) {
				rightLeftHeight = node->right->left->getHeightInteger();
			}
		}
		if (rightRightHeight >= rightLeftHeight) {
			rotateLeft(node);
		} else {
			rotateRight(node->right);
			rotateLeft(node);
		}
	}
}

int AVLTree::AVLNode::getHeightInteger() {
	return static_cast<int>(this->getHeight());
}

/**
 * Updates the height of a node by checking the height of the right and left subtree.
 * Requires the height of left and right to be accurate
 * @param node the node being updated
 */
void AVLTree::updateHeight(AVLNode*& node) {
	if (!node) return;

	// get heights of both subtrees, set to 0 if null.
	int leftHeight = 0;
	int rightHeight = 0;
	int height;

	// check for nullptrs, and get heights.
	if (node->left != nullptr) {
		leftHeight = node->left->getHeightInteger();
	}
	if (node->right != nullptr) {
		rightHeight = node->right->getHeightInteger();
	}

	// check which subtree is larger, use the largest to calculate height.
	if (leftHeight > rightHeight) {
		node->height = leftHeight + 1;
	} else {
		node->height = rightHeight + 1;
	}
}
int AVLTree::getBalanceFactor(AVLNode*& node) {
	if (!node) return 0;

	// get heights of both subtrees, set to -1 if null.
	int leftHeight = 0;
	int rightHeight = 0;

	if (node->left != nullptr) {
		leftHeight = node->left->getHeightInteger();
	}

	if (node->right != nullptr) {
		rightHeight = node->right->getHeightInteger();
	}

	return leftHeight - rightHeight;
}

AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode *&node) {
	if (!node || !node->right) {
		return node;
	}
	// get right node and left node of right node
	// then perform rotation
	AVLNode* right = node->right;
	AVLNode* rightLeft = right->left;

	right->left = node;
	node->right = rightLeft;

	updateHeight(node);
	updateHeight(right);

	node = right;
	return node;
}

AVLTree::AVLNode* AVLTree::rotateRight(AVLNode *&node) {
	if (!node || !node->left) {
		return node;
	}
	// get right node and left node of right node
	// then perform rotation
	AVLNode* left = node->left;
	AVLNode* leftRight = node->left->right;

	left->right = node;
	node->left = leftRight;

	updateHeight(node);
	updateHeight(left);

	node = left;
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
			updateHeight(current);
			balanceNode(current);
			return true;
		} else {
			std::cout << "FAILED INSERT";
			return false;
		}
	}
	else if (val < current->getValue()) {
		// left subtree
		if (insertNode(key, val, current->getLeft())) {
			updateHeight(current);
			balanceNode(current);
			return true;
		} else {
			std::cout << "FAILED INSERT";
			return false;
		}
	}
	return false;
}

/**
 * recursive and overloaded helper method of remove.
 *
 * @param current the current node being checked
 * @param key the key of the node being removed.
 * @return returns true if the node was removed, returns false otherwise.
 */
bool AVLTree:: remove(AVLNode *&current, KeyType key, size_t value) {
	// BASE CASE 1: nullptr, key not in tree //
	if (current == nullptr) {
		return false;
	}
	bool result = false;

	// BASE CASE 2: key found //
	if (current->getKey() == key) {
		if (removeNode(current)) {
			return true;
		}
		return false; // shouldn't be reached in theory
	}

	// Recurse down right subtree
	if (value > current->getValue()) {
		result = remove(current->left, key, value);
		if (remove(current->getRight(), key, value)) {
			updateHeight(current);
			balanceNode(current);
			return true;
		}
	}
	// Recurse down left subtree
	else if (value < current->getValue()) {
		if (remove(current->getLeft(), key, value)) {
			updateHeight(current);
			balanceNode(current);
			return true;
		}
	}
	// if successful, update height and rebalance
	if (!result) return false;
	updateHeight(current);
	balanceNode(current);
	return true;
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
	// auto nChildren = current->getNumChildren();
	if (current->isLeaf()) {
		// CASE 1 - Leaf - we can delete the node.
		current = nullptr;
	} else if (current->getNumChildren() == 1) {
		// CASE 1 - One child - replace current with its only child
		if (current->right) {
			current = current->right;
		} else {
			current = current->left;
		}
	} else {
		// CASE 3 - Two children
		// get the smallest key in the right subtree
		AVLNode* smallestInRight = current->right;

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
 *
 * @param key the key being searched for
 * @param current the current node being checked
 * @return returns the value associated with the key, if it exists.
 */
std::optional<size_t> AVLTree::get(const string& key, AVLNode* current) const {
	// BASE CASE 1: nullptr, key not in tree //
	if (current == nullptr) {
		return false;
	}
	// recurse left
	optional<size_t> result = get(key, current->left);
	if (result.has_value()) {
		return result;
	}

	// BASE CASE 2: key found, return //
	if (current->getKey() == key) {
		return current->getValue();
	}
	// recurse right
	result = get(key, current->right);
	if (result.has_value()) {
		return result;
	}
	return nullopt;
}

/**
 * Recursive helper method of ~AVLTree. Destroys all nodes
 * in the tree using postorder traversal.
 * @param current the current node being destroyed
 */
void AVLTree::destroy(AVLNode *&current) {
	if (current == nullptr) return;
	// go down subtrees before destroying node
	destroy(current->left);
	destroy(current->right);
	delete current;
}

/**
 * Recursive helper method of the deep copy constructor. Uses pre-order traversal.
 * @param current current node being copied
 */
void AVLTree::createDeepCopy(AVLNode *current) {
	if (current == nullptr) {
		return;
	}
	// insert current
	insert(current->getKey(), current->getValue());
	// recurse left, then right
	createDeepCopy(current->left);
	createDeepCopy(current->right);
}

/**
 * Recursive helper method for operator[].
 * @param key the key being searched for
 * @param current the current node being checked
 * @return returns the node associated with the key if it is found, returns nullptr otherwise.
 */
AVLTree::AVLNode* AVLTree::getNodeRef(const string& key, AVLNode* current) {
	// BASE CASE 1: nullptr, key not in tree //
	if (current == nullptr) {
		return nullptr;
	}
	// recurse left
	AVLNode* result = getNodeRef(key, current->left);
	if (result != nullptr) return result;

	// BASE CASE 2: key found, return //
	if (current->getKey() == key) {
		return current;
	}
	// recurse right
	result = getNodeRef(key, current->right);
	if (result != nullptr) return result;
	return nullptr;
}