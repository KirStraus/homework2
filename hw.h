#include <map>
#include <iostream>

template<typename T>
    struct logging_allocator {
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U>;
    };

    logging_allocator() = default;
    ~logging_allocator() = default;

    template<typename U> 
    logging_allocator(const logging_allocator<U>&) {

    }

    T *allocate(std::size_t n = 10) {
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t) {

        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {

        p->~T();
    }
};

class custom_map {
    public:

    std::map <int, int, std::less<int>, logging_allocator<std::pair<const int, int>>> mp;
    int counter = 0;

    int fill_custom_map(){
        for (int count = 0; count < 10; ++count){
            if (count == 0){
                mp[count] = 1;
            }
            else {
                mp[count] = mp[count -1] * count;
            }
        }
        counter = 10;
        return 0;
    }

    int print_custom_map(){
        for(auto it = mp.cbegin(); it != mp.cend(); ++it){
            std::cout << it->first << " " << it -> second<< " " << "\n";
        }
        return 0;
    }
    
    int add_next_element(){
        mp[counter] = mp[counter-1] * counter;
        counter += 1;
        return 0;
    }
};

