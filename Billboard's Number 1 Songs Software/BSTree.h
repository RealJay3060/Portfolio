//
//  BSTree.h
//  BST
//
//  Created by Dr. John Charlery on 03/15/2025.
//  Copyright (c) 2025 University of the West Indies. All rights reserved.
//

#ifndef BST_BSTree_h
#define BST_BSTree_h

#include <iostream>
#include <string>

using namespace std;


//====================================================================
//          BST Node class
//====================================================================

class BSTNode
    {
        private:
                string month;
                string artist;
                string title;
                string label;
                int    year;
                int    weeks;

                BSTNode* left;
                BSTNode* right;

        public:

            // Constructor functions
            BSTNode(string, int, string, string, string, int);

            // Accessor functions
            BSTNode* getLeft()   {return left;};
            BSTNode* getRight()  {return right;}
            string getTitle()    {return title;}
            string getData();

            // Mutator functions
            void setData(string, int, string, string, string, int);
            void setLeft(BSTNode* ptr) {left = ptr;}
            void setRight(BSTNode* ptr){right = ptr;}
            void copyData(BSTNode*);
     };


BSTNode::BSTNode(string mon, int yr, string singer, string song,
                 string house, int noWeeks)
    {
        month = mon;
        year = yr;
        artist = singer;
        title = song;
        label = house;
        weeks = noWeeks;
        left = NULL;
        right = NULL;
    }


string BSTNode::getData()
    {
        string str = month + " | ";
        str.append(to_string(year) + " | ");
        str.append(artist + " | ");
        str.append(title + " | ");
        str.append(label + " | ");
        str.append(to_string(weeks) + "\n");

        return str;
    }

void BSTNode::setData(string mon, int yr, string singer, string song,
             string house, int noWeeks)
    {
        month = mon;
        year = yr;
        artist = singer;
        title = song;
        label = house;
        weeks = noWeeks;
    }


// Copy all the data from ptr into the node
void BSTNode::copyData(BSTNode* ptr)
    {
        month  = ptr->month;
        year   = ptr->year;
        artist = ptr->artist;
        title  = ptr->title;
        label  = ptr->label;
        weeks  = ptr->weeks;
    }





//====================================================================
//          BSTree container class
//====================================================================


class BSTree
    {
        private:
            BSTNode* root;

            // Recursive counterpart for inserting a node
            BSTNode* insertHelper(BSTNode*, string, int, string,
                                  string, string, int);

            // Recursive counterpart for deleting a node
             BSTNode* deleteHelper(BSTNode*, string);

            // Recursive counterpart of preorder traversal
            string preOrderHelper(BSTNode* );

            // Recursive counterpart of postorder traversal
            string postOrderHelper(BSTNode* );

            // Recursive counterpart of inorder traversal
            string inOrderHelper(BSTNode* );

        public:
            //  Constructor function
            BSTree() { root = NULL;}

            // Mutator functions
            void purge(){ root = NULL;}
            void insert(string, int, string, string, string, int);

            void remove(string song) { root = deleteHelper(root, song);}

            string deleteNode(const string& song) {
                root = deleteHelper(root, song);
                return "Deleted: " + song;
            }

            // Accessor functions
            BSTNode* getRoot() { return root;}
            string preOrder()  { return preOrderHelper(root); }
            string postOrder() { return postOrderHelper(root); }
            string inOrder()   { return inOrderHelper(root); }

    };


void BSTree::insert(string mon, int yr, string singer, string song,
                    string house, int noWeeks)
    {
        root = insertHelper(root, mon, yr, singer, song, house, noWeeks);
    }




BSTNode* BSTree::insertHelper(BSTNode* ptr, string mon, int yr,
                              string singer, string song,
                              string house, int noWeeks)
    {
        if ( ptr == NULL )         // The tree is empty - new first node!
            {
                ptr = new BSTNode(mon, yr, singer, song, house, noWeeks);
            }
        else                       // choose which sub-tree to follow
            {
                if (song.compare(ptr->getTitle()) >= 0)          // insert in right subtree - Operational defn.
                    ptr->setRight(insertHelper(ptr->getRight(), mon, yr, singer, song, house, noWeeks));
                else                                                    // insert in left subtree
                    ptr->setLeft(insertHelper(ptr->getLeft(), mon, yr, singer, song, house, noWeeks));
            }
        return ptr;
    }







BSTNode* BSTree::deleteHelper(BSTNode* ptr, string song)
{
    if (ptr == NULL) {
        cout << "Reached NULL node. Stopping.\n";
        return NULL;
    }

    cout << "Visiting node: " << ptr->getTitle() << "\n";

    if (song < ptr->getTitle())
    {
        cout << "Going left\n";
        ptr->setLeft(deleteHelper(ptr->getLeft(), song));
    }
    else if (song > ptr->getTitle())
    {
        cout << "Going right\n";
        ptr->setRight(deleteHelper(ptr->getRight(), song));
    }
    else // Found the node to delete
    {
        cout << "Found node to delete: " << ptr->getTitle() << "\n";

        // Case 1: No children
        if (ptr->getLeft() == NULL && ptr->getRight() == NULL)
        {
            cout << "Deleting leaf node: " << ptr->getTitle() << "\n";
            delete ptr;
            return NULL;
        }

        // Case 2: One child
        else if (ptr->getLeft() == NULL)
        {
            cout << "Deleting node with only right child: " << ptr->getTitle() << "\n";
            BSTNode* temp = ptr->getRight();
            delete ptr;
            return temp;
        }
        else if (ptr->getRight() == NULL)
        {
            cout << "Deleting node with only left child: " << ptr->getTitle() << "\n";
            BSTNode* temp = ptr->getLeft();
            delete ptr;
            return temp;
        }

        // Case 3: Two children
        else
        {
            cout << "Deleting node with two children: " << ptr->getTitle() << "\n";
            BSTNode* successor = ptr->getRight();

            // Find inorder successor
            while (successor->getLeft() != NULL) {
                cout << "Traversing to left of successor: " << successor->getTitle() << "\n";
                successor = successor->getLeft();
            }

            cout << "Successor found: " << successor->getTitle() << "\n";

            ptr->copyData(successor);
            ptr->setRight(deleteHelper(ptr->getRight(), successor->getTitle()));
        }
    }

    return ptr;
}






string BSTree::inOrderHelper(BSTNode* ptr)
	{
        string str = "";

        if ( ptr != NULL )
            {
                str.append( inOrderHelper(ptr->getLeft()) );

                str.append( ptr->getData() );

                str.append( inOrderHelper(ptr->getRight()) );
              }
		return str;
	}




string BSTree::preOrderHelper(BSTNode* ptr)
	{
        string str = "";

        if ( ptr != NULL )
            {
                str.append( ptr->getData() );

                str.append( preOrderHelper(ptr->getLeft() ));
                str.append( preOrderHelper(ptr->getRight() ));
              }
		return str;
	}




string BSTree::postOrderHelper(BSTNode* ptr)
	{
        string str = "";

        if ( ptr != NULL )
            {
                str.append( postOrderHelper(ptr->getLeft() ));
                str.append( postOrderHelper(ptr->getRight() ));

                str.append( ptr->getData() );
             }
		return str;
	}








#endif
