/*#include <iostream>
#include <stack>
#include <queue>
#include <utility>

template <class K, class V>
class BSTree {
    struct node {
        K key;
        V value;
        node * child[2] = {nullptr, nullptr};
        node(const K& k) : key(k), value() {}
        node(const K& k, const V& v) : key(k), value(v) {}

    };
    node * root = nullptr;
    node *& left(node *& n) {
        return n->child[0];
    }
    node *& right(node *& n) {
        return n->child[1];
    }

    node * left(node * n) const {
        return n->child[0];
    }
    node * right(node * n) const {
        return n->child[1];
    }

    void inorder(node * n) {
        if(!n) return;
        inorder(left(n));
        std::cout << "(" << n->key << ", " << n->value << ") ";
        inorder(right(n));
    }

    void preorder(node * n) {
        if(!n) return;
        std::cout << "(" << n->key << ", " << n->value << ") ";
        preorder(left(n));
        preorder(right(n));
    }

    void postorder(node * n) {
        if(!n) return;
        postorder(left(n));
        postorder(right(n));
        std::cout << "(" << n->key << ", " << n->value << ") ";
    }

public:
    BSTree() = default;

    virtual ~BSTree(){
        free(root);
    }

    V & operator [] (const K & key) {
        node ** n = nullptr;
        if(!search(n, key))
            *n = new node(key);
        return (*n)->value;
    }

    bool search(const K & key) {
        node ** n = nullptr;
        return search(n, key);
    }

    bool search(node **& n, const K & key) {
        n = &root;
        while(*n && (*n)->key != key)
            n = &(*n)->child[(*n)->key < key];

        return *n != nullptr;
    }

    bool insert(const K & key, const V & value) {
        node ** n = nullptr;
        if(search(n, key))
            return false;

        *n = new node(key, value);
        return true;
    }

    bool remove(const K & key) {
        node ** n = nullptr;
        if (!search(n, key)) return false;

        node * to_delete = *n;

        if (!left(to_delete) && !right(to_delete)) {
            // leaf node
            *n = nullptr;
        } else if (!left(to_delete)) {
            // only right child
            *n = right(to_delete);
        } else if (!right(to_delete)) {
            //only left child
            *n = left(to_delete);
        } else {
            // two children
            node ** min_right = right_min(to_delete);

            to_delete->key = (*min_right)->key;
            to_delete->value = (*min_right)->value;
            to_delete = *min_right;
            *min_right = right(to_delete);
        }

        delete to_delete;
        return true;
    }

    bool successor(const K & key, K & succ_key) {
        node * curr = root;
        node * succ = nullptr;
        while (curr) {
            if (curr->key > key) {
                succ = curr;
                curr = left(curr);
            } else if (curr->key < key) {
                curr = right(curr);
            } else {
                if (right(curr)) {
                    curr = right(curr);
                    while (left(curr)) curr = left(curr);
                    succ = curr;
                }
                break;
            }
        }
        if (succ) {
            succ_key = succ->key;
            return true;
        }
        return false;
    }

    bool predecessor(const K & key, K & pred_key) {
        node * curr = root;
        node * pred = nullptr;
        while (curr) {
            if (curr->key < key) {
                pred = curr;
                curr = right(curr);
            } else if (curr->key > key) {
                curr = left(curr);
            } else {
                if (left(curr)) {
                    curr = left(curr);
                    while (right(curr)) curr = right(curr);
                    pred = curr;
                }
                break;
            }
        }
        if (pred) {
            pred_key = pred->key;
            return true;
        }
        return false;
    }

    node ** right_min(node * n) {
        node ** s = &right(n);
        while(*s && left(*s))
            s = &left(*s);
        return s;
    }

    void inorder() { inorder(root); std::cout << std::endl; }
    void preorder() { preorder(root); std::cout << std::endl; }
    void postorder() { postorder(root); std::cout << std::endl; }

    void levelorder() { // Por niveles
        if (!root) return;
        std::queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            node* curr = q.front();
            q.pop();
            std::cout << "(" << curr->key << ", " << curr->value << ") ";
            if (left(curr)) q.push(left(curr));
            if (right(curr)) q.push(right(curr));
        }
        std::cout << std::endl;
    }

    void free(node * n) {
        if(!n) return;
        free(left(n));
        free(right(n));
        delete n;
    }

    class iterator {
        std::stack<node*> s;
        node* curr;
        void push_left() {
            while (curr) {
                s.push(curr);
                curr = curr->child[0];
            }
            if (!s.empty()) {
                curr = s.top();
                s.pop();
            } else {
                curr = nullptr;
            }
        }
    public:
        explicit iterator(node* root) : curr(root) { push_left(); }
        iterator() : curr(nullptr) {}

        iterator& operator++() {
            if (curr) {
                curr = curr->child[1];
                push_left();
            }
            return *this;
        }
        bool operator!=(const iterator& other) const {
            return curr != other.curr;
        }
        std::pair<const K&, V&> operator*() {
            return {curr->key, curr->value};
        }
    };
    iterator begin() {
        return iterator(root);
    }
    iterator end() {
        return iterator(nullptr);
    }
};


int main()
{
    BSTree<int, bool> tree;

    tree.insert(10, 1);
    tree.insert(5, 1);
    tree.insert(15, 1);
    tree.insert(20, 1);
    tree.insert(12, 1);
    tree.insert(8, 1);
    tree.insert(4, 1);
    tree.insert(2, 1);

    std::cout << "Inorder: "; tree.inorder();
    std::cout << "Level-order: "; tree.levelorder();

    tree.remove(12);
    std::cout << "After deleting 12 \n Inorder: "; tree.inorder();

    tree[22] = false;
    std::cout << "Inorder after [22]=false: "; tree.inorder();

    tree[22] = true;

    std::cout << "\nRange based for loop" << std::endl;
    for (auto e : tree) {
        std::cout << "Key: " << e.first << " | Value: " << e.second << std::endl;
    }

    int res = 0;
    if (tree.successor(10, res)) {
        std::cout << "\nSuccessor of 10 is: " << res << std::endl;
    }
    if (tree.predecessor(10, res)) {
        std::cout << "Predecessor of 10 is: " << res << std::endl;
    }

    return 0;
}*/