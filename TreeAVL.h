#pragma once
#include <string>

class TreeAVL {
private:

    struct node // структура для представления узлов дерева
    {
    public:

        explicit node(const std::string& str);

    public:
        node* left;
        node* right;
        unsigned long key;
        int height;
        std::string value;
    };

public:
    TreeAVL();
    ~TreeAVL();

    void Insert(const std::string& str);
    bool Find(const std::string& str);
    void Remove(const std::string& str);

private:
    bool FindImpl(node* p, unsigned long key);
    node* Insert(node* p, const std::string& str); // вставка ключа k в дерево с корнем p
    node* Remove(node* p, const std::string& str); // удаление ключа k из дерева p
    node* RotateRight(node* p); // правый поворот вокруг p
    node* RotateLeft(node* q); // левый поворот вокруг q
    node* Balance(node* p); // балансировка узла p
    node* FindMin(node* p); // поиск узла с минимальным ключом в дереве p
    node* RemoveMin(node* p); // удаление узла с минимальным ключом из дерева p

    int Height(node* p);
    int BFactor(node* p);
    void FixHeight(node* p);

    void _free_tree(node* tree);

private:
    node* _tree;
};

