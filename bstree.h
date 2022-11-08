#include <iostream>
#include <optional>

template <typename T, typename U>
class BSNode {

public:
    T key;
    U value;
    BSNode<T, U>* left;
    BSNode<T, U>* right;

    BSNode<T, U>(const T& k, const U& v)
    {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
    }

};

template<typename T, typename U>
class BSTree {

public:
    BSNode<T, U>* root = nullptr;
    ~BSTree() {
        removeall(root);
    }

    bool insert(const T& key, const U& value);
    U search(const T& key);
    bool remove(const T& key);

    //for checking
    void preorder(BSNode<T, U>*& node) {
        if (!node) return;

        std::cout << node->key << ": " << node->value << std::endl;
        preorder(node->left);
        preorder(node->right);
    }
    void inorder(BSNode<T, U>*& node) {
        if (!node) return;

        inorder(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        inorder(node->right);
    }

private:
    bool insert(BSNode<T, U>*& node, const T& key, const U& value);
    U search(BSNode<T, U>*& node, const T& key);
    BSNode<T, U>* remove(BSNode<T, U>*& node, const T& key);
    void removeall(BSNode<T, U>*& node);
};


template<typename T, typename U>
bool BSTree<T, U>::insert(const T& key, const U& value) {
    return insert(root, key, value);
}

template<typename T, typename U>
U BSTree<T, U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool BSTree<T, U>::remove(const T& key) {
    if (!search(root, key)) return false;
    remove(root, key);
    return true;
}


template<typename T, typename U>
bool BSTree<T, U>::insert(BSNode<T, U>*& node, const T& key, const U& value) {
   
    // if null root
    if (node == nullptr)
    {
        node = new BSNode<T, U>(key, value);
        return true;
    }
    // same key update value
    if (key.compare(node->key) == 0)
    {
        node->value = value;
        return false;
    }
    // key is smaller
    if (key.compare(node->key) < 0)
    {
		if (node->left == nullptr)
			node->left = new BSNode<T, U>(key, value);
		
		else insert(node->left, key, value); // traverse again
    }
    // key is greater
    else if (key.compare(node->key) > 0)
    {
        if (node->right == nullptr)
            node->right = new BSNode<T, U>(key, value);
        
        else insert(node->right, key, value);
    }
	return true;
}

template<typename T, typename U>
U BSTree<T, U>::search(BSNode<T, U>*& node, const T& key) {

    BSNode<T, U>* temp = node;
	
    while (temp) // loop until key is found or reaches the leaf nodes
    {
        if (key.compare(temp->key) == 0) return copy->value;
        if (key.compare(temp->key) < 0)
        {
            temp = temp->left;
        }
        else if (key.compare(temp->key) > 0)
        {
            temp = temp->right;
        }
    }
    if (temp == nullptr) return 0; // if not found return 0
    return temp->value;
}

template<typename T, typename U>
BSNode<T, U>* BSTree<T, U>::remove(BSNode<T, U>*& node, const T& key) {
	// the public remove function deals with the case when key doesn't exist

    // root is null
	if (node == nullptr)
	{
		return NULL;
	}
    // key smaller than current node key
    if (key.compare(node->key) < 0) node->left = remove(node->left, key);
    // key greater than current node key
    else if (key.compare(node->key) > 0) node->right = remove(node->right, key);

    // same key
    else
    {
        // no child
        if (node->left == NULL && node->right == NULL)
		{
			delete(node);
			node = nullptr;
			return NULL; 
		}
        // one right child: copy the child, delete node, redefine node
        else if (node->left == NULL) {
			BSNode<T, U>* temp;
			temp = node->right;
			delete(node);
			node = temp;
			return node;
        }
        // one left child
        else if (node->right == NULL) {
			BSNode<T, U>* temp;
			temp = node->left;
			delete(node);
			node = temp;
			return node;
        }
        // two children
        else
        {
			// find min of right subtree, copy temp values to node, delete temp from the subtrees
            BSNode<T, U>* temp;
            temp = node->right;
            while (temp && temp->left != nullptr)
            {
                temp = temp->left;
            }
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }
    return node;
}

template<typename T, typename U>
void BSTree<T, U>::removeall(BSNode<T, U>*& node) {
	// when node is null return
    if (!node) return;

	// traverse the tree to delete nodes
    removeall(node->left);
    removeall(node->right);
    delete(node);
	node = nullptr;
}

