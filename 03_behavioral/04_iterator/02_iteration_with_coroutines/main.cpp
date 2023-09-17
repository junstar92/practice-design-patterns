#include <iostream>
#include <string>
#include <coroutine>
#include <optional>

template<typename T>
struct generator
{
    struct promise_type
    {
        using value_type = std::optional<T>;

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        std::suspend_always yield_value(T value) {
            this->value = std::move(value);
            return {};
        }
        void return_void() { this->value = std::nullopt; }

        generator get_return_object() {
            return generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        value_type get_value() {
            return std::move(value);
        }
        bool finished() { return !value.has_value(); }

    private:
        value_type value{};
    };

    explicit generator(std::coroutine_handle<promise_type> handle) : handle{handle} {}
    ~generator() {
        if (handle) handle.destroy();
    }
    typename promise_type::value_type next() {
        if (handle) {
            handle.resume();
            return handle.promise().get_value();
        }
        else {
            return {};
        }
    }

    struct end_iterator {};
    struct iterator {
        using value_type = typename promise_type::value_type;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        iterator(generator& gen) : gen{&gen} {}

        value_type operator*() const {
            if (gen) {
                return gen->handle.promise().get_value();
            }
            return {};
        }
        value_type operator->() const {
            if (gen) {
                return gen->handle.promise().get_value();
            }
            return {};
        }
        iterator& operator++() {
            if (gen && gen->handle) {
                gen->handle.resume();
            }
            return *this;
        }
        iterator& operator++(int) {
            if (gen && gen->handle) {
                gen->handle.resume();
            }
            return *this;
        }
        bool operator==(end_iterator const&) const {
            return gen ? gen->handle.promise().finished() : true;
        }
    
    private:
        generator* gen;
    };

    iterator begin() {
        iterator it{*this};
        return ++it;
    }
    end_iterator end() {
        return end_sentinel;
    }

private:
    std::coroutine_handle<promise_type> handle;
    end_iterator end_sentinel{};
};

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
    : root{root}{
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

    generator<Node<T>*> post_order() {
        return post_order_impl(root);
    }

private:
    generator<Node<T>*> post_order_impl(Node<T>* node) {
        if (node) {
            for (auto x : post_order_impl(node->left))
                co_yield x.value();
            for (auto y : post_order_impl(node->right))
                co_yield y.value();
            co_yield node;
        }
    }
};

int main(int argc, char** argv)
{
    BinaryTree<std::string> family{
        new Node<std::string>{"me",
            new Node<std::string>{"mother",
                new Node<std::string>{"mother's mother"},
                new Node<std::string>{"mother's father"}
            },
            new Node<std::string>{"father"}
        }
    };

    std::cout << "=== preorder travesal with iterator:\n";
    for (auto it = family.begin(); it != family.end(); ++it) {
        std::cout << (*it).value << std::endl;
    }

    std::cout << "=== postorder travesal with coroutines:\n";
    for (auto it : family.post_order()) {
        std::cout << it.value()->value << std::endl;
    }

    return 0;
}