#pragma once
#define TT template <typename T>
#include <utility>


TT
class WeakPtr;

class ControlBlock {
public:

    ControlBlock();

    void increment_shared();
    void decrement_shared();
    void increment_weak();
    void decrement_weak();
    size_t get_shared_count() const;

private:
    size_t shared_count;
    size_t weak_count;
};


TT
class SharedPtr {
public:

    SharedPtr();
    explicit SharedPtr(T* raw_ptr);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;

    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    ~SharedPtr();
    T& operator*() const;
    T* operator->() const;
    bool operator!() const;
    T* get() const;
    bool valid() const;
    void reset(T* raw_ptr = nullptr);
    friend class WeakPtr<T>;

private:
    T* ptr;
    ControlBlock* control;
    void free();
};


TT
class WeakPtr {
public:
    
    WeakPtr();
    WeakPtr(const SharedPtr<T>& sp);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;

    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(const SharedPtr<T>& sp);
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    ~WeakPtr();
    bool expired() const;
    SharedPtr<T> lock() const;

private:
    T* ptr;
    ControlBlock* control;
    void free();
};

inline ControlBlock::ControlBlock() : shared_count(1), weak_count(0) {}

inline void ControlBlock::increment_shared() { ++shared_count; }

inline void ControlBlock::decrement_shared() {
    if (--shared_count == 0 && weak_count == 0) delete this;
}

inline void ControlBlock::increment_weak() { ++weak_count; }

inline void ControlBlock::decrement_weak() {
    if (--weak_count == 0 && shared_count == 0) delete this;
}

inline size_t ControlBlock::get_shared_count() const { return shared_count; }

TT
SharedPtr<T>::SharedPtr() : ptr(nullptr), control(nullptr) {}

TT
SharedPtr<T>::SharedPtr(T* raw_ptr) : ptr(raw_ptr), control(raw_ptr ? new ControlBlock() : nullptr) {}

TT
SharedPtr<T>::SharedPtr(const SharedPtr& other) : ptr(other.ptr), control(other.control) {
    if (control) control->increment_shared();
}

TT
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), control(other.control) {
    other.ptr = nullptr;
    other.control = nullptr;
}

TT
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    if (this != &other) {
        free();
        ptr = other.ptr;
        control = other.control;
        if (control) control->increment_shared();
    }
    return *this;
}

TT
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        free();
        ptr = other.ptr;
        control = other.control;
        other.ptr = nullptr;
        other.control = nullptr;
    }
    return *this;
}

TT
SharedPtr<T>::~SharedPtr() { free(); }

TT
T& SharedPtr<T>::operator*() const { return *ptr; }

TT
T* SharedPtr<T>::operator->() const { return ptr; }

TT
bool SharedPtr<T>::operator!() const
{
    return !this->get();
}

TT
T* SharedPtr<T>::get() const { return ptr; }

TT
bool SharedPtr<T>::valid() const { return ptr != nullptr; }

TT
void SharedPtr<T>::reset(T* raw_ptr) {
    free();
    ptr = raw_ptr;
    control = raw_ptr ? new ControlBlock() : nullptr;
}

TT
void SharedPtr<T>::free() {
    if (control) {
        control->decrement_shared();
        if (control->get_shared_count() == 0) {
            delete ptr;
            ptr = nullptr;
        }
        control = nullptr;
    }
}

TT
WeakPtr<T>::WeakPtr() : ptr(nullptr), control(nullptr) {}

TT
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sp) : ptr(sp.ptr), control(sp.control) {
    if (control) control->increment_weak();
}

TT
WeakPtr<T>::WeakPtr(const WeakPtr& other) : ptr(other.ptr), control(other.control) {
    if (control) control->increment_weak();
}

TT
WeakPtr<T>::WeakPtr(WeakPtr&& other) noexcept : ptr(other.ptr), control(other.control) {
    other.ptr = nullptr;
    other.control = nullptr;
}

TT
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) {
    if (this != &other) {
        free();
        ptr = other.ptr;
        control = other.control;
        if (control) control->increment_weak();
    }
    return *this;
}

TT
WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& sp) {
    free();
    ptr = sp.ptr;
    control = sp.control;
    if (control) control->increment_weak();
    return *this;
}

TT
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        free();
        ptr = other.ptr;
        control = other.control;
        other.ptr = nullptr;
        other.control = nullptr;
    }
    return *this;
}

TT
WeakPtr<T>::~WeakPtr() { free(); }

TT
bool WeakPtr<T>::expired() const { return control == nullptr || control->get_shared_count() == 0; }

TT
SharedPtr<T> WeakPtr<T>::lock() const {
    if (expired()) return SharedPtr<T>();
    SharedPtr<T> sp;
    sp.ptr = ptr;
    sp.control = control;
    control->increment_shared();
    return sp;
}

TT
void WeakPtr<T>::free() {
    if (control) {
        control->decrement_weak();
        control = nullptr;
    }
    ptr = nullptr;
}
