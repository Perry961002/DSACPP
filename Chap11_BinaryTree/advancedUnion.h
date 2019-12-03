//
// Created by perry on 2019/12/3.
//

/*
 * 因为路径压缩会改变树的高度，但不会改变树的重量，所以使用重量规则来优化合并函数
 * 接下来分别实现了3种路径压缩算法（路径紧缩、路径分割和路径对折）来优化查找函数
 */
//使用重量规则的结点结构
struct unionFindNode {
    int parent;  //root为真时表示树的重量，即结点数，否则是父结点的指针
    bool root;  //仅当为根时，值为真

    unionFindNode() { parent = 1; root = true;}
};

struct advancedUnion {
    unionFindNode *node;
    advancedUnion(int numberOfElements) { initialize(numberOfElements);}

    //初始化并查集，每个结点就是一棵只包含它自己的树
    void initialize(int numberOfElements) {
        node = new unionFindNode[numberOfElements + 1];
    }

    //使用重量规则来合并两个不同根的树
    void unite(int rootA, int rootB) {
        //将重量较轻的作为子树
        if (node[rootA].parent < node[rootB].parent) {
            //rootA作为子树
            node[rootB].parent += node[rootA].parent;
            node[rootA].root = false;
            node[rootA].parent = rootB;
        } else {
            node[rootA].parent += node[rootB].parent;
            node[rootB].root = false;
            node[rootB].parent = rootA;
        }
    }

    //普通的查找函数
    int find(int theElement) {
        while (!node[theElement].root)
            theElement = node[theElement].parent;
        return theElement;
    }

    /*
    * 使用路径紧缩来优化的查找函数
    * 从待查结点到根结点的路径上，所有结点的parent指针都被改为指向根结点
    */
    int findWithCompaction(int theElement) {
        //找到最终的根theRoot
        int theRoot = theElement;
        while (!node[theRoot].root)
            theRoot = node[theRoot].parent;

        //压缩从theElement到theRoot的路径，将路径上的每个结点都指向theRoot
        int currentNode = theElement;
        while (currentNode != theRoot) {
            int parentNode = node[currentNode].parent;
            node[currentNode].parent = theRoot;  //直接指向theRoot
            currentNode = parentNode;  //向上移动一层
        }
        return theRoot;
    }

    /*
     * 使用路径分割来优化的查找函数
     * 从待查结点到根结点的路径上，除根结点和其子结点之外，每个结点的parent指针都被改为指向各自的祖父
     */
    int findWithSplitting(int theElement) {
        int parentNode = 0;
        //除根结点和其子结点之外，每个结点的parent指针都被改为指向各自的祖父
        while (!node[theElement].root) {
            parentNode = node[theElement].parent;
            if (node[parentNode].root)  //根结点的子结点
                return parentNode;
            node[theElement].parent = node[parentNode].parent;
            theElement = parentNode;
        }
        //最终的根结点
        return theElement;
    }

    /*
     * 使用路径对折来优化的查找函数
     * 从待查结点到根结点的路径上，除根结点和其子结点之外，每个结点的parent指针都被改为指向各自的祖父
     */
    int findWithHalving(int theElement) {
        int parentNode = 0;
        //除根结点和其子结点之外，每个结点的parent指针都被改为指向各自的祖父
        while (!node[theElement].root) {
            parentNode = node[theElement].parent;
            if (node[parentNode].root)  //根结点的子结点
                return parentNode;
            node[theElement].parent = node[parentNode].parent;
            theElement = node[parentNode].parent;
        }
        //最终的根结点
        return theElement;
    }
};