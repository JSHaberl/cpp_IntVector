#include "intvector.hpp"

namespace intvector {

    Vector::Vector(int* arr, size_t arrsize, size_t cap) :  size_{arrsize}, capacity_{cap}{
        if (arr == nullptr || size_ == 0) {
            array_ = nullptr;
            size_ = 0;
        }
        if (size_ >= capacity_) {capacity_ = size_ * 2;}
        array_ = new int[capacity_];
        copy(arr, arrsize);

    };

    Vector::Vector(size_t fillsize, int num, size_t cap) : size_{fillsize}, capacity_{cap}{
        if (fillsize >= capacity_) {capacity_ = fillsize * 2;}
        array_ = new int[capacity_];
        for (int i{0}; i < size_; i++) {
            array_[i] = num;
        }
    }

    void Vector::resize(size_t cap, int fill) {
        if (size_ > cap || cap > size_ * 2) {
            return;
        }
        capacity_ = cap;
        int* newarr = new int[capacity_];
        for (size_t i{0}; i < size_; i++) {
            newarr[i] = array_[i];
        }
        for (size_t i{size_}; i < capacity_; i++){
            newarr[i] = fill;
        }

        delete[] array_;
        array_ = newarr;
    }

    void Vector::copy(int* arr, size_t size){
        if (size == 0) {size = size_;} else {size_ = size;}
        if (size > capacity_) {capacity_ = size * 2; delete[] array_; array_ = new int[capacity_];}
        for (size_t i{0}; i < size_; i++) {
            array_[i] = arr[i];
        }
    }

    int Vector::pop_back(){
        size_--;
        int returnVal = array_[size_];
        if (size_ <= capacity_ / 2 && capacity_ > 100) resize(size_);
        return returnVal;
    }

    void Vector::push_back(int num) {
        size_++;
        if (size_ >= capacity_) {resize(size_ * 2);}
        array_[size_ - 1] = num;
    }

    Vector Vector::operator+(Vector& other) const {
        size_t combinedCapacity = capacity_ + other.capacity_;
        size_t combinedSize = size_ + other.size_;
        int* newarr = new int[combinedSize];
        for (size_t i{0}; i < combinedSize; i++) {
            if (i < size_) { newarr[i] = array_[i];}
            else {newarr[i] = other.array_[i - size_];}
        }

        return Vector(newarr, combinedSize);
    }
}
