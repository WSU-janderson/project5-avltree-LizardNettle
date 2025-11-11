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
	else { // should in theory only reach this when there's a duplicate value
		return false;
	}
	return false;
}

/**
 *
 * @param key the key being removed from the AVLTree
 * @return returns true if the key was found and removed, returns false otherwise.
 */
bool AVLTree::remove(const std::string& key) {
	return false;
}
/**
 * recursive and overloaded helper method of remove. DESCRIBE METHOD FURTHER.
 *
 * @param current the current node being checked
 * @param key the key of the node being removed.
 * @return
 */
bool AVLTree::remove(AVLNode *&current, KeyType key) {
	return false;
}


void AVLTree::balanceNode(AVLNode *&node) {
}

/**
 * removeNode contains all of the logic for actually removing the nodes.
 * Helper method for remove.
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
        remove(root, smallestInRight->key); // delete this one

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
 * @return returns the number of children the AVLNode has (always 0, 1, or 2)
 */
size_t AVLTree::AVLNode::numChildren() const {
	if (this->left != nullptr && this->right != nullptr) {
		return 2;
	}
	if (this->left != nullptr || this->right != nullptr) {
		return 1;
	}
	return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
	return this->left == nullptr && this->right == nullptr;
}

/**
 * checks the height of the AVLTree by checking against a list of all BSTNodes
 * and returning the largest height value.
 * @return returns the height of the AVLTree
 */
size_t AVLTree::AVLNode::getHeight() const {
	return 0;
}