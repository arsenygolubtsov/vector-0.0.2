#include <iostream>

template <typename T>
class vector_t
{
private:
    T* elements_;
    std::size_t size_;
    std::size_t capacity_;

public:
    vector_t();
    vector_t(vector_t const& other);
    vector_t& operator=(vector_t const& other);
    ~vector_t();

    std::size_t size() const;
    std::size_t capacity() const;

    void push_back(T value);
    void pop_back();

    T& operator[](std::size_t index);
    T operator[](std::size_t index) const;

    bool operator==(vector_t const& other) const;

    T& at(std::size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Error");
        }
        return (*this)[index];
    }
};

template <typename T>
vector_t<T>::vector_t()
{
     elements_ = nullptr;
     size_ = 0;
     capacity_ = 0;
}

template <typename T>
vector_t<T>::vector_t(vector_t const & other)
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = new T[capacity_];
    for (int i = 0; i < other.size_; ++i) {
        elements_[i] = other.elements_[i];
    }
}

template <typename T>
vector_t<T> & vector_t<T>::operator =(vector_t const & other)
{
    delete[] elements_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    T *elements_ = new T [capacity_];
    for (int i = 0; i < other.size_; ++i) {
        elements_[i] = other.elements_[i];
    }
	return *this;
}

template <typename T>
bool vector_t<T>::operator ==(vector_t const & other) const
{
	bool success = false;
	if (size_ == other.size_ && capacity_ == other.capacity_) {
		for (std::size_t i=0; i<other.size_; i++) {
			if (elements_[i] != other.elements_[i]) return success;
		}
		success = !success;
	}
	return success;
}

template <typename T>
vector_t<T>::~vector_t()
{
    delete[] elements_;
}

template <typename T>
std::size_t vector_t<T>::size() const
{
    return size_;
}

template <typename T>
std::size_t vector_t<T>::capacity() const
{
    return capacity_;
}

template <typename T>
void vector_t<T>::push_back(T value)
{
    if(size_ == capacity_) {
	    if(capacity_ == 0) {
            capacity_ = 1;
            size_ = 1;
            elements_ = new T[capacity_];
            elements_[0] = value;
            }
            else {
                T *mas;
                mas = new T[size_];
                for(std::size_t i = 0; i < size_; ++i) {
                    mas[i] = elements_[i];
                }
                delete [] elements_;
                capacity_ = 2 * capacity_;
                elements_ = new T[capacity_];
                for(std::size_t i = 0; i < size_; ++i) {
                    elements_[i] = mas[i];
                }
                delete [] mas;
                elements_[size_] = value;
                size_ ++;
            }
    }    
    else {
        elements_[size_] = value;
        size_ ++;
    }
}

template <typename T>
void vector_t<T>::pop_back()
{
    size_ --;
    if(size_ == 0 || size_ * 4 == capacity_) {
        T *mas;
        mas = new T[size_];
        for(std::size_t i = 0; i < size_; ++i) {
            mas[i] = elements_[i];
        }
        delete [] elements_;
        capacity_ = capacity_ / 2;
        elements_ = new T[capacity_];
        for(std::size_t i = 0; i < size_; ++i) {
            elements_[i] = mas[i];
        }
        delete [] mas;
    }        
}

template <typename T>
T & vector_t<T>::operator [](std::size_t index)
{
	return elements_[index];
}

template <typename T>
T vector_t<T>::operator [](std::size_t index) const
{
	return elements_[index];
}

template <typename T>
bool operator !=(vector_t<T> const & lhs, vector_t<T> const & rhs)
{
	bool success = true;
	if (lhs == rhs) {
		success = !success;
	}
	
	return success;
}
