//
// Created by zande on 11/10/2025.
//

#include "BSTNode.h"

using namespace std;

/**
 * initialize with no values
 */
BSTNode::BSTNode() {
	this->key = "";
	this->value = 0;
	this->left = nullptr;
	this->right = nullptr;
	height = 0;
}
BSTNode::BSTNode(std::string &key, size_t value) {
	this->key = key;
	this->value = value;
	this->left = nullptr;
	this->right = nullptr;
	height = 0;
}

void BSTNode::load(std::string &key, size_t value) {
	this->key = key;
	this->value = value;
}

BSTNode* BSTNode::insertRight(BSTNode* rightChild) {
	this->right = rightChild;
}

BSTNode* BSTNode::insertLeft(BSTNode* leftChild) {
	this->left = leftChild;
}

void BSTNode::setHeight(int height) {
	this->height = height;
}

// getters
std::string BSTNode::getKey() {
	return this->key;
}

size_t BSTNode::getValue() {
	return this->value;
}

size_t& BSTNode::getValueRef() {
	return this->value;
}

BSTNode* BSTNode::getLeft() {
	return this->left;
}
BSTNode* BSTNode::getRight() {
	return this->right;
}

int BSTNode::getHeight() {
	return this->height;
}

int BSTNode::getBalance() {}

bool BSTNode::isLeaf() {
	return this->left == nullptr && this->right == nullptr;
}


