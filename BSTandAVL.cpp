#include <iostream>
#include <stack>

// 定义二叉搜索树节点
template <typename BSTDataType>
class BSTnode
{
protected:
    BSTDataType _data;
    BSTnode *_left;
    BSTnode *_right;

public:
    // 节点构造函数
    BSTnode(BSTDataType data, BSTnode *left = nullptr, BSTnode *right = nullptr)
        : _data(data), _left(left), _right(right) {}
    // 节点析构函数
    ~BSTnode() {}
};

// 定义二叉搜索树
template <typename BSTDataType>
class BST : private BSTnode<BSTDataType>
{
private:
    BSTnode<BSTDataType> *_root;

    // 计算总深度和节点个数
    void computeDepthAndCount(BSTnode<BSTDataType> *node, int depth, int &totalDepth, int &count);

    // 删除节点
    void deleteNode(BSTnode<BSTDataType> *&root, BSTDataType x);

    // 查找最小值的节点
    BSTnode<BSTDataType> *findMin(BSTnode<BSTDataType> *node);

public:
    BST()
    {
        _root = nullptr;
    }

    BSTnode<BSTDataType> *getRoot()
    {
        return _root;
    }

    // 插入节点
    void insertNode(BSTDataType data);

    // 中序遍历
    void inOrder(BSTnode<BSTDataType> *p);

    // 计算平均搜索长度（ASL）
    double computeASL();

    // 查找节点
    BSTnode<BSTDataType> *search(BSTDataType x);

    // 删除节点
    void deleteNode(BSTDataType x);
};

// 实现计算总深度和节点个数的函数
template <typename BSTDataType>
void BST<BSTDataType>::computeDepthAndCount(BSTnode<BSTDataType> *node, int depth, int &totalDepth, int &count)
{
    if (node == nullptr) {
        return;
    }

    totalDepth += depth;
    count++;

    computeDepthAndCount(node->_left, depth + 1, totalDepth, count);
    computeDepthAndCount(node->_right, depth + 1, totalDepth, count);
}

// 实现查找最小值节点的函数
template <typename BSTDataType>
BSTnode<BSTDataType> *BST<BSTDataType>::findMin(BSTnode<BSTDataType> *node)
{
    while (node && node->_left != nullptr)
        node = node->_left;
    return node;
}

// 实现插入节点的函数
template <typename BSTDataType>
void BST<BSTDataType>::insertNode(BSTDataType data)
{
    BSTnode<BSTDataType> *newNode = new BSTnode<BSTDataType>(data);
    if (_root == nullptr) {
        _root = newNode;
        return;
    }
    BSTnode<BSTDataType> *p = _root;
    BSTnode<BSTDataType> *pre = nullptr;
    while (p != nullptr) {
        pre = p;
        if (data < p->_data)
            p = p->_left;
        else
            pre->_right = newNode;
    }

    // 实现中序遍历的函数
    template <typename BSTDataType>
    void BST<BSTDataType>::inOrder(BSTnode<BSTDataType> * p)
    {
        std::stack<BSTnode<BSTDataType> *> s;
        while (p != nullptr || !s.empty()) {
            while (p != nullptr) {
                s.push(p);
                p = p->_left;
            }
            if (!s.empty()) {
                p = s.top();
                s.pop();
                std::cout << p->_data << " ";
                p = p->_right;
            }
        }
        std::cout << "\n";
    }

    // 实现计算平均搜索长度（ASL）的函数
    template <typename BSTDataType>
    double BST<BSTDataType>::computeASL()
    {
        int totalDepth = 0;
        int count = 0;

        computeDepthAndCount(_root, 1, totalDepth, count);

        return static_cast<double>(totalDepth) / count;
    }

    // 实现查找节点的函数
    template <typename BSTDataType>
    BSTnode<BSTDataType> *BST<BSTDataType>::search(BSTDataType x)
    {
        BSTnode<BSTDataType> *p = _root;
        while (p != nullptr) {
            if (p->_data == x)
                return p;
            else if (x < p->_data)
                p = p->_left;
            else
                p = p->_right;
        }
        return nullptr;
    }

    // 实现删除节点的函数
    template <typename BSTDataType>
    void BST<BSTDataType>::deleteNode(BSTDataType x)
    {
        deleteNode(_root, x);
    }

    template <typename BSTDataType>
    void BST<BSTDataType>::deleteNode(BSTnode<BSTDataType> * &root, BSTDataType x)
    {
        if (root == nullptr)
            return;

        if (x < root->_data)
            deleteNode(root->_left, x);
        else if (x > root->_data)
            deleteNode(root->_right, x);
        else {
            if (root->_left == nullptr && root->_right == nullptr) {
                delete root;
                root = nullptr;
            } else if (root->_left == nullptr) {
                BSTnode<BSTDataType> *temp = root;
                root = root->_right;
                delete temp;
            } else if (root->_right == nullptr) {
                BSTnode<BSTDataType> *temp = root;
                root = root->_left;
                delete temp;
            } else {
                BSTnode<BSTDataType> *temp = findMin(root->_right);
                root->_data = temp->_data;
                deleteNode(root->_right, temp->_data);
            }
        }
    }
}

class Solution1{

};
