#include <map>
#include <iostream>

template<typename T>
    struct logging_allocator {
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        void* meme;
        bool is_zanyato[10] { false, false, false, false, false, false, false, false, false, false };

    template<typename U>
    struct rebind {
        using other = logging_allocator<U>;
    };

    logging_allocator(){
        //std::cout << "constructor\n";
        meme = std::malloc(10*sizeof(T));
        if (!meme){
            throw std::bad_alloc();
        }
    }
    ~logging_allocator()
    {
        //std::cout << "destructor\n";
        std::free(meme);
    }

    template<typename U> 
    logging_allocator(const logging_allocator<U>&) {

    }

    T *allocate(std::size_t count) {
        //std::cout << "allocate bytes: " << count << '\n';
        for (int i = 0; i < 10; ++i) {
            if (is_zanyato[i] == false) {
                bool elementsInRowIsNotBisy = true;
                for (int j = 1; j < static_cast<int> (count); ++j) {
                    if (is_zanyato[i + j]) {
                        elementsInRowIsNotBisy = false;
                        break;
                    }
                }
                if (elementsInRowIsNotBisy) {
                    //std::cout << "element with offset " << i << (reinterpret_cast<T *>(meme) + i) << '\n';
                    for (int j = 0; j < static_cast<int> (count); ++j) {
                        is_zanyato[i + j] = true;
                    }

                    return reinterpret_cast<T *>(meme) + i;
                }
            }
        }
        throw std::bad_alloc();
//        return reinterpret_cast<T *>(meme);
    }

    void deallocate(T* ptr, std::size_t count) {
        T* memeWithType = reinterpret_cast<T*>(meme);
        const int firstIndex = ptr - memeWithType;
        for (int i = 0; i < static_cast<int> (count); ++i) {
            is_zanyato[firstIndex + i] = false;
        }
    }

    template<typename U, typename ...Args>
    void construct(U *meme, Args &&...args) {
        new(meme) U(std::forward<Args>(args)...);
    }

    void destroy(T *meme) {
        meme->~T();
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

