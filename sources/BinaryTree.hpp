#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <queue>
#include <stack>

namespace ariel
{
    const int PREORDER = 0;
    const int INORDER = 1;
    const int POSTORDER = 2;

    template <class T>
    class BinaryTree
    {
        struct Node
        {
            T data;
            Node *left = nullptr;
            Node *right = nullptr;

            Node() = default;

            Node(T info) : data(info), left(nullptr), right(nullptr) {}

            ~Node()
            {
                delete left;
                delete right;
            }
            Node(const Node &other)
            {
                //copy ctor
                this->data = other->data;
                if (other->left)
                {
                    this->left = new Node(other->left->data);
                }
                if (other->right)
                {
                    this->right = new Node(other->right->data);
                }
            }

            Node(Node &&node) noexcept
            {
                this->data = node.data;
                node.data = nullptr;
                this->left = node.left;
                node.left = nullptr;
                this->right = node.right;
                node.right = nullptr;
            }

            Node &operator=(const Node &node)
            {
                if (this == &node)
                {
                    return *this;
                }
                data = node->data;
                if (node->left)
                {
                    this->left = node->left;
                }
                if (node->right)
                {
                    this->right = node->right;
                }
                return *this;
            }

            Node &operator=(Node &&node) noexcept
            {
                if (left)
                {
                    delete left;
                }
                if (right)
                {
                    delete right;
                }
                data = node.data;
                node.data = nullptr;
                left = node.left;
                node.left = nullptr;
                right = node.right;
                node.right = nullptr;

                return *this;
            }
        };

        Node *root = nullptr;

    public:
        BinaryTree<T>()
        {
            root = nullptr;
        }

        ~BinaryTree<T>()
        {
            delete root;
        }

        void copy_tree(Node *new_node, const Node *exist_node)
        {
            if (exist_node->left != nullptr)
            {
                new_node->left = new Node(exist_node->left->data);
                copy_tree(new_node->left, exist_node->left);
            }
            if (exist_node->right != nullptr)
            {
                new_node->right = new Node(exist_node->right->data);
                copy_tree(new_node->right, exist_node->right);
            }
        }

        BinaryTree &operator=(const BinaryTree<T> &tree)
        {
            if (this == &tree)
            {
                return *this;
            }
            if (root != nullptr)
            {
                delete root;
            }
            if (tree.root != nullptr)
            {
                root = new Node{tree.root->data};
                copy_tree(root, tree.root);
            }
            return *this;
        }

        BinaryTree &operator=(BinaryTree<T> &&tree) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = tree.root;
            tree.root = nullptr;
            return *this;
        }

        BinaryTree(const BinaryTree &tree)
        {
            //copy ctor
            if (tree.root != nullptr)
            {
                this->root = new Node(tree.root->data);
                copy_tree(root, tree.root);
            }
        }

        BinaryTree(BinaryTree &&tree) noexcept
        {
            this->root = tree.root;
            tree.root = nullptr;
        }

        Node *search_node(Node *current, const T &info)
        {
            if (current == nullptr)
            {
                return nullptr;
            }
            if (current->data == info)
            {
                return current;
            }
            Node *sub_left = search_node(current->left, info);
            Node *sub_right = search_node(current->right, info);
            if (sub_left != nullptr)
            {
                return sub_left;
            }
            if (sub_right != nullptr)
            {
                return sub_right;
            }
            return nullptr;
        }

        BinaryTree<T> &add_root(const T &info)
        {
            if (root == nullptr)
            {
                root = new Node(info);
            }
            else
            {
                root->data = info;
            }
            return *this;
        }

        BinaryTree<T> &
        add_left(const T &father, const T &left_son)
        {
            Node *node = search_node(root, father);
            if (node == nullptr)
            {
                throw std::invalid_argument("The node father does not exist");
            }
            if (node->left == nullptr)
            {
                node->left = new Node(left_son);
            }
            else
            {
                node->left->data = left_son;
            }
            return *this;
        }

        BinaryTree<T> &add_right(const T &father, const T &right_son)
        {
            Node *node = search_node(root, father);
            if (node == nullptr)
            {
                throw std::invalid_argument("The node father does not exist");
            }
            if (node->right == nullptr)
            {
                node->right = new Node(right_son);
            }
            else
            {
                node->right->data = right_son;
            }
            return *this;
        }

        class iterator
        {

        private:
            int Order;
            std::queue<Node *> q;
            Node *curr;

        public:
            iterator(int order, Node *current = nullptr) : curr(current), Order(order)
            {
                if (order == PREORDER) // father left right
                {
                    if (curr == nullptr)
                    {
                        return;
                    }
                    std::stack<Node *> s;
                    s.push(curr);
                    while (!s.empty())
                    {
                        Node *node = s.top();
                        q.push(node);
                        s.pop();

                        if (node->right)
                        {
                            s.push(node->right);
                        }
                        if (node->left)
                        {
                            s.push(node->left);
                        }
                    }
                    curr = q.front();
                    q.pop();
                }

                if (order == INORDER) // left father right
                {
                    if (curr == nullptr)
                    {
                        return;
                    }

                    std::stack<Node *> s;
                    Node *node = curr;

                    while (node != nullptr || !s.empty())
                    {
                        while (node != nullptr)
                        {
                            s.push(node);
                            node = node->left;
                        }
                        node = s.top();
                        q.push(node);
                        s.pop();
                        node = node->right;
                    }
                    curr = q.front();
                    q.pop();
                }

                if (order == POSTORDER) // left right father
                {
                    if (curr == nullptr)
                    {
                        return;
                    }

                    std::stack<Node *> s1;
                    std::stack<Node *> s2;

                    s1.push(curr);
                    Node *node = nullptr;

                    while (!s1.empty())
                    {
                        node = s1.top();
                        s1.pop();
                        s2.push(node);

                        if (node->left)
                        {
                            s1.push(node->left);
                        }
                        if (node->right)
                        {
                            s1.push(node->right);
                        }
                    }

                    while (!s2.empty())
                    {
                        node = s2.top();
                        q.push(node);
                        s2.pop();
                    }
                    curr = q.front();
                    q.pop();
                }
            }

            T &
            operator*() const
            {
                return curr->data;
            }

            T *operator->() const
            {
                return &(curr->data);
            }

            iterator &operator++()
            {
                if (q.empty())
                {
                    curr = nullptr;
                }
                else
                {
                    curr = q.front();
                    q.pop();
                }
                return *this;
            }

            iterator operator++(int)
            {
                iterator temp = *this;
                if (q.empty())
                {
                    curr = nullptr;
                }
                else
                {
                    curr = q.front();
                    q.pop();
                }
                return temp;
            }

            bool operator==(const iterator &other) const
            {
                return curr == other.curr;
            }

            bool operator!=(const iterator &other) const
            {
                return curr != other.curr;
                ;
            }
        };

        iterator begin_preorder()
        {
            return iterator(0, root);
        }
        iterator end_preorder()
        {
            return iterator(0);
        }
        iterator begin_inorder()
        {
            return iterator(1, root);
        }
        iterator end_inorder()
        {
            return iterator(1);
        }
        iterator begin_postorder()
        {
            return iterator(2, root);
        }
        iterator end_postorder()
        {
            return iterator(2);
        }
        iterator begin()
        {
            return iterator(1, root);
        }
        iterator end()
        {
            return iterator(1);
        }

        static void print_tree(std::ostream &os, const std::string &prefix, const Node *node, bool isLeft)
        {
            if (node != nullptr)
            {
                os << prefix;
                if (isLeft)
                {
                    os << "├──";
                }
                else
                {
                    os << "└──";
                }
                // Print the data of the node
                std::cout << node->data << std::endl;
                // Enter the next tree level - left and right branch
                print_tree(prefix + (isLeft ? "│   " : "    "), node->left, true);
                print_tree(prefix + (isLeft ? "│   " : "    "), node->right, false);
            }
        }

        static void print_tree(std::ostream &os, const Node *node)
        {
            print_tree(os, "", node, false);
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree)
        {
            if (tree.root == nullptr)
            {
                return os;
            }
            os << std::endl;
            print_tree(os, tree.root);
            os << std::endl;
            return os;
        }
    };
}
