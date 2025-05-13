#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <string>

using namespace std;

class SplayNode {
private:
    string month;
    string artist;
    string title;
    string label;
    int year;
    int weeks;

    SplayNode* left;
    SplayNode* right;

public:
    SplayNode(string mon, int yr, string singer, string song, string house, int noWeeks)
        : month(mon), year(yr), artist(singer), title(song),
          label(house), weeks(noWeeks), left(nullptr), right(nullptr) {}

    SplayNode* getLeft() { return left; }
    SplayNode* getRight() { return right; }
    string getTitle() { return title; }

    void setLeft(SplayNode* ptr) { left = ptr; }
    void setRight(SplayNode* ptr) { right = ptr; }

    string getData() {
        return month + " | " + to_string(year) + " | " + artist + " | " +
               title + " | " + label + " | " + to_string(weeks) + "\n";
    }
};

class SplayTree {
private:
    SplayNode* root;

    SplayNode* rightRotate(SplayNode* x) {
        SplayNode* y = x->getLeft();
        x->setLeft(y->getRight());
        y->setRight(x);
        return y;
    }

    SplayNode* leftRotate(SplayNode* x) {
        SplayNode* y = x->getRight();
        x->setRight(y->getLeft());
        y->setLeft(x);
        return y;
    }

    SplayNode* splay(SplayNode* root, const string& title) {
        if (!root || root->getTitle() == title)
            return root;

        // Left subtree
        if (title < root->getTitle()) {
            if (!root->getLeft()) return root;

            // Zig-Zig (Left Left)
            if (root->getLeft() && root->getLeft()->getLeft() &&
                title < root->getLeft()->getLeft()->getTitle()) {
                root->setLeft(splay(root->getLeft()->getLeft(), title));
                root = rightRotate(root);
            }
            // Zig-Zag (Left Right)
            else if (root->getLeft() && root->getLeft()->getRight() &&
                    title > root->getLeft()->getRight()->getTitle()) {
                root->getLeft()->setRight(splay(root->getLeft()->getRight(), title));
                if (root->getLeft()->getRight())
                    root->setLeft(leftRotate(root->getLeft()));
}

            return (root->getLeft() == nullptr) ? root : rightRotate(root);
        }

        // Right subtree
        else {
            if (!root->getRight()) return root;

            // Zag-Zig (Right Left)
            if (root->getRight() && root->getRight()->getLeft() &&
                title < root->getRight()->getLeft()->getTitle()) {
                root->getRight()->setLeft(splay(root->getRight()->getLeft(), title));
                if (root->getRight()->getLeft())
                    root->setRight(rightRotate(root->getRight()));
            }
            // Zag-Zag (Right Right)
            else if (root->getRight() && root->getRight()->getRight() &&
                    title > root->getRight()->getRight()->getTitle()) {
                root->setRight(splay(root->getRight()->getRight(), title));
                root = leftRotate(root);
            }

            return (root->getRight() == nullptr) ? root : leftRotate(root);
        }
    }

    SplayNode* insertHelper(SplayNode* node, string mon, int yr, string singer,
                            string song, string house, int noWeeks) {
        if (!node)
            return new SplayNode(mon, yr, singer, song, house, noWeeks);

        // Defensive: splay might return null (shouldn't, but guard it)
        cout << "SPLAY DEBUG — splaying for title: " << song << endl;
        node = splay(node, song);
        cout << "SPLAY DEBUG — done splaying." << endl;

        if (!node) {
        cout << "SPLAY DEBUG — splay returned null. Skipping insert." << endl;
        return nullptr;
    }
        if (node && song == node->getTitle()) return node;

        SplayNode* newNode = new SplayNode(mon, yr, singer, song, house, noWeeks);

        if (song < node->getTitle()) {
            newNode->setRight(node);
            newNode->setLeft(node->getLeft());
            node->setLeft(nullptr);
        } else {
            newNode->setLeft(node);
            newNode->setRight(node->getRight());
            node->setRight(nullptr);
        }

        return newNode;
    }

    SplayNode* deleteHelper(SplayNode* node, const string& title) {
        if (!node) return nullptr;

        node = splay(node, title);
        if (node->getTitle() != title) return node;

        SplayNode* temp;
        if (!node->getLeft()) {
            temp = node->getRight();
        } else {
            temp = splay(node->getLeft(), title);
            temp->setRight(node->getRight());
        }

        delete node;
        return temp;
    }

    string inOrderHelper(SplayNode* node) {
        if (!node) return "";
        return inOrderHelper(node->getLeft()) +
               node->getData() +
               inOrderHelper(node->getRight());
    }

    string preOrderHelper(SplayNode* node) {
        if (!node) return "";
        return node->getData() +
               preOrderHelper(node->getLeft()) +
               preOrderHelper(node->getRight());
    }

    string postOrderHelper(SplayNode* node) {
        if (!node) return "";
        return postOrderHelper(node->getLeft()) +
               postOrderHelper(node->getRight()) +
               node->getData();
    }


public:

    string deleteNode(const string& title) {
        root = deleteHelper(root, title);
        return "Deleted: " + title;
    }

    SplayTree() : root(nullptr) {}

    void insert(string mon, int yr, string singer, string song,
                string house, int noWeeks) {
        root = insertHelper(root, mon, yr, singer, song, house, noWeeks);
    }

    void remove(string title) {
        root = deleteHelper(root, title);
    }

    string inOrder() { return inOrderHelper(root); }
    string preOrder() { return preOrderHelper(root); }
    string postOrder() { return postOrderHelper(root); }
};

#endif
