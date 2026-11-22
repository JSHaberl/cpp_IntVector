#ifndef INTVECTOR_HPP
#define INTVECTOR_HPP
#include <cstddef>

namespace intvector {
    class Vector {

        public:
            Vector(int* arr = nullptr, size_t arrsize = 0);
            Vector(size_t fillsize, int num = 0);
            int at(int index) const {return array_[index];};
            size_t size() const{return size_;};
            int pop_back();
            void push_back(int num);
            bool empty() const {return size_ == 0;};
            Vector operator+(Vector& other) const;
            int operator[](int index) const {return this->at(index);}
            ~Vector(){delete array_;};

        private:
            void resize(size_t cap);
            void copy(int* arr, size_t size = 0);
            size_t size_;
            size_t capacity_;
            int* array_;

    };
}



#endif
