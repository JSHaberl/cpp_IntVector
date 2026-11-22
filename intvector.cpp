#include "intvector.hpp"

namespace intvector {

    Vector::Vector(int* arr, size_t arrsize) :  size_{arrsize}, capacity_{arrsize}{
        if (array_ == nullptr || size_ == 0) {
            array_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
        array_ = new int[size_];
        copy(arr, arrsize);

    };

    Vector::Vector(size_t fillsize, int num) : size_{fillsize}, capacity_{size_}{
        array_ = new int[capacity_];
        for (int i{0}; i < size_; i++) {
            array_[i] = num;
        }
    }

    void Vector::resize(size_t cap) {
        if (size_ < cap) {
            cap = size_;
        }
        capacity_ = cap;
        int* newarr = new int[capacity_];
        for (size_t i{0}; i < size_; i++) {
            newarr[i] = array_[i];
        }

        delete array_;
        array_ = newarr;
    }

    void Vector::copy(int* arr, size_t size){
        if (size == 0) {size = size_;} else {size_ = size;}
        delete array_;
        array_ = new int[size];
        for (size_t i{0}; i < size_; i++) {
            array_[i] = arr[i];
        }
    }

    int Vector::pop_back(){
        size_--;
        int returnVal = array_[size_];
        resize(size_);
        return returnVal;
    }

    void Vector::push_back(int num) {
        size_++;
        resize(size_);
        array_[size_ - 1] = num;
    }

    Vector Vector::operator+(Vector& other) const {
        size_t combinedSize = size_ + other.size_;
        int* newarr = new int[combinedSize];
        for (size_t i{0}; i < combinedSize; i++) {
            if (i < size_) { newarr[i] = array_[i];}
            else {newarr[i] = other.array_[i - size_];}
        }

        return Vector(newarr, combinedSize);
    }
}
