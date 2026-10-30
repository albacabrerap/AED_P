/*#include <iostream>

template <class T>
class doubly_linked_list
{
    struct node
    {
        T dato;
        node * next = nullptr;
        node * prev = nullptr;

        node(const T & d, node * n = nullptr, node * p = nullptr) : dato(d), next(n), prev(p) {}
    };

    node * head = nullptr;
    node * tail = nullptr;
    size_t size = 0;

    node* reverseRc(node* curr) {
        if (!curr) return nullptr;
        node * temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        if (!temp) return curr;
        return reverseRc(temp);
    }

public:
    linked_list() = default;

    ~linked_list() {
        clear();
    }

    void clear() {
        node * curr = head;
        while (curr) {
            node * next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    linked_list(const linked_list & other) {
        for (node * n = other.head; n; n = n->next) {
            push_back(n->dato);
        }
    }

    linked_list(linked_list && other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    linked_list & operator=(const linked_list & other) {
        if (this != &other) {
            clear();
            for (node * n = other.head; n; n = n->next) {
                push_back(n->dato);
            }
        }
        return *this;
    }

    linked_list & operator=(linked_list && other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void push_front(const T & d) {
        node * n = new node(d, head, nullptr);
        if (head) {
            head->prev = n;
        } else {
            tail = n;
        }
        head = n;
        size++;
    }

    void push_back(const T & d) {
        node * n = new node(d, nullptr, tail);
        if (tail) {
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size++;
    }

    void pop_front() {
        if (size == 0) return;
        node * temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (size == 0) return;
        node * temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    node ** search(const T & d) {
        node ** n = &head;
        while (*n && (*n)->dato != d)
            n = &(*n)->next;
        return n;
    }

    node ** remove(node ** n) {
        if (!n || !*n) return n;

        node * nt = *n;
        *n = nt->next;
        if (nt->next) {
            nt->next->prev = nt->prev;
        } else {
            tail = nt->prev;
        }
        delete nt;
        size--;
        return n;
    }

    node ** insert(node ** n, const T & d) {
        if (!n) return n;
        node * target = *n;
        if (target) {
            node * p = target->prev;
            node * new_node = new node(d, target, p);
            target->prev = new_node;
            *n = new_node;
        } else {
            node * p = tail;
            node * new_node = new node(d, nullptr, p);
            *n = new_node;
            tail = new_node;
            if (!head) head = new_node;
        }
        size++;
        return n;
    }

    node ** front() {
        return &head;
    }

    void reverse() {
        tail = head;
        node * current = head;
        node * temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    void reverseRcp() {
        if (!head) return;
        tail = head;
        head = reverseRc(head);
    }

    void merge(linked_list & other) {
        if (this == &other || other.size == 0) return;
        if (size == 0) {
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = other.tail = nullptr;
            other.size = 0;
            return;
        }

        node dummy{T()};
        node * tail_merged = &dummy;

        node * p1 = head;
        node * p2 = other.head;

        while (p1 && p2) {
            node * next_node = nullptr;
            if (p1->dato <= p2->dato) {
                next_node = p1;
                p1 = p1->next;
            } else {
                next_node = p2;
                p2 = p2->next;
            }
            tail_merged->next = next_node;
            next_node->prev = (tail_merged == &dummy) ? nullptr : tail_merged;
            tail_merged = tail_merged->next;
        }
        if (p1) {
            tail_merged->next = p1;
            p1->prev = tail_merged;
        } else if (p2) {
            tail_merged->next = p2;
            p2->prev = tail_merged;
            tail = other.tail;
        }

        head = dummy.next;
        size += other.size;

        other.head = other.tail = nullptr;
        other.size = 0;
    }

    size_t get_size() const {
        return size;
    }

    friend std::ostream & operator << (std::ostream & os, const linked_list<T> & ll) {
        os << "head <-> ";
        for (node * n = ll.head; n; n = n->next)
            os << n->dato << " <-> ";
        os << "nullptr";
        return os;
    }
};

int main()
{
    linked_list<int> ll;
    for (int i = 1; i <= 5; ++i)
        ll.push_front(i);

    std::cout << "Original list:\n" << ll << "\n\n";

    std::cout << "First node" << (*ll.front())->dato << "\n\n";

    ll.reverse();
    std::cout << "Reverse:\n" << ll << "\n\n";

    ll.reverseRcp();

    linked_list<int> l2;
    l2.push_back(20);
    l2.push_back(40);
    l2.push_back(60);

    std::cout << "List 2: " << l2 << "\n\n";

    ll.merge(l2);
    std::cout << "Merged List 1: " << ll << "\n";
    std::cout << "List 2 after merge: " << l2 << "\n\n";

    ll.pop_front();
    ll.pop_back();
    std::cout << "After pop_front() and pop_back(): " << ll << "\n\n";

    ll.insert(ll.search(30), 25);
    std::cout << "After inserting 25 before 30: " << ll << "\n\n";

    ll.remove(ll.search(40));
    std::cout << "After removing 40: " << ll << "\n";

    return 0;
}*/