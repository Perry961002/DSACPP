//
// Created by perry on 2019/12/9.
//

#include <iostream>
#include <fstream>
#include <string>
#include "../Chap11_BinaryTree/binaryTreeNode.h"
#include "../Chap8_Stack/arrayStack.h"
#include "huffmanTree.h"

using namespace std;

void enCode(binaryTreeNode<int> *tree, int *weights, string str) {
    if (tree == NULL) return;

    //是叶子结点
    if (tree->leftChild == NULL && tree->rightChild == NULL) {
        cout << "element: " << char('a' + tree->element - 1) << ", weight: " << weights[tree->element] << ", code: " << str
             << endl;
        return;
    }
    //递归左右子树
    if (tree->leftChild != NULL)
        enCode(tree->leftChild, weights, str + "0");
    if (tree->rightChild != NULL)
        enCode(tree->rightChild, weights, str + "1");
}

int main() {
    //加载test.txt文件里的英文小短文，统计里面每个字母的频率
    ifstream in("../../Chap12_PriorityQueue/test.txt");
    int weights[27] = {0};
    string str;
    if (in) {
        while (in >> str) {
            for (char c : str) {
                if (c > 'a' && c < 'z')
                    ++weights[c - 'a' + 1];
                else if (c > 'A' && c < 'Z')
                    ++weights[c - 'A' + 1];
                str = "";
            }
        }
        in.close();
    } else {
        cout << "Failed to open TXT file！" << endl;
        return 0;
    }

    //构建huffman树
    binaryTreeNode<int> *tree = huffmanTree(weights, 26);

    //根据huffman树对字符进行编码
    enCode(tree, weights, "");
    return 0;
}