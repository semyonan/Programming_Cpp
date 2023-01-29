#include <algorithm>
#include <memory>
#include <vector>

bool comp(const std::pair<std::pair<int, int>, std::vector<uint8_t*> > &a, const std::pair<std::pair<int, int>, std::vector<uint8_t*> > &b) {
    return a.first.first < b.first.first;
};

bool comp1(const std::pair<std::pair<int, int>, std::vector<uint8_t*> > &b, const int &val) {
    return b.first.first < val;
};

bool comp2(const std::pair<std::pair<int, int>, std::vector<uint8_t*> > &b, uint8_t* val) {
    return b.second[0] < val;
};

template<class T>
class custom_allocator {
    static_assert(!std::is_same_v<T, void>, "Type of the allocator can not be void");
    private:
        std::shared_ptr<uint8_t> mem;
        std::shared_ptr<std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > > ptr_chunks;
        size_t size;
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef T&& rereference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        template<class Other> 
        struct rebind { typedef custom_allocator<Other> other; };

        std::shared_ptr<uint8_t> get_mem() const { return mem; }

        std::shared_ptr<std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > > get_ptr_chunks() const { return ptr_chunks; }

        size_t get_size() const { return size; }

        custom_allocator() : custom_allocator({80, 160, 320, 640, 1280}, {8, 16, 32, 64, 128} ) { }
        custom_allocator(const std::vector<int> &sizes, const std::vector<int> &nums) {
            if (sizes.size() != nums.size()) {  
                throw std::logic_error("Sizes size and num size isn't the same");
            }

            int num = sizes.size();
            ptr_chunks = std::make_shared<std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > >();
            std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > &chunks = *(ptr_chunks.get());
            chunks.resize(num);

            size = 0;
            int ptr = 0;
            for (int i = 0; i < num; i++) {
                chunks[i].first.first = sizes[i];
                chunks[i].first.second = nums[i];
                chunks[i].second.resize(nums[i]);
                size += nums[i]*sizes[i];
            }

            sort(chunks.begin(), chunks.end(), comp);

            uint8_t* begin = static_cast<uint8_t*>(std::malloc(size));
            std::shared_ptr<uint8_t> temp(begin);
            mem = temp;

            for (int i = 0; i < num; ++i) {
                for(int j = 0; j < chunks[i].second.size(); ++j) {
                    chunks[i].second[j] = begin + ptr;
                    ptr += chunks[i].first.first;
                }
            }

            begin = nullptr;
            temp = nullptr;
        }

        template<class Other>
        custom_allocator(const custom_allocator<Other>& right) noexcept { 
            if (*this != right) {
                mem = right.get_mem();
                ptr_chunks = right.get_ptr_chunks();
                size = right.get_size();
            }
        }

        pointer allocate(size_type num_objects) {
            if (num_objects > max_size()) {
                throw std::bad_array_new_length();
            }

            if (num_objects == 0) {
                return nullptr;
            }

            int temp = num_objects*sizeof(T);
            std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > &chunks = *(ptr_chunks.get());

            std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > >::iterator cur = std::lower_bound(chunks.begin(), chunks.end(), temp, comp1);

            if (cur != chunks.end()) {
                if (cur->first.second == 0) {
                    for (auto iter = cur; iter != chunks.end(); ++iter) {
                        if (iter->first.second != 0) {
                            cur = iter;
                            break;
                        }
                    }
                }

                uint8_t* ptr = cur->second.back();
                cur->first.second--;
                if (cur->second.size() > 1) {
                    cur->second.pop_back();   
                }
                return reinterpret_cast<T*>(ptr);
            }

            throw std::bad_alloc();
        }

        void deallocate(T* ptr, size_type count) noexcept {
            if ((!ptr) || (count == 0)) {
                return;
            }

            std::uint8_t* deallocation_ptr = reinterpret_cast<std::uint8_t*>(ptr);
            auto begin = mem.get();
            std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > &chunks = *(ptr_chunks.get());

            uint8_t *temp = deallocation_ptr;

            std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > >::iterator cur = std::lower_bound(chunks.begin(), chunks.end(), temp, comp2);

            if ((cur != chunks.end()) && (deallocation_ptr == cur->second[0])) {
                cur->first.second++;
                return;
            }

            if ((cur == chunks.end()) && (deallocation_ptr < begin + size) 
                || ((cur->second[0] > deallocation_ptr) && (deallocation_ptr > begin))) {
                    --cur;
                    cur->first.second++;
                    cur->second.push_back(deallocation_ptr);
            }
        }

        template<typename U, typename... Args>
        void construct(U* ptr, Args&&... args) { new(reinterpret_cast<void*>(ptr)) U { std::forward<Args>(args)... }; }

        void destroy(pointer ptr) {
            ptr->~T();
        }

        size_type max_size() {
            std::vector<std::pair<std::pair<int, int>, std::vector<uint8_t*> > > &chunks = *(ptr_chunks.get());
            return chunks[chunks.size()-1].first.first/sizeof(T); 
        };

        template <class U>
        bool operator==(const custom_allocator <U>& b) { return mem == b.get_mem(); }

        template <class U>
        bool operator!=(const custom_allocator <U>& b) { return !(operator==(b)); }

        ~custom_allocator() { mem.reset(); ptr_chunks.reset();  }
};