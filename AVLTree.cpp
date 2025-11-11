/**
 * AVLTree.cpp
 * Created by Zander Little 11/08/2025
 * DESCRIPTION HERE
 */

#include "AVLTree.h"

#include <string>

/**
 * Insert a new key-value pair into the tree. After a successful insert, the tree is rebalanced if necessary.
 * Duplicate keys are disallowed
 *
 * @param key the key being inserted
 * @param value the value being inserted
 * @return returns true if the insertion is successful, returns false otherwise.
 */
bool AVLTree::insert(const std::string& key, size_t value) {
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