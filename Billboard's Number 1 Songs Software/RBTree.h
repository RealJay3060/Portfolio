#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

class RBNode {
private:
    string month;
    string artist;
    string title;
    string label;
    int year;
    int weeks;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

public:
    RBNode(string mon, int yr, string singer, string song,
           string house, int noWeeks, Color c = RED)
        : month(mon), year(yr), artist(singer), title(song),
          label(house), weeks(noWeeks), color(c),
          left(nullptr), right(nullptr), parent(nullptr) {}

    // Accessors
    RBNode* getLeft() { return left; }
    RBNode* getRight() { return right; }
    RBNode* getParent() { return parent; }
    Color getColor() { return color; }
    string getTitle() { return title; }

    string getData() {
        string colorStr = (color == RED) ? "R" : "B";
        return month + " | " + to_string(year) + " | " + artist + " | " +
               title + " | " + label + " | " + to_string(weeks) +
               " [" + colorStr + "]\n";
    }

    // Mutators
    void setLeft(RBNode* ptr) { left = ptr; }
    void setRight(RBNode* ptr) { right = ptr; }
    void setParent(RBNode* ptr) { parent = ptr; }
    void setColor(Color c) { color = c; }
};

class RBTree {
private:
    RBNode* root;
    RBNode* nil;

    void leftRotate(RBNode* x) {
        RBNode* y = x->getRight();
        x->setRight(y->getLeft());

        if (y->getLeft() != nil)
            y->getLeft()->setParent(x);

        y->setParent(x->getParent());

        if (x->getParent() == nil)
            root = y;
        else if (x == x->getParent()->getLeft())
            x->getParent()->setLeft(y);
        else
            x->getParent()->setRight(y);

        y->setLeft(x);
        x->setParent(y);
    }

    void rightRotate(RBNode* y) {
        RBNode* x = y->getLeft();
        y->setLeft(x->getRight());

        if (x->getRight() != nil)
            x->getRight()->setParent(y);

        x->setParent(y->getParent());

        if (y->getParent() == nil)
            root = x;
        else if (y == y->getParent()->getRight())
            y->getParent()->setRight(x);
        else
            y->getParent()->setLeft(x);

        x->setRight(y);
        y->setParent(x);
    }

    void insertFixup(RBNode* z) {
        while (z->getParent()->getColor() == RED) {
            if (z->getParent() == z->getParent()->getParent()->getLeft()) {
                RBNode* y = z->getParent()->getParent()->getRight();
                if (y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getRight()) {
                        z = z->getParent();
                        leftRotate(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    rightRotate(z->getParent()->getParent());
                }
            } else {
                RBNode* y = z->getParent()->getParent()->getLeft();
                if (y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getLeft()) {
                        z = z->getParent();
                        rightRotate(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    leftRotate(z->getParent()->getParent());
                }
            }
        }
        root->setColor(BLACK);
    }

    void transplant(RBNode* u, RBNode* v) {
        if (u->getParent() == nil)
            root = v;
        else if (u == u->getParent()->getLeft())
            u->getParent()->setLeft(v);
        else
            u->getParent()->setRight(v);

        v->setParent(u->getParent());
    }

    RBNode* minimum(RBNode* node) {
        while (node->getLeft() != nil)
            node = node->getLeft();
        return node;
    }

    void deleteFixup(RBNode* x) {
        while (x != root && x->getColor() == BLACK) {
            if (x == x->getParent()->getLeft()) {
                RBNode* w = x->getParent()->getRight();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    leftRotate(x->getParent());
                    w = x->getParent()->getRight();
                }
                if (w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getRight()->getColor() == BLACK) {
                        w->getLeft()->setColor(BLACK);
                        w->setColor(RED);
                        rightRotate(w);
                        w = x->getParent()->getRight();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getRight()->setColor(BLACK);
                    leftRotate(x->getParent());
                    x = root;
                }
            } else {
                RBNode* w = x->getParent()->getLeft();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rightRotate(x->getParent());
                    w = x->getParent()->getLeft();
                }
                if (w->getRight()->getColor() == BLACK && w->getLeft()->getColor() == BLACK) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getLeft()->getColor() == BLACK) {
                        w->getRight()->setColor(BLACK);
                        w->setColor(RED);
                        leftRotate(w);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    w->getLeft()->setColor(BLACK);
                    rightRotate(x->getParent());
                    x = root;
                }
            }
        }
        x->setColor(BLACK);
    }

    string inOrderHelper(RBNode* node) {
        if (node == nil) return "";
        return inOrderHelper(node->getLeft()) + node->getData() + inOrderHelper(node->getRight());
    }

    string preOrderHelper(RBNode* node) {
        if (node == nil) return "";
        return node->getData() + preOrderHelper(node->getLeft()) + preOrderHelper(node->getRight());
    }

    string postOrderHelper(RBNode* node) {
        if (node == nil) return "";
        return postOrderHelper(node->getLeft()) + postOrderHelper(node->getRight()) + node->getData();
    }

public:
    RBTree() {
        nil = new RBNode("", 0, "", "", "", 0, BLACK);
        root = nil;
    }

    void insert(string mon, int yr, string singer, string song,
                string house, int noWeeks) {
        RBNode* z = new RBNode(mon, yr, singer, song, house, noWeeks);
        z->setLeft(nil);
        z->setRight(nil);
        RBNode* y = nil;
        RBNode* x = root;

        while (x != nil) {
            y = x;
            if (z->getTitle() < x->getTitle())
                x = x->getLeft();
            else
                x = x->getRight();
        }

        z->setParent(y);
        if (y == nil)
            root = z;
        else if (z->getTitle() < y->getTitle())
            y->setLeft(z);
        else
            y->setRight(z);

        z->setColor(RED);
        insertFixup(z);
    }

    void remove(string song) {
        RBNode* z = root;
        while (z != nil && z->getTitle() != song) {
            if (song < z->getTitle())
                z = z->getLeft();
            else
                z = z->getRight();
        }

        if (z == nil) return;

        RBNode* y = z;
        Color yOriginalColor = y->getColor();
        RBNode* x;

        if (z->getLeft() == nil) {
            x = z->getRight();
            transplant(z, z->getRight());
        } else if (z->getRight() == nil) {
            x = z->getLeft();
            transplant(z, z->getLeft());
        } else {
            y = minimum(z->getRight());
            yOriginalColor = y->getColor();
            x = y->getRight();

            if (y->getParent() == z)
                x->setParent(y);
            else {
                transplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }

            transplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
            y->setColor(z->getColor());
        }

        delete z;

        if (yOriginalColor == BLACK)
            deleteFixup(x);
    }

    string inOrder() { return inOrderHelper(root); }
    string preOrder() { return preOrderHelper(root); }
    string postOrder() { return postOrderHelper(root); }
};

#endif
