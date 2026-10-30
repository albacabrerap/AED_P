/*#include <iostream>
#include <vector>
#include <initializer_list>
#include <utility>

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
    size_t size_val = 0;

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
        size_val = 0;
    }

    linked_list(const linked_list & other) {
        for (node * n = other.head; n; n = n->next) {
            push_back(n->dato);
        }
    }

    linked_list(linked_list && other) noexcept
        : head(other.head), tail(other.tail), size_val(other.size_val) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_val = 0;
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
            size_val = other.size_val;
            other.head = nullptr;
            other.tail = nullptr;
            other.size_val = 0;
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
        size_val++;
    }

    void push_back(const T & d) {
        node * n = new node(d, nullptr, tail);
        if (tail) {
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size_val++;
    }

    void pop_front() {
        if (size_val == 0) return;
        node * temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size_val--;
    }

    void pop_back() {
        if (size_val == 0) return;
        node * temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size_val--;
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
        size_val--;
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
        size_val++;
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
        if (this == &other || other.size_val == 0) return;
        if (size_val == 0) {
            head = other.head;
            tail = other.tail;
            size_val = other.size_val;
            other.head = other.tail = nullptr;
            other.size_val = 0;
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
        size_val += other.size_val;

        other.head = other.tail = nullptr;
        other.size_val = 0;
    }

    size_t get_size() const {
        return size_val;
    }

    size_t size() const {
        return size_val;
    }

    T& operator[](size_t index) {
        node* curr = head;
        for (size_t i = 0; i < index && curr; ++i) curr = curr->next;
        return curr->dato;
    }

    const T& operator[](size_t index) const {
        node* curr = head;
        for (size_t i = 0; i < index && curr; ++i) curr = curr->next;
        return curr->dato;
    }

    friend std::ostream & operator << (std::ostream & os, const linked_list<T> & ll) {
        os << "head <-> ";
        for (node * n = ll.head; n; n = n->next)
            os << n->dato << " <-> ";
        os << "nullptr";
        return os;
    }
};


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
    size_t size_val = 0;

    node* reverseRc(node* curr) {
        if (!curr) return nullptr;
        node * temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        if (!temp) return curr;
        return reverseRc(temp);
    }

public:
    doubly_linked_list() = default;

    ~doubly_linked_list() {
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
        size_val = 0;
    }

    doubly_linked_list(const doubly_linked_list & other) {
        for (node * n = other.head; n; n = n->next) {
            push_back(n->dato);
        }
    }

    doubly_linked_list(doubly_linked_list && other) noexcept
        : head(other.head), tail(other.tail), size_val(other.size_val) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_val = 0;
    }

    doubly_linked_list & operator=(const doubly_linked_list & other) {
        if (this != &other) {
            clear();
            for (node * n = other.head; n; n = n->next) {
                push_back(n->dato);
            }
        }
        return *this;
    }

    doubly_linked_list & operator=(doubly_linked_list && other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size_val = other.size_val;
            other.head = nullptr;
            other.tail = nullptr;
            other.size_val = 0;
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
        size_val++;
    }

    void push_back(const T & d) {
        node * n = new node(d, nullptr, tail);
        if (tail) {
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size_val++;
    }

    void pop_front() {
        if (size_val == 0) return;
        node * temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size_val--;
    }

    void pop_back() {
        if (size_val == 0) return;
        node * temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size_val--;
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
        size_val--;
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
        size_val++;
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

    void merge(doubly_linked_list & other) {
        if (this == &other || other.size_val == 0) return;
        if (size_val == 0) {
            head = other.head;
            tail = other.tail;
            size_val = other.size_val;
            other.head = other.tail = nullptr;
            other.size_val = 0;
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
        size_val += other.size_val;

        other.head = other.tail = nullptr;
        other.size_val = 0;
    }

    size_t get_size() const {
        return size_val;
    }

    size_t size() const {
        return size_val;
    }

    T& operator[](size_t index) {
        node* curr = head;
        for (size_t i = 0; i < index && curr; ++i) curr = curr->next;
        return curr->dato;
    }

    const T& operator[](size_t index) const {
        node* curr = head;
        for (size_t i = 0; i < index && curr; ++i) curr = curr->next;
        return curr->dato;
    }

    friend std::ostream & operator << (std::ostream & os, const doubly_linked_list<T> & ll) {
        os << "head <-> ";
        for (node * n = ll.head; n; n = n->next)
            os << n->dato << " <-> ";
        os << "nullptr";
        return os;
    }
};


template <typename T>
class vvector {
    T* dat_= nullptr;
    size_t size_ = 0;
    size_t cap_= 0;

    void change_cap(size_t new_cap) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(dat_[i]);
        }
        delete[] dat_;
        dat_ = new_data;
        cap_ = new_cap;
    }

public:
    vvector() : dat_(nullptr), size_(0), cap_(0) {}

    explicit vvector(size_t count, const T& value = T()) : size_(count), cap_(count) {
        dat_ = new T[cap_];
        for (size_t i = 0; i < size_; ++i) {
            dat_[i] = value;
        }
    }

    vvector(std::initializer_list<T> init) : size_(init.size()), cap_(init.size()) {
        dat_ = new T[cap_];
        size_t i = 0;
        for (const auto& item : init) {
            dat_[i++] = item;
        }
    }

    vvector(const vvector& other) : size_(other.size_), cap_(other.cap_) {
        dat_ = new T[cap_];
        for (size_t i = 0; i < size_; ++i) {
            dat_[i] = other.dat_[i];
        }
    }

    vvector(vvector&& other) noexcept : dat_(other.dat_), size_(other.size_), cap_(other.cap_) {
        other.dat_ = nullptr;
        other.size_= 0;
        other.cap_= 0;
    }

    ~vvector() {
        delete[] dat_;
    }

    vvector& operator=(const vvector& other) {
        if (this != &other) {
            delete[] dat_;
            size_ = other.size_;
            cap_ = other.cap_;
            dat_ = new T[cap_];
            for (size_t i = 0; i < size_; ++i) {
                dat_[i] = other.dat_[i];
            }
        }
        return *this;
    }

    vvector& operator=(vvector&& other) noexcept {
        if (this != &other) {
            delete[] dat_;
            dat_ = other.dat_;
            size_ = other.size_;
            cap_ = other.cap_;

            other.dat_ = nullptr;
            other.size_ = 0;
            other.cap_ = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (size_ == cap_) {
            size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
            change_cap(new_cap);
        }
        dat_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == cap_) {
            size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
            change_cap(new_cap);
        }
        dat_[size_++]= std::move(value);
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            dat_[size_].~T();
        }
    }

    T& operator[](size_t index) {
        return dat_[index];
    }
    const T& operator[](size_t index) const {
        return dat_[index];
    }

    T* begin() {
        return dat_;
    }
    T* end() {
        return dat_ + size_;
    }
    const T* begin() const {
        return dat_;
    }
    const T* end() const {
        return dat_ + size_;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }
    [[nodiscard]] size_t capacity() const {
        return cap_;
    }
    [[nodiscard]] bool empty() const {
        return size_ == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const vvector& s) {
        for (T c : s) {
            os << c << " ";
        }
        return os;
    }
};

template <typename T>
class circularBuffer {
    vvector<T> buffer_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t capacity_ = 0;
    size_t size_ = 0;
public:
    circularBuffer() : capacity_(0) {}
    explicit circularBuffer(size_t count) : capacity_(count), buffer_(count) {}

    void push(const T& item) {
        if (capacity_ == 0) return;
        buffer_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;
        if (size_ < capacity_) {
            size_++;
        } else {
            head_ = (head_ + 1) % capacity_;
        }
    }

    void pop() {
        if (size_ == 0) return;
        head_ = (head_ + 1) % capacity_;
        size_--;
    }

    T& front() { return buffer_[head_]; }
    const T& front() const { return buffer_[head_]; }

    T& back() { return buffer_[(tail_ + capacity_ - 1) % capacity_]; }
    const T& back() const { return buffer_[(tail_ + capacity_ - 1) % capacity_]; }

    [[nodiscard]] bool empty() const { return size_ == 0; }
    [[nodiscard]] bool full() const { return size_ == capacity_; }
    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] size_t capacity() const { return capacity_; }

    T& operator[](size_t index) { return buffer_[(head_ + index) % capacity_]; }
    const T& operator[](size_t index) const { return buffer_[(head_ + index) % capacity_]; }

    friend std::ostream & operator << (std::ostream & os, const circularBuffer& cb) {
        os << "Buffer -> ";
        for (size_t i = 0; i < cb.size(); ++i) {
            os << cb[i] << " ";
        }
        return os;
    }
};


template <typename T>
class linked_list_stack {
    linked_list<T> stack_;
public:
    linked_list_stack() = default;

    void push(const T& item) {
        stack_.push_front(item);
    }

    void pop() {
        stack_.pop_front();
    }

    [[nodiscard]] bool empty() const {
        return stack_.size() == 0;
    }

    const T& top() const {
        return stack_[0];
    }

    T& top() {
        return stack_[0];
    }

    [[nodiscard]] size_t size() const {
        return stack_.size();
    }

    T& operator[](size_t index) {
        return stack_[index];
    }

    const T& operator[](size_t index) const {
        return stack_[index];
    }

    friend std::ostream & operator << (std::ostream & os, const linked_list_stack<T> & s) {
        os << "Top -> ";
        for (size_t i = 0; i < s.size() ; i++) {
            os << s[i] << " ";
        }
        return os;
    }
};

template <typename T>
class vector_stack {
    vvector<T> stack_;
public:
    vector_stack() : stack_() {}

    void push(const T& item) {
        stack_.push_back(item);
    }

    void pop() {
        stack_.pop_back();
    }

    [[nodiscard]] bool empty() const {
        return stack_.empty();
    }

    [[nodiscard]] size_t size() const {
        return stack_.size();
    }

    const T& top() const {
        return stack_[stack_.size() - 1];
    }

    T& top() {
        return stack_[stack_.size() - 1];
    }

    T& operator[](size_t index) {
        return stack_[index];
    }

    const T& operator[](size_t index) const {
        return stack_[index];
    }

    friend std::ostream & operator << (std::ostream & os, const vector_stack& s) {
        os << "Top -> ";
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            os << s[i] << " ";
        }
        return os;
    }
};


template <typename T>
class linked_list_queue {
    linked_list<T> queue_;
public:
    linked_list_queue() = default;

    void enqueue(const T& item) {
        queue_.push_back(item);
    }

    void dequeue() {
        queue_.pop_front();
    }

    [[nodiscard]] bool empty() const {
        return queue_.size() == 0;
    }

    [[nodiscard]] size_t size() const {
        return queue_.size();
    }

    const T& front() const {
        return queue_[0];
    }

    T& front() {
        return queue_[0];
    }

    T& operator[](size_t index) {
        return queue_[index];
    }

    const T& operator[](size_t index) const {
        return queue_[index];
    }

    friend std::ostream & operator << (std::ostream & os, const linked_list_queue& s) {
        os << "Front -> ";
        for (size_t i = 0; i < s.size() ; i++) {
            os << s[i] << " ";
        }
        return os;
    }
};

template <typename T>
class vector_queue {
    vvector<T> queue_;
    size_t head_ = 0;
public:
    vector_queue() : queue_() {}

    void push(const T& item) {
        queue_.push_back(item);
    }

    void enqueue(const T& item) {
        push(item);
    }

    void pop() {
        if (!empty()) {
            head_++;
        }
    }

    void dequeue() {
        pop();
    }

    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    [[nodiscard]] size_t size() const {
        return queue_.size() - head_;
    }

    const T& top() const {
        return queue_[head_];
    }

    T& top() {
        return queue_[head_];
    }

    const T& front() const {
        return queue_[head_];
    }

    T& front() {
        return queue_[head_];
    }

    T& operator[](size_t index) {
        return queue_[head_ + index];
    }

    const T& operator[](size_t index) const {
        return queue_[head_ + index];
    }

    friend std::ostream & operator << (std::ostream & os, const vector_queue& s) {
        os << "Front -> ";
        for (size_t i = 0; i < s.size(); ++i) {
            os << s[i] << " ";
        }
        return os;
    }
};

template <typename T>
class queue_stack {
    linked_list_queue<T> enters;
    linked_list_queue<T> exits;
public:
    queue_stack() = default;

    void push(const T& item) {
        exits.enqueue(item);
        while (!enters.empty()) {
            exits.enqueue(enters.front());
            enters.dequeue();
        }
        std::swap(enters, exits);
    }

    void pop() {
        if (!enters.empty()) {
            enters.dequeue();
        }
    }

    const T& top() const {
        return enters.front();
    }

    T& top() {
        return enters.front();
    }

    [[nodiscard]] bool empty() const {
        return enters.empty();
    }

    [[nodiscard]] size_t size() const {
        return enters.size();
    }

    T& operator[](size_t index) {
        return enters[index];
    }

    const T& operator[](size_t index) const {
        return enters[index];
    }

    friend std::ostream & operator << (std::ostream & os, const queue_stack& s) {
        os << "Top -> ";
        for (size_t i = 0; i < s.size(); ++i) {
            os << s[i] << " ";
        }
        return os;
    }
};

template <typename T>
class stack_queue {
    linked_list_stack<T> in_stack_;
    linked_list_stack<T> out_stack_;

    void transfer() {
        if (out_stack_.empty()) {
            while (!in_stack_.empty()) {
                out_stack_.push(in_stack_.top());
                in_stack_.pop();
            }
        }
    }

public:
    stack_queue() = default;

    void enqueue(const T& item) {
        in_stack_.push(item);
    }

    void push(const T& item) {
        enqueue(item);
    }

    void dequeue() {
        transfer();
        if (!out_stack_.empty()) {
            out_stack_.pop();
        }
    }

    void pop() {
        dequeue();
    }

    const T& front() const {
        const_cast<stack_queue*>(this)->transfer();
        return out_stack_.top();
    }

    T& front() {
        transfer();
        return out_stack_.top();
    }

    [[nodiscard]] bool empty() const {
        return in_stack_.empty() && out_stack_.empty();
    }

    [[nodiscard]] size_t size() const {
        return in_stack_.size() + out_stack_.size();
    }

    friend std::ostream & operator << (std::ostream & os, const stack_queue& q) {
        os << "Front -> ";
        stack_queue copy = q;
        while (!copy.empty()) {
            os << copy.front() << " ";
            copy.dequeue();
        }
        return os;
    }
};

template <typename T>
class linked_list_deque {
    doubly_linked_list<T> deque_;
public:
    linked_list_deque() = default;

    void push_front(const T& item) {
        deque_.push_front(item);
    }

    void push_back(const T& item) {
        deque_.push_back(item);
    }

    void pop_front() {
        deque_.pop_front();
    }

    void pop_back() {
        deque_.pop_back();
    }

    const T& front() const {
        return deque_[0];
    }

    T& front() {
        return deque_[0];
    }

    const T& back() const {
        return deque_[deque_.size() - 1];
    }

    T& back() {
        return deque_[deque_.size() - 1];
    }

    [[nodiscard]] bool empty() const {
        return deque_.size() == 0;
    }

    [[nodiscard]] size_t size() const {
        return deque_.size();
    }

    T& operator[](size_t index) {
        return deque_[index];
    }

    const T& operator[](size_t index) const {
        return deque_[index];
    }

    friend std::ostream & operator << (std::ostream & os, const linked_list_deque& d) {
        os << "Front -> ";
        for (size_t i = 0; i < d.size(); ++i) {
            os << d[i] << " ";
        }
        return os;
    }
};

template <typename T>
class vector_deque {
    vvector<T> deque_;
    size_t head_ = 0;
public:
    vector_deque() = default;

    void push_back(const T& item) {
        deque_.push_back(item);
    }

    void push_front(const T& item) {
        vvector<T> temp;
        temp.push_back(item);
        for (size_t i = head_; i < deque_.size(); ++i) {
            temp.push_back(deque_[i]);
        }
        deque_ = std::move(temp);
        head_ = 0;
    }

    void pop_front() {
        if (!empty()) {
            head_++;
        }
    }

    void pop_back() {
        if (!empty()) {
            deque_.pop_back();
        }
    }

    const T& front() const {
        return deque_[head_];
    }

    T& front() {
        return deque_[head_];
    }

    const T& back() const {
        return deque_[deque_.size() - 1];
    }

    T& back() {
        return deque_[deque_.size() - 1];
    }

    [[nodiscard]] bool empty() const {
        return size() == 0;
    }

    [[nodiscard]] size_t size() const {
        return deque_.size() - head_;
    }

    T& operator[](size_t index) {
        return deque_[head_ + index];
    }

    const T& operator[](size_t index) const {
        return deque_[head_ + index];
    }

    friend std::ostream & operator << (std::ostream & os, const vector_deque& d) {
        os << "Front -> ";
        for (size_t i = 0; i < d.size(); ++i) {
            os << d[i] << " ";
        }
        return os;
    }
};

template <typename T>
class circular_buffer {
    vvector<T> buffer_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t capacity_ = 0;
    size_t size_ = 0;

    void resize(size_t new_capacity) {
        vvector<T> new_buffer(new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            new_buffer[i] = std::move(buffer_[(head_ + i) % capacity_]);
        }
        buffer_ = std::move(new_buffer);
        head_ = 0;
        tail_ = size_;
        capacity_ = new_capacity;
    }

public:
    circular_buffer() : capacity_(0) {}
    explicit circular_buffer(size_t capacity) : capacity_(capacity), buffer_(capacity) {}

    void push(const T& item) {
        push_back(item);
    }

    void push_back(const T& item) {
        if (capacity_ == 0) {
            resize(4);
        } else if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        buffer_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;
        size_++;
    }

    void push_front(const T& item) {
        if (capacity_ == 0) {
            resize(4);
        } else if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        head_ = (head_ + capacity_ - 1) % capacity_;
        buffer_[head_] = item;
        size_++;
    }

    void pop() {
        pop_front();
    }

    void pop_front() {
        if (size_ == 0) return;
        head_ = (head_ + 1) % capacity_;
        size_--;
    }

    void pop_back() {
        if (size_ == 0) return;
        tail_ = (tail_ + capacity_ - 1) % capacity_;
        size_--;
    }

    bool erase(size_t index) {
        if (index >= size_) return false;

        if (index == 0) {
            pop_front();
            return true;
        }
        if (index == size_ - 1) {
            pop_back();
            return true;
        }

        for (size_t i = index; i < size_ - 1; ++i) {
            size_t curr = (head_ + i) % capacity_;
            size_t next = (head_ + i + 1) % capacity_;
            buffer_[curr] = std::move(buffer_[next]);
        }

        tail_ = (tail_ + capacity_ - 1) % capacity_;
        size_--;
        return true;
    }

    T& front() { return buffer_[head_]; }
    const T& front() const { return buffer_[head_]; }

    T& back() { return buffer_[(tail_ + capacity_ - 1) % capacity_]; }
    const T& back() const { return buffer_[(tail_ + capacity_ - 1) % capacity_]; }

    [[nodiscard]] bool empty() const { return size_ == 0; }
    [[nodiscard]] bool full() const { return size_ == capacity_; }
    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] size_t capacity() const { return capacity_; }

    T& operator[](size_t index) { return buffer_[(head_ + index) % capacity_]; }
    const T& operator[](size_t index) const { return buffer_[(head_ + index) % capacity_]; }

    friend std::ostream & operator << (std::ostream & os, const circular_buffer& cb) {
        os << "Buffer -> ";
        for (size_t i = 0; i < cb.size(); ++i) {
            os << cb[i] << " ";
        }
        return os;
    }
};

template <typename T>
class circular_buffer_deque {
    circular_buffer<T> deque_;
public:
    circular_buffer_deque() = default;
    explicit circular_buffer_deque(size_t capacity) : deque_(capacity) {}

    void push_back(const T& item) {
        deque_.push_back(item);
    }
    void push_front(const T& item) {
        deque_.push_front(item);
    }
    void pop_front() {
        deque_.pop_front();
    }
    void pop_back() {
        deque_.pop_back();
    }

    bool erase(size_t index) {
        return deque_.erase(index);
    }

    const T& front() const {
        return deque_.front();
    }
    T& front() {
        return deque_.front();
    }
    const T& back() const {
        return deque_.back();
    }
    T& back() {
        return deque_.back();
    }

    [[nodiscard]] bool empty() const {
        return deque_.empty();
    }
    [[nodiscard]] size_t size() const {
        return deque_.size();
    }

    T& operator[](size_t index) {
        return deque_[index];
    }
    const T& operator[](size_t index) const {
        return deque_[index];
    }

    friend std::ostream & operator << (std::ostream & os, const circular_buffer_deque& d) {
        os << "Front -> ";
        for (size_t i = 0; i < d.size(); ++i) {
            os << d[i] << " ";
        }
        return os;
    }
};


int main()
{
    std::cout << "Stack with linked list\n";
    linked_list_stack<int> lls;
    lls.push(10);
    lls.push(20);
    lls.push(30);
    std::cout << "Contents: " << lls << "\n";
    std::cout << "Top element: " << lls.top() << "\n";
    std::cout << "Size: " << lls.size() << "\n";
    lls.pop();
    std::cout << "After pop: " << lls << "\n";
    std::cout << "Is empty: " << (lls.empty() ? "true" : "false") << "\n\n";

    std::cout << "Stack with vector\n";
    vector_stack<int> vs;
    vs.push(100);
    vs.push(200);
    vs.push(300);
    std::cout << "Contents: " << vs << "\n";
    std::cout << "Top element: " << vs.top() << "\n";
    vs.pop();
    std::cout << "After pop: " << vs << "\n\n";

    std::cout << "Stack with queues\n";
    queue_stack<int> qs;
    qs.push(1);
    qs.push(2);
    qs.push(3);
    std::cout << "Contents: " << qs << "\n";
    std::cout << "Top element: " << qs.top() << "\n";
    qs.pop();
    std::cout << "After pop: " << qs << "\n\n";

    std::cout << "Queue with linked list\n";
    linked_list_queue<int> llq;
    llq.enqueue(5);
    llq.enqueue(15);
    llq.enqueue(25);
    std::cout << "Contents: " << llq << "\n";
    std::cout << "Front element: " << llq.front() << "\n";
    std::cout << "Size: " << llq.size() << "\n";
    llq.dequeue();
    std::cout << "After dequeue: " << llq << "\n\n";

    std::cout << "Queue with vector\n";
    vector_queue<int> vq;
    vq.enqueue(50);
    vq.enqueue(150);
    vq.enqueue(250);
    std::cout << "Contents: " << vq << "\n";
    std::cout << "Front element: " << vq.front() << "\n";
    vq.dequeue();
    std::cout << "After dequeue: " << vq << "\n\n";

    std::cout << "Queue with two stacks\n";
    stack_queue<int> sq;
    sq.enqueue(500);
    sq.enqueue(1500);
    sq.enqueue(2500);
    std::cout << "Contents: " << sq << "\n";
    std::cout << "Front element: " << sq.front() << "\n";
    sq.dequeue();
    std::cout << "After dequeue: " << sq << "\n\n";

    std::cout << "Deque with double linked list\n";
    linked_list_deque<int> lld;
    lld.push_back(10);
    lld.push_back(20);
    lld.push_front(5);
    lld.push_front(1);
    std::cout << "Contents: " << lld << "\n";
    std::cout << "Front element: " << lld.front() << "\n";
    std::cout << "Back element: " << lld.back() << "\n";
    lld.pop_front();
    std::cout << "After pop_front: " << lld << "\n";
    lld.pop_back();
    std::cout << "After pop_back: " << lld << "\n\n";

    std::cout << "Deque with vector\n";
    vector_deque<int> vd;
    vd.push_back(100);
    vd.push_back(200);
    vd.push_front(50);
    std::cout << "Contents: " << vd << "\n";
    std::cout << "Front element: " << vd.front() << "\n";
    std::cout << "Back element: " << vd.back() << "\n";
    vd.pop_front();
    std::cout << "After pop_front: " << vd << "\n\n";

    std::cout << "Deque with Circular Buffer\n";
    circular_buffer_deque<int> cbd(4);
    cbd.push_back(10);
    cbd.push_back(20);
    cbd.push_front(5);
    cbd.push_front(1);
    std::cout << "Contents: " << cbd << "\n";
    std::cout << "Front element: " << cbd.front() << "\n";
    std::cout << "Back element: " << cbd.back() << "\n";
    cbd.pop_front();
    std::cout << "After pop_front: " << cbd << "\n";
    cbd.pop_back();
    std::cout << "After pop_back: " << cbd << "\n\n";

    return 0;

}*/