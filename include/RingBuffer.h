#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <vector>
#include <stdexcept>
#include <cstddef>

template<class T>
class RingBuffer
{
public:
    explicit RingBuffer(size_t capacity)
        : m_buffer(capacity)
        , m_capacity(capacity)
        , m_size(0)
        , m_head(0)
    {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    void append(const T& item) {
        m_buffer[m_head] = item;
        m_head = (m_head + 1) % m_capacity;
        if (m_size < m_capacity) {
            m_size++;
        }
    }

    T& operator[](size_t index) {
        return at_impl(index);
    }

    const T& operator[](size_t index) const {
        return at_impl(index);
    }

    const T& at(size_t index) const {
        return at_impl(index);
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

private:
    // 非 const 版本的 at_impl
    T& at_impl(size_t index) {
        if (index < m_size) {
            size_t actual_index = (m_head - 1 - index + m_capacity) % m_capacity;
            return m_buffer[actual_index];
        }
        throw std::out_of_range("Index out of range");
    }

    // const 版本的 at_impl
    const T& at_impl(size_t index) const {
        if (index < m_size) {
            size_t actual_index = (m_head - 1 - index + m_capacity) % m_capacity;
            return m_buffer[actual_index];
        }
        throw std::out_of_range("Index out of range");
    }

    std::vector<T> m_buffer;
    size_t m_capacity;
    size_t m_size;
    size_t m_head;
};

#endif // RING_BUFFER_H
