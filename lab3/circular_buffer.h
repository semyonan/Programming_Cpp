#include <stdio.h>
#define DEFAULT_SIZE 4

class buf_out_of_range : public std::out_of_range {
    public:
        buf_out_of_range(const std::string& msg)
            : std::out_of_range(msg) {}
};

template <class T>
class circular_buffer {
private:
	T *buf_;
	unsigned int head_;
	unsigned int tail_ ;
	unsigned int capacity_;
	bool full_;
    bool empty_;
    void set(unsigned int head, unsigned int tail, bool full, bool empty) {
        head_ = head;
        tail_ = tail;
        full_ = full;
        empty_ = empty;
    }
public:
    class iterator {
        public:
            
            typedef iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef T** p_pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef int difference_type;
            iterator(pointer ptr, pointer first, pointer last) : ptr_(ptr), first_(first), last_(last) {};

            self_type operator++() {
                if (ptr_ == last_) {
                    ptr_ = first_;
                } else {
                    ptr_++;
                }
                return *this;
            }

            self_type operator++(int junk) {
                self_type i = *this; 

                if (i.ptr_ == i.last_) {
                    i.ptr_ = i.first_;
                } else {
                    i.ptr_++;
                }

                return i; 
            }

            reference operator*() { return *ptr_; }
            pointer operator->() { return ptr_; }
            bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
            bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        private:
            pointer ptr_, first_, last_;
    };

    class const_iterator {
        public:
            typedef const_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef T** p_pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef int difference_type;
            const_iterator(const pointer ptr, pointer first, pointer last) : ptr_(ptr), first_(first), last_(last) {};

            self_type operator++() {
                if (ptr_ == last_) {
                    ptr_ = first_;
                } else {
                    ptr_++;
                }
                return *this;
            }

            self_type operator++(int junk) {
                self_type i = *this; 

                if (i.ptr_ == i.last_) {
                    i.ptr_ = i.first_;
                } else {
                    i.ptr_++;
                }

                return i; 
            }

            reference operator*() { return *ptr_; }
            pointer operator->() { return ptr_; }
            bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
            bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        private:
            const pointer ptr_;
            pointer first_, last_;
    };

	circular_buffer() : circular_buffer(DEFAULT_SIZE) {}

    circular_buffer(unsigned int size) :
		capacity_(size+1),
        buf_(new T[capacity_]),
        head_(0),
        tail_(0),
        full_(false),
        empty_(true)
	{}

    circular_buffer(const circular_buffer &cp) :
        capacity_(cp.capacity_),
        buf_(cp.buf_),
        head_(cp.head_),
        tail_(cp.tail_),
        full_(cp.full_),
        empty_(cp.empty_)
    {}

    circular_buffer & operator=(const circular_buffer &cp) {
        if (this != &cp) {
            capacity_ = cp.capacity_;
            buf_ = cp.buf_;
            head_ = cp.head_;
            tail_ = cp.tail_;
            full_ = cp.full_;
            empty_ = cp.empty_;
        }
        return *this;
    }

    void push_back(const T &item) {
       
        if (is_full()) {
            if (capacity_ == 1)  {
                resize(capacity_*2);
            } else {
                resize((capacity_ - 1)*2);
            }
        }
        
        buf_[tail_] = item;
        tail_ = (tail_ + 1) % capacity_;

        empty_ = tail_ == head_;
    }

    void push_front(const T &item) {
       
        if (is_full()) {
            if (capacity_ == 1)  {
                resize(capacity_*2);
            } else {
                resize((capacity_ - 1)*2);
            }
        }

        head_ = (head_ + (capacity_ - 1))%capacity_;
        buf_[head_] = item;

        empty_ = tail_ == head_;
    }

    void pop_back() {
        if (empty_) {
            throw buf_out_of_range("You are trying to pop empty buffer\n");
        }

        tail_ = (tail_ + (capacity_ - 1)) % capacity_;
        full_ = false;
        
        empty_ = head_ == tail_;

        if (empty_) {
            tail_ = 0;
            head_ = 0;
        }
    }

	void pop_front() {
        if (empty_) {
            throw buf_out_of_range("You are trying to pop empty buffer\n");
        }

        head_ = (head_ + 1) % capacity_;
        full_ = false;
        
        empty_ = head_ == tail_;

        if (empty_) {
            tail_ = 0;
            head_ = 0;
        }

    }

    T front() {
        if (empty_) {
            throw buf_out_of_range("Buffer is empty\n");
        }
        return buf_[head_];
    } 

    T back() {
        if (empty_) {
            throw buf_out_of_range("Buffer is empty\n");
        }
        return buf_[(tail_ + (capacity_ - 1))%capacity_];
    }

    T& operator[](unsigned int ind) {
        if (ind >= capacity_ - 1) {
            throw buf_out_of_range("Index is out of buf range");
        } 
        return buf_[(head_ + ind)%capacity_];
    }

    const T& operator[](unsigned int ind) const {
        if (ind >= capacity_ - 1) {
            throw buf_out_of_range("Index is out of buf range");
        } 
        return buf_[(head_ + ind)%capacity_];
    }

	void reset() {
        set(0, 0, false, true);
    }

    void resize(unsigned int new_capacity_) {
        if (new_capacity_ == 0) {
            set(0, 0, false, true);
            capacity_ = 1;
            return;
        } else if (new_capacity_ + 1 == capacity_) {
            return;
        }

        T *tmp = new T[new_capacity_ + 1];

        for (int i = 0, j = head_;((i < size()) && (i < new_capacity_)); i++) {
            tmp[i] = buf_[j];
            j = (j+1)%capacity_;
        }

        delete[] buf_;
        buf_ = tmp;

        if (new_capacity_ > size()) {
            if (empty_) {
                set(0, 0, false, true);
            } else {
                set(0, size(), false, false);
            }
        } else { 
            set(0, new_capacity_, true, false);
        } 
    
        capacity_ = new_capacity_ + 1;
        
        tmp = nullptr;
    };

	bool empty() const {
	    //if head and tail are equal, we are empty
	    return empty_;
    };

	bool is_full() {
	    //If tail is ahead the head by 1, we are full
        full_ =  ((!empty_) && (tail_ + 1)%capacity_ == head_) || (capacity_ == 1);
	    return full_;
    };
    
    unsigned int size() {
        if (empty_) {
            return 0;
        } else if (head_ < tail_) {
            return tail_ - head_;
        } else {
            return capacity_ - head_ + tail_;
        }
    }

	unsigned int capacity() const {
        return capacity_;
    };

    iterator begin() {
        return iterator(buf_ + head_, buf_, buf_ + capacity_ - 1);
    };

    iterator end() {
        return iterator(buf_ + tail_%capacity_, buf_, buf_ + capacity_ - 1);
    };

    const_iterator cbegin() const {
        return const_iterator(buf_ + head_, buf_, buf_ + capacity_ - 1);
    };

    const_iterator cend() const {
        return const_iterator(buf_ + tail_%capacity_, buf_, buf_ + capacity_ - 1);
    };

    ~circular_buffer() {
        delete[] buf_;
    }
};