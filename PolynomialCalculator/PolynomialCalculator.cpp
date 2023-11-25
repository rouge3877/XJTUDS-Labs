#include <cmath>
#include <iostream>
using namespace std;

// 定义多项式的节点
class Node
{
public:
    int _coef; // 系数
    int _exp;  // 指数
    Node *_next;
    Node(int c, int e, Node *n = nullptr)
        : _coef(c), _exp(e), _next(n) {}
};

class Polynomial
{
private:
    Node *_head; // 多项式的头节点
public:
    // 多项式的项数存放在头结点的_coed中
    Polynomial() : _head(new Node(0, 0, nullptr)) {} 

    // 析构函数
    ~Polynomial()
    { 
        Node *p = _head;
        while (p != nullptr) {
            Node *q = p;
            p = p->_next;
            delete q;
        }
    }
    
    //按照多项式的指数的降序插入
    void insert(int coef, int exp)
    {
        Node *p = _head;
        while (p->_next != nullptr && p->_next->_exp > exp) {
            p = p->_next;
        }
        if (p->_next != nullptr && p->_next->_exp == exp) {
            p->_next->_coef += coef;
            if (p->_next->_coef == 0) {
                Node *q = p->_next;
                p->_next = q->_next;
                delete q;
                _head->_coef--;
            }
        } else {
            p->_next = new Node(coef, exp, p->_next);
            _head->_coef++;
        }
    }


    //从文件读取多项式，格式为: a*x^b+c*x^d-e*x^f ..., 区分正负号且中间没有空格，每个项的系数和指数都是整数
    void readFromFile(const char *filename)
    {
        FILE *fp = fopen(filename, "r");
        if (fp == nullptr) {
            cout << "文件打开失败" << endl;
            return;
        }
        

        fclose(fp);
        
    }

    //输出多项式，输出形式为整数序列：n,c1,e1,c2,e2,…,cn,en, 其中n是多项式的项数，ci,ei分别是第i项的系数和指数，序列按指数降序排列
    void print()
    {
        cout << _head->_coef;
        Node *p = _head->_next;
        while (p != nullptr) {
            cout << "," << p->_coef << "," << p->_exp;
            p = p->_next;
        }
        cout << endl;
    }

    //多项式相加


};

int main()
{
    Polynomial p;
    p.readFromFile("/home/rouge/cpp-repo/XJTUDS/Labs/PolynomialCalculator/poly.txt");
    p.print();
    return 0;
}