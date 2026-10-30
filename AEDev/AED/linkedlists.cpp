/*#include <iostream>

template <class T>
class linked_list
{
    struct node
    {
        T dato;
        node * next = nullptr;

        // node constructor
        node(const T & d, node * n = nullptr) : dato(d), next(n) {}
    };

    node * head = nullptr;
    node * tail = nullptr;
    size_t size = 0;

    // private reverse
    node* reverseRc(node* curr) {
        //empty list or reached the last node
        if (!curr || !curr->next) {
            return curr;
        }
        // recurse to tail
        node* newHead = reverseRc(curr->next);

        // reverse the link
        curr->next->next = curr;
        curr->next = nullptr;

        return newHead;
    }

public:
    linked_list() = default;

    // destructor
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

    // copy constructor
    linked_list(const linked_list & other) {
        for (node * n = other.head; n; n = n->next) {
            push_back(n->dato);
        }
    }

    // move constructor
    linked_list(linked_list && other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // copy operator
    linked_list & operator=(const linked_list & other) {
        if (this != &other) {
            clear();
            for (node * n = other.head; n; n = n->next) {
                push_back(n->dato);
            }
        }
        return *this;
    }

    // move operator
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
        head = new node(d, head);
        if (size == 0) {
            tail = head;
        }
        size++;
    }

    void push_back(const T & d) {
        node * n = new node(d);
        if (size == 0) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        size++;
    }

    void pop_front() {
        if (size == 0) return;
        node * temp = head;
        head = head->next;
        delete temp;
        size--;

        if (size == 0) {
            tail = nullptr;
        }
    }

    void pop_back() {
        if (size == 0) return;

        if (size == 1) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        node * curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }

        delete tail;
        tail = curr;
        tail->next = nullptr;
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
        if (nt == tail) {
            // udating
            tail = nullptr;
        }
        *n = nt->next;
        delete nt;
        size--;
        return n;
    }

    node ** insert(node ** n, const T & d) {
        *n = new node(d, *n);
        if ((*n)->next == nullptr) {
            tail = *n;
        }
        size++;
        return n;
    }

    // access pointer-to-pointer to head
    node ** front() {
        return &head;
    }

    // I
    // iterative reverse
    void reverse() {
        tail = head;
        node * current = head;
        node * temp = nullptr;

        while (current != nullptr) {
            node * next = current->next;
            current->next = temp;
            temp = current;
            current = next;
        }
        head = temp;
    }

    // recursive reverse made public
    void reverseRcp() {
        if (!head) return;
        tail = head;
        head = reverseRc(head); // privately sets the new head
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
            if (p1->dato <= p2->dato) {
                tail_merged->next = p1;
                p1 = p1->next;
            } else {
                tail_merged->next = p2;
                p2 = p2->next;
            }
            tail_merged = tail_merged->next;
        }
        if (p1) {
            tail_merged->next = p1;
        } else {
            tail_merged->next = p2;
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
        os << "head -> ";
        for (node * n = ll.head; n; n = n->next)
            os << n->dato << " -> ";
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

    // front pointer-to-pointer access
    std::cout << "First node" << (*ll.front())->dato << "\n\n";

    // iterative reverse
    ll.reverse();
    std::cout << "Reverse:\n" << ll << "\n\n";

    // recursive reverse
    ll.reverseRcp();

    linked_list<int> l2;
    l2.push_back(20);
    l2.push_back(40);
    l2.push_back(60);

    std::cout << "List 2: " << l2 << "\n\n";

    // merge l2 into ll
    ll.merge(l2);
    std::cout << "Merged List 1: " << ll << "\n";
    std::cout << "List 2 after merge: " << l2 << "\n\n";

    // pop operations
    ll.pop_front();
    ll.pop_back();
    std::cout << "After pop_front() and pop_back(): " << ll << "\n\n";

    // search and insert
    ll.insert(ll.search(30), 25);
    std::cout << "After inserting 25 before 30: " << ll << "\n\n";

    // search and remove
    ll.remove(ll.search(40));
    std::cout << "After removing 40: " << ll << "\n";




    return 0;
}*/