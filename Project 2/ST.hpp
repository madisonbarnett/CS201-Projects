#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>

#include "RBT.hpp"
#include "RBTPrint.hpp"

/*  
	Name: Madison Barnett
	Email: mtbarnett@crimson.ua.edu
	Course Section: Fall 2024 CS 201-002  
	Homework #: 2
*/  

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
	typedef RBTNode<Key, Type>* iterator;

	// Constructors
	// constant
	ST() {
		this->nodeCount = 0; // initialize nodeCount as 0 and root as nullptr
		this->root = nullptr;
	}; 

	// Destructor
	// linear in the size of the ST
	~ST() {
		this->DeleteTree(this->root); // Call RBT.hpp DeleteTree function
		this->root = nullptr; // Reset root and nodeCount to represent empty tree
		this->nodeCount = 0;
	};

	// access or insert specifies element
	// inserts if the key is not present and returns a reference to
	// the value corresponding to that key
	// O(LogN), N size of ST
	Type& operator[](const Key& key) {
		RBTNode<Key, Type>* correctNode = this->Search(key); // Search to determine if node already exists
		if (correctNode != nullptr) {
			return correctNode->value; // if present, access node and return value
		}
		else {
			correctNode = new RBTNode<Key, Type>(key, Type(), nullptr, true, nullptr, nullptr); // Declare new node & insert if not already in ST
        	this->InsertNode(correctNode); 
			this->nodeCount = this->nodeCount + 1; // Increase nodeCount
        	return correctNode->value;
		}
	}; 

	// insert a (key, value) pair, if the key already exists
	// set the new value to the existing key
	// O(LogN), N size of ST
	void insert(const Key& key, const Type& value) {
		RBTNode<Key, Type>* foundNode = this->Search(key); // RBT.hpp search function to determine if node already exists
		if (foundNode != nullptr) {
			foundNode->value = value; // If already exists, update value
		}
		else { // Else declare new node, insert into ST, and update nodeCount
			RBTNode<Key, Type>* newNode = new RBTNode<Key, Type>(key, value, nullptr, true, nullptr, nullptr); 
			this->InsertNode(newNode);
			this->nodeCount = this->nodeCount + 1;
		}
	};

	// remove element at the given position
	// amortized constant
	void remove(iterator position) {
		this->RemoveNode(position); // Call to RBT.hpp RemoveNode to remove node at given position
		this->nodeCount = this->nodeCount - 1; // Reduce nodeCount
	};

    // remove element with keyvalue key and 
	// return number of elements removed (either 0 or 1)
	// O(logN), N size of ST
	std::size_t remove(const Key& key) {
		if (this->Remove(key)) { // Remove() from RBT.hpp removes node and returns true if node is found in tree
			this->nodeCount = this->nodeCount - 1;
			return 1;
		}
		else { // Remove() returned false, no node was removed
			return 0;
		}
	};  

	// removes all elements from the ST, after this size() returns 0
	// linear in the size of the ST
	void clear() {
		this->DeleteTree(this->root); // RBT.hpp DeleteTree() recursively deletes nodes from tree
    	this->root = nullptr;          
    	this->nodeCount = 0; // Reset root and nodeCount values to represent an empty tree
	}; 

	// checks if ST has no elements; true is empty, false otherwise
	// constant
	bool empty() const {
		if (this->root == nullptr) { // if root == nullptr, tree is empty
			return true;
		}
		else {
			return false;
		}
	}; 

	// returns number of elements in ST
	// constant
	std::size_t size() const {	
		//return this->root->Count();
		return this->nodeCount; // return private member nodeCount that maintains number of elements in ST
	}; 

	// returns number of elements that match keyvalue key
	// value returned is 0 or 1 since keys are unique
	// O(LogN), N size of ST
	std::size_t count(const Key& key) {
		RBTNode<Key, Type>* foundNode = this->Search(key); // RBT.hpp Search() returns node with matching key
		if (foundNode == nullptr) { // if returned node is nullptr, key doesn't exist in tree
			return 0;
		}
		else {
			return 1;
		}
	}; 

	// find an element with keyvalue key and return 
	// the iterator to the element found, nullptr if not found
	// O(LogN), N size of ST
	iterator find(const Key& key) {
		iterator foundNode = this->Search(key); // utilizes iterator member declared at beginning and RBT.hpp Search()
		return foundNode; 
	};

	// check if key exists in ST
	// O(LogN), N size of ST
	bool contains(const Key& key) {
		RBTNode<Key, Type>* foundNode = this->Search(key);
		if (foundNode == nullptr) { // Key doesn't exist in ST if Search(key) returns nullptr
			return false; 
		}
		else {
			return true;
		}
	};

    // return contents of ST as a vector of (key,value) pairs
    // O(N), N size of ST
	// make this inorder
	std::vector<std::pair<Key, Type>> toVector() {
		std::vector<std::pair<Key, Type>> STVector;
		inorder(this->GetRoot(), STVector); // Helper function returns ST as a vector representing inorder traversal of the RBT
		
		return STVector;
    };

	// print the symbol table as Red-Black Tree
	// O(N), N size of ST
	void displayTree() {
		std::cout << RBTPrint<Key,Type>::TreeToString(RedBlackTree<Key,Type>::root) << std::endl;
	};

	// print the symbol table in sorted order
	// O(N), N size of ST
	void display() {
		std::vector<std::pair<Key, Type>> STtable = this->toVector();
		for (int i = 0; i<STtable.size(); i++) {
			std::cout << STtable[i].first << ": " << STtable[i].second << std::endl; // Prints each value of the inorder vector in specified format
		}
		/*for (int i = STtable.size() - 1; i >= 0; i--) {
			std::cout << STtable[i].first << ": " << STtable[i].second << std::endl;
		}
		*/
	};

private:
	std::size_t nodeCount;

	void inorder(RBTNode<Key, Type>* root, std::vector<std::pair<Key, Type>>& RBTvector) {
		if (root == nullptr) {
			return;
		}

		inorder(root->left, RBTvector);
		RBTvector.push_back(std::make_pair(root->key, root->value));
		inorder(root->right, RBTvector);
		return;
	}

	//vector

};

#endif
