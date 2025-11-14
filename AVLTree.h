/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
	AVLTree();
	~AVLTree();

	AVLTree(const AVLTree& other);
	size_t& operator[](const std::string& key);
	void operator=(const AVLTree& other);
    using KeyType = std::string;
    using ValueType = size_t;

	bool insert(const string& key, size_t value);
	bool remove(const string& key);
	bool contains(const string& key) const;
	std::optional<size_t> get(const string& key) const;
	vector<std::string> findRange(const std::string& lowKey, const std::string& highKey) const;
	vector<std::string> keys() const;
	size_t size() const;
	size_t getHeight() const;

	friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;
        AVLNode* left;
        AVLNode* right;

    	AVLNode();
    	AVLNode(std::string &key, size_t value);

    	void load(std::string &key, size_t value);
    	AVLNode* insertRight(AVLNode* rightChild);
    	AVLNode* insertLeft(AVLNode* leftChild);
    	void setHeight(int height);

    	std::string getKey();
    	size_t getValue();
    	size_t& getValueRef();
		AVLNode *&getLeft();
		AVLNode *&getRight();
    	int getNodeHeight();
    	int getBalance();
    	int getNumChildren();
    	bool isLeaf();
        size_t getHeight() const;
    };

    private:
    AVLNode* root;
	AVLNode* getRoot() const;
	/* Methods for rebalancing */
	void balanceNode(AVLNode*& node);
	void updateHeight(AVLNode*& node);
	// void updateAllHeights();
	size_t getBalanceFactor(AVLNode*& node);
	AVLNode* rotateLeft(AVLNode*& node);
	AVLNode* rotateRight(AVLNode*& node);
	AVLNode* rotateLeftRight(AVLNode*& node);
	AVLNode* rotateRightLeft(AVLNode*& node);

	/* Recursive helper methods */
	size_t height(AVLNode* current) const;
	size_t inorderTraversal(AVLNode*& current);
	bool insertNode(string& key, size_t value, AVLNode*& current);
	bool remove(AVLNode*& current, KeyType key, size_t value);
    bool removeNode(AVLNode*& current);
	optional<size_t> get(const string& key, AVLNode* current) const;
	void destroy(AVLNode*& current);
	void createDeepCopy(AVLNode* current);
	AVLNode* getNodeRef(const string& key, AVLNode* current);


};

#endif //AVLTREE_H
