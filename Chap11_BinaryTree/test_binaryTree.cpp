//
// Created by perry on 2019/12/2.
//

#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

int main() {
    linkedBinaryTree<int> a,x,y,z;
    y.makeTree(1,a,a);
    z.makeTree(2,a,a);
    x.makeTree(3,y,z);
    y.makeTree(4,x,a);
    cout << "Number of nodes = ";
    cout << y.size() << endl;
    cout << "height = ";
    cout << y.height() << endl;

    auto output = [] (binaryTreeNode<int>* t) { if (t != NULL) cout << t->element << " ";};
    cout << "preOrder output: ";
    y.preOrder(output);

    cout << endl << "inOrder output: ";
    y.inOrder(output);

    cout << endl << "postOrder output: ";
    y.postOrder(output);

    return 0;
}