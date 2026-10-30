/*
#include <iostream>

template <class T>
class linked_list
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


template<class T>
class hhash {
    int cant = 0;
    size_t size = 100;
    linked_list<T> *list;

public:

    hhash() {
        list = new linked_list<T>[size];
    }

    explicit hhash(int size_) : cant(0), size(size_) {
        list = new linked_list<T>[size];
    }

    ~hhash() {
        delete[] list;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            list[i].clear();
        }
        cant = 0;
    }

    [[nodiscard]] int hashfunc(const int i) const {
        return i % size;
    }

    [[nodiscard]] int hashfunc(const std::string& v) const {
        int sum = 0;
        for (auto& c : v)
            sum = ((sum * 26) % size + (c - 'A' + 1)) % size;
        return sum;
    }

    hhash(const hhash &other) : cant(other.cant), size(other.size) {
        list = new linked_list<T>[size];
        for (int i = 0; i < size; ++i) {
            list[i] = other.list[i];
        }
    }

    hhash(hhash &&other) noexcept : cant(other.cant), size(other.size), list(other.list) {
        other.list = nullptr;
        other.cant = 0;
        other.size = 0;
    }

    hhash &operator=(const hhash &other) {
        if (this != &other) {
            delete[] list;
            cant = other.cant;
            size = other.size;
            list = new linked_list<T>[size];
            for (int i = 0; i < size; ++i) {
                list[i] = other.list[i];
            }
        }
        return *this;
    }

    hhash &operator=(hhash &&other) noexcept {
        if (this != &other) {
            delete[] list;
            cant = other.cant;
            size = other.size;
            list = other.list;
            other.list = nullptr;
            other.cant = 0;
            other.size = 0;
        }
        return *this;
    }


    void insert(const T d) {
        list[hashfunc(d)].push_back(d);
        cant++;
    }

    void remove(const T d) {
        int bucketIndex = hashfunc(d);
        auto target = list[bucketIndex].search(d);
        if (target && *target) {
            list[bucketIndex].remove(target);
            cant--;
            }
        }

    auto search(const T d) {
        int bucketIndex = hashfunc(d);
        return list[bucketIndex].search(d);
    }

    friend std::ostream & operator << (std::ostream & os, const hhash<T> & ll) {
        for (int i = 0; i < ll.cant; ++i) {
            os << ll.list[i] << " ";
        }
        return os;
    }


};

int main() {
    hhash<int> hash(10); //table of size 10

    hash.insert(42);
    hash.insert(15);
    hash.insert(82);
    hash.insert(7);

    // search
    int searchVal = 82;
    auto foundVal = hash.search(searchVal);
    if (foundVal && *foundVal) {
        std::cout << "Found " << searchVal << " in the hash table.\n";
    } else {
        std::cout << searchVal << " not found.\n";
    }

    // missing value
    searchVal = 99;
    foundVal = hash.search(searchVal);
    if (foundVal && *foundVal) {
        std::cout << "Found " << searchVal << " in the hash table.\n";
    } else {
        std::cout << searchVal << " not found.\n";
    }

    hhash<std::string> stringHash(20);

    stringHash.insert("app");
    stringHash.insert("boar");
    stringHash.insert("crimson");

    if (auto foundStr = stringHash.search("boar"); foundStr && *foundStr) {
        std::cout << "Found 'boar' in the hash table.\n";
    } else {
        std::cout << "'Boar' not found.\n";
    }

    //print hash tables
    std::cout<<hash << std::endl;
    std::cout << stringHash << std::endl;


    return 0;
}
*/

