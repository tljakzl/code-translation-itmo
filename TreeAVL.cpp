#include "TreeAVL.h"
#include <algorithm>
#include "Hash.h"

TreeAVL::node *TreeAVL::Insert(TreeAVL::node *p, const std::string& str) {
    if (!p)
        return new node(str);

    auto k = Hash_djb2(str);

    if (k < p->key)
        p->left = Insert(p->left, str);
    else if (k > p->key)
        p->right = Insert(p->right, str);

    // k == key не вставляем, так как элемент уже есть

    return Balance(p);
}

TreeAVL::node *TreeAVL::Remove(TreeAVL::node *p, const std::string& str) {
    if(!p)
        return nullptr;

    auto k = Hash_djb2(str);

    if(k < p->key)
        p->left = Remove(p->left, str);
    else if(k > p->key)
        p->right = Remove(p->right, str);
    else //  k == p->key
    {
        node* q = p->left;
        node* r = p->right;
        delete p;

        if(!r)
            return q;

        node* min = FindMin(r);
        min->right = RemoveMin(r);
        min->left = q;

        return Balance(min);
    }

    return Balance(p);
}

TreeAVL::node *TreeAVL::RemoveMin(TreeAVL::node *p)    {
    if(p->left== nullptr)
        return p->right;

    p->left = RemoveMin(p->left);

    return Balance(p);
}

TreeAVL::node *TreeAVL::FindMin(TreeAVL::node *p) {
    if(!p->left)
        return p;

    return FindMin(p->left);
}

TreeAVL::node *TreeAVL::Balance(TreeAVL::node *p) {
    FixHeight(p);

    if(BFactor(p) == 2)
    {
        if(BFactor(p->right) < 0)
            p->right = RotateRight(p->right);

        return RotateLeft(p);
    }

    if(BFactor(p) == -2)
    {
        if(BFactor(p->left) > 0)
            p->left = RotateLeft(p->left);

        return RotateRight(p);
    }

    return p; // балансировка не нужна
}

TreeAVL::node *TreeAVL::RotateLeft(TreeAVL::node *q) {

    node* p = q->right;
    q->right = p->left;
    p->left = q;

    FixHeight(q);
    FixHeight(p);

    return p;
}

TreeAVL::node *TreeAVL::RotateRight(TreeAVL::node *p) {
    node* q = p->left;
    p->left = q->right;
    q->right = p;

    FixHeight(p);
    FixHeight(q);

    return q;
}

void TreeAVL::FixHeight(TreeAVL::node *p) {

    auto hl = Height(p->left);
    auto hr = Height(p->right);

    p->height = std::max(hl, hr) + 1;
}

int TreeAVL::BFactor(TreeAVL::node *p) {
    if(!p)
        return 0;

    return Height(p->right) - Height(p->left);
}

int TreeAVL::Height(TreeAVL::node *p) {
    if(!p)
        return 0;

    return p->height;
}

TreeAVL::TreeAVL()
:_tree(nullptr)
{

}

void TreeAVL::Insert(const std::string& str) {
    if(_tree)
    {
        _tree = Insert(_tree, str);
    }
    else
    {
        _tree = new node(str);
    }
}

TreeAVL::~TreeAVL() {
    _free_tree(_tree);
}

void TreeAVL::_free_tree(TreeAVL::node* tree) {

    if(tree)
    {
        _free_tree(tree->left);
        _free_tree(tree->right);

        delete tree;
    }
}

void TreeAVL::Remove(const std::string& str) {
    _tree = Remove(_tree, str);
}

TreeAVL::node::node(const std::string& str)
: left(nullptr)
, right(nullptr)
, key(Hash_djb2(str))
, height(1)
, value(str)
{
}
