//
// Created by vldmr on 18.07.19.
//

#ifndef LECS_PARS_TREE_H
#define LECS_PARS_TREE_H

#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <string>
#include <queue>
#include <utility>

class Tree {
public:
    Tree() {
        left   = nullptr;
        right  = nullptr;
        parent = nullptr;
        value  = "";
        alloc  = true;
    }

    explicit Tree(const std::string &val) {
        left   = nullptr;
        right  = nullptr;
        parent = nullptr;
        value  = val;
        alloc  = true;
    }


    void AddLeftNode(const std::string &val) {
        this->left = CreateNode(this, val);
    }

    void AddRightNode(const std::string &val) {
        this->right = CreateNode(this, val);
    }


    Tree *GetLeftNode() {
        return this->left;
    }


    void AddLeftTree(Tree* tree) {
        tree->parent = this;
        this->left = tree;
    }


    void AddRightTree(Tree * tree) {
        tree->parent = this;
        this->right = tree;
    }


    void ChangeValue(const std::string &val) {
        value = val;
    }


    Tree *GetRightNode() {
        return this->right;
    }


    Tree *GetParentNode() {
        return this->parent;
    }


    std::string GetValue() {
        return this->value;
    }


    void PrintTree() {
        std::cout << this << "\t" << this->value << "\t"
                  << this->left << "\t" << this->right << std::endl;
        if (this->left != nullptr) this->left->PrintTree();
        if (this->right != nullptr) this->right->PrintTree();
    }



    /**
     * @brief Create like a root node of syntax tree
     * @param[in] node_name - name of the node (value)
     *
     * @return node of tree
     */
    static Tree *CreateNode(const std::string &val) {
        auto *node = new Tree(val);
        return node;
    }


    /**
     * @brief Create node of syntax tree
     * @param[in] t_tree    - parent node
     * @param[in] node_name - name of the created node (value)
     *
     * @return node of tree
     */
    static Tree *CreateNode(Tree *parent_tree, const std::string &val) {
        auto *node = new Tree(val);
        node->parent = std::addressof(*parent_tree);
        return node;
    }


    void FreeTree() {
        if (this->left  != nullptr) this->left->FreeTree();
        if (this->right != nullptr) this->right->FreeTree();
        parent = nullptr;
        value  = "";
        alloc  = false;
    }

    static void FreeTree(Tree *&t_tree) { // used like Tree::FreeTree(root);
        try {
            if (t_tree->left  != nullptr) FreeTree(t_tree);
            if (t_tree->right != nullptr) FreeTree(t_tree);
            delete t_tree;
            t_tree = nullptr;
        } catch (const std::exception &exp) {
            std::cerr << "<E> Tree: Catch exception in " << __func__ << ": "
                      << exp.what() << std::endl;
        }
    }


    virtual ~Tree() {
        FreeTree();
    } // = default;
private:
    Tree *left;
    Tree *right;
    Tree *parent;
    std::string value;
    bool alloc { false }; // allocation flag
};


#endif //LECS_PARS_TREE_H
