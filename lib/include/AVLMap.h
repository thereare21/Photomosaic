//
// Created by Raymond Tsai on 10/25/23.
//

#ifndef PHOTOMOSAIC_AVLMAP_H
#define PHOTOMOSAIC_AVLMAP_H

template <typename K, typename V>
class AVLMap {
private:
    class AVLNode {
    public:
        K key;
        V value;
        AVLNode* left;
        AVLNode* right;

        int height;

        AVLNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr), height(0) {};

        //returns the balance factor of this node.
        int getBalanceFactor() {
            return left->getHeight() - right->getHeight();
        }

        //returns the height of this node
        int getHeight() {
            if (this == nullptr) {
                return 0;
            } else {
                return this->height;
            }
        }

        //calculates the new height based on its children, updates height accordingly
        void updateHeight() {
            if (this == nullptr) {
                return;
            } else {
                this->height = 1 + std::max(this->left->getHeight(), this->right->getHeight());
            }
        }

        //prints all the elements within the current node and children
        void printAll() {
            printValue();
            if (left != nullptr && right != nullptr) {
                left->printAll();
                right->printAll();
            }
        }

        //prints the key of the node, as well as the left and right keys, if they exist
        void printValue() {
            if (this != nullptr) {
                std::cout << "(" << key << " " << value << ") Height: " << height;
                if (this->left != nullptr) {
                    std::cout << " Left: " << this->left->key;
                }
                if (this->right != nullptr) {
                    std::cout << " Right: " << this->right->key;
                }
                std::cout << std::endl;
            }
        }
    };

    //the root will start off as null pointer.
    AVLNode* root = nullptr;

    //inserts new node with key K and value v at the given node
    //updates the current node accordingly
    //performs rotations as needed
    void insert(AVLNode*& node, const K& k, const V& v) {
        if (node == nullptr) {
            node = new AVLNode(k, v);
        } else if (*k < node->key) {
            if (node->left == nullptr) {
                node->left = new AVLNode(k, v);
                node->left->updateHeight();
            } else {
                insert(node->left, k, v);
            }
        } else if (*k > node->key) {
            if (node->right == nullptr) {
                node->right = new AVLNode(k, v);
                node->right->updateHeight();
            } else {
                insert(node->right, k, v);
            }
        } else {
            node-> value = v; //if already exists, update old value with the new one
        }

        //update the height of the given node once inserted.
        node->updateHeight();
        int balanceFactor = node->getBalanceFactor();

        //perform the necessary rotations
        performRotations(node, k, balanceFactor);
    }

    //performs necessary rotations after insertion
    void performRotations(AVLNode*& node, const K& k, int balanceFactor) {
        // Left Heavy
        if (balanceFactor > 1) {
            if (*k < node->left->key) {
                node = rightRotate(node); // Left-Left case
            } else {
                node->left = leftRotate(node->left); // Left-Right case
                node = rightRotate(node); // Left-Left case
            }
        }
        // Right Heavy
        if (balanceFactor < -1) {
            if (*k > node->right->key) {
                node = leftRotate(node); // Right-Right case
            } else {
                node->right = rightRotate(node->right); // Right-Left case
                node = leftRotate(node); // Right-Right case
            }
        }
    }

    //right rotation
    AVLNode* rightRotate(AVLNode* x) {
        AVLNode* y = x->left;
        AVLNode* T2 = y->right;

        y->right = x;
        x->left = T2;

        x->updateHeight();
        y->updateHeight();

        //update the root if it was swapped
        if (x == root) {
            root = y;
        }

        return y;
    }

    //left rotation
    AVLNode* leftRotate(AVLNode* y) {
        AVLNode* x = y->right;
        AVLNode* T2 = x->left;

        x->left = y;
        y->right = T2;

        //update heights accordingly
        y->updateHeight();
        x->updateHeight();

        //update the root if it was swapped
        if (y == root) {
            root = x;
        }

        return x;
    }

    //prints all elements in the AVLMap with its left and right neighbors
    void printAll() {
        if (root != nullptr) {
            root->printAll();
        }
    }



public:
    //insert a node with the given key and value into the AVLMap
    void insert(const K k, const V v) {
        insert(root, k, v);
        //balance
    }

    //return the value of the Node with the closest key to the given key
    V& search(K k) {
        /*
        if (root != nullptr) {
            return search(root, k);
        }*/
        AVLNode* closest = nullptr;
        AVLNode* currNode = root;
        while (currNode != nullptr) {

            if (*currNode->key == k) {
                return currNode->value;
            }

            if (closest == nullptr || std::abs(*currNode->key - k) < std::abs(*closest->key - k)) {
                closest = currNode;
                //std::cout << " -> " << closest->key << " " << closest->height;
            }

            if (*k > currNode->key) {
                currNode = currNode->right;
            } else if (*k < currNode->key) {
                currNode = currNode->left;
            }
        }
        //std::cout << std::endl;
        //std::cout << "Found " << closest->key << " Looking for: " << k << std::endl;
        return closest->value;
    }

    //DONE: update balance factors in the insert function DONE
    //DONE: detect a rotate scenario
    //DONE: code each rotation scheme LL RR LR RL


    //prints all elements in the AVLMap with its left and right neighbors
    void printAllElements() {
        printAll();
    }
};


#endif //PHOTOMOSAIC_AVLMAP_H
