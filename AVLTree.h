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
	size_t& operator[](const string& key);
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
    	int getHeight();
    	int getBalance();
    	int getNumChildren();
    	bool isLeaf();


    	size_t numChildren() const;
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
    };

    private:
    AVLNode* root;
	void balanceNode(AVLNode*& node);

	/* Helper method for Insert */
	bool insertNode(string& key, size_t value, AVLNode*& current);

    /* Helper methods for remove */
    bool remove(AVLNode*& current, KeyType key, size_t value);
    bool removeNode(AVLNode*& current);


};

#endif //AVLTREE_H
