#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
using namespace std;

class AVLNode {
private:
    string month;
    string artist;
    string title;
    string label;
    int year;
    int weeks;
    int balanceFactor;
    AVLNode* left;
    AVLNode* right;

public:
    AVLNode(string mon, int yr, string singer, string song, string house, int noWeeks)
        : month(mon), year(yr), artist(singer), title(song), label(house),
          weeks(noWeeks), balanceFactor(0), left(nullptr), right(nullptr) {}

    // Accessors
    AVLNode* getLeft() { return left; }
    AVLNode* getRight() { return right; }
    string getTitle() { return title; }
    int getBalanceFactor() { return balanceFactor; }

    string getData() {
        return month + " | " + to_string(year) + " | " + artist + " | " +
               title + " | " + label + " | " + to_string(weeks) +
               " (" + to_string(balanceFactor) + ")\n";
    }

    // Mutators
    void setLeft(AVLNode* ptr) { left = ptr; }
    void setRight(AVLNode* ptr) { right = ptr; }
    void setBalanceFactor(int bf) { balanceFactor = bf; }
};

class AVLTree {
private:
    AVLNode* root;

    // Helper functions
    int height(AVLNode* node) {
        if (!node) return 0;
        return 1 + max(height(node->getLeft()), height(node->getRight()));
    }

    int getBalance(AVLNode* node) {
        if (!node) return 0;
        return height(node->getLeft()) - height(node->getRight());
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->getLeft();
        AVLNode* T2 = x->getRight();

        x->setRight(y);
        y->setLeft(T2);

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->getRight();
        AVLNode* T2 = y->getLeft();

        y->setLeft(x);
        x->setRight(T2);

        return y;
    }

    AVLNode* insertHelper(AVLNode* node, string mon, int yr, string singer,
                          string song, string house, int noWeeks) {
        if (!node)
            return new AVLNode(mon, yr, singer, song, house, noWeeks);

        if (song < node->getTitle())
            node->setLeft(insertHelper(node->getLeft(), mon, yr, singer, song, house, noWeeks));
        else if (song > node->getTitle())
            node->setRight(insertHelper(node->getRight(), mon, yr, singer, song, house, noWeeks));
        else
            return node;

        int balance = getBalance(node);
        node->setBalanceFactor(balance);

        // Balancing cases
        if (balance > 1 && song < node->getLeft()->getTitle())
            return rightRotate(node);

        if (balance < -1 && song > node->getRight()->getTitle())
            return leftRotate(node);

        if (balance > 1 && song > node->getLeft()->getTitle()) {
            node->setLeft(leftRotate(node->getLeft()));
            return rightRotate(node);
        }

        if (balance < -1 && song < node->getRight()->getTitle()) {
            node->setRight(rightRotate(node->getRight()));
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->getLeft())
            current = current->getLeft();
        return current;
    }

    AVLNode* deleteHelper(AVLNode* node, string song) {
        cout << "Looking at node: " << (node ? node->getTitle() : "NULL") << endl;

        if (!node) return node;

        if (song < node->getTitle())
            node->setLeft(deleteHelper(node->getLeft(), song));
        else if (song > node->getTitle())
            node->setRight(deleteHelper(node->getRight(), song));
        else {
            // Case: node has only one child or no child
            if (!node->getLeft() || !node->getRight()) {
                AVLNode* temp = node->getLeft() ? node->getLeft() : node->getRight();
                cout << "Deleting node: " << node->getTitle() << endl;
                delete node;
                return temp;
            }

            // Case: node has two children
            cout << "Finding inorder successor for: " << node->getTitle() << endl;
            AVLNode* temp = minValueNode(node->getRight());
            cout << "Successor is: " << temp->getTitle() << endl;
            node->setRight(deleteHelper(node->getRight(), temp->getTitle()));

            return node;
        }

        int balance = getBalance(node);
        node->setBalanceFactor(balance);

        if (balance > 1 && getBalance(node->getLeft()) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalance(node->getLeft()) < 0) {
            node->setLeft(leftRotate(node->getLeft()));
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->getRight()) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalance(node->getRight()) > 0) {
            node->setRight(rightRotate(node->getRight()));
            return leftRotate(node);
        }

        return node;
    }

    string inOrderHelper(AVLNode* node) {
        if (!node) return "";
        return inOrderHelper(node->getLeft()) + node->getData() + inOrderHelper(node->getRight());
    }

    string preOrderHelper(AVLNode* node) {
        if (!node) return "";
        return node->getData() + preOrderHelper(node->getLeft()) + preOrderHelper(node->getRight());
    }

    string postOrderHelper(AVLNode* node) {
        if (!node) return "";
        return postOrderHelper(node->getLeft()) + postOrderHelper(node->getRight()) + node->getData();
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string mon, int yr, string singer, string song,
                string house, int noWeeks) {
        root = insertHelper(root, mon, yr, singer, song, house, noWeeks);
    }

    void remove(string song) {
        root = deleteHelper(root, song);
    }

    string inOrder() { return inOrderHelper(root); }
    string preOrder() { return preOrderHelper(root); }
    string postOrder() { return postOrderHelper(root); }
};

#endif
