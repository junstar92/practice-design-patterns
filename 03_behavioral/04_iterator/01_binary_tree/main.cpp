#include <iostream>
#include <string>
#include <coroutine>

template<typename T>
struct BinaryTree;

template<typename T>
struct Node
{
    T value;
    Node<T>* left{nullptr};
    Node<T>* right{nullptr};
    Node<T>* parent{nullptr};
    BinaryTree<T>* tree{nullptr};

    explicit Node(T const& value) : value{value} {}
    Node(T const& value, Node<T>* const left, Node<T>* const right)
    : value{value}, left{left}, right{right} {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }
    ~Node() {
        if (left) delete left;
        if (right) delete right;
    }

    void set_tree(BinaryTree<T>* t) {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }
};

template<typename T>
struct BinaryTree
{
    Node<T>* root{nullptr};

    explicit BinaryTree(Node<T>* const root)
    : root{root}, pre_order{*this} {
        root->set_tree(this);
    }
    ~BinaryTree() {
        if (root) delete root;
    }

    template<typename U>
    struct PreOrderIterator
    {
        Node<U>* current;

        explicit PreOrderIterator(Node<U>* current)
        : current{current} {}

        bool operator!=(PreOrderIterator<U> const& other) {
            return current != other.current;
        }

        PreOrderIterator<U>& operator++() {
            if (current->right) {
                current = current->right;
                while (current->left)
                    current = current->left;
            }
            else {
                Node<T>* p = current->parent;
                while (p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() { return *current; }
    };

    using iterator = PreOrderIterator<T>;
    iterator begin() {
        Node<T>* n = root;
        
        if (n) {
            while (n->left)
                n = n->left;
        }
        return iterator{n};
    }
    iterator end() {
        return iterator{nullptr};
    }

    // expose as a traversal object
    class pre_order_traversal
    {
        BinaryTree<T> &tree;

    public:
        pre_order_traversal(BinaryTree<T> &tree) : tree{tree} {}
        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }
    } pre_order;
};

int main(int argc, char** argv)
{
    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f
    BinaryTree<std::string> family{
        new Node<std::string>{"me",
            new Node<std::string>{"mother",
                new Node<std::string>{"mother's mother"},
                new Node<std::string>{"mother's father"}
            },
            new Node<std::string>{"father"}
        }
    };

    // pre-order traversal
    for (auto it = family.begin(); it != family.end(); ++it) {
        std::cout << (*it).value << std::endl;
    }


    // use iterator name
    std::cout << "=== through a dedicated object:\n";
    for (auto const& it : family.pre_order) {
        std::cout << it.value << std::endl;
    }

    return 0;
}