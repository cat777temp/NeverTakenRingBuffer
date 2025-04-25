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

    const T& at(size_t index) const {
        // 如果索引超出范围，返回默认值（不抛出异常）
        if (index >= m_size) {
            static T default_value = T();
            return default_value;
        }
        size_t actual_index = (m_head - 1 - index + m_capacity) % m_capacity;
        return m_buffer[actual_index];
    }

    T& at(size_t index) {
        // 如果索引超出范围，返回默认值（不抛出异常）
        if (index >= m_size) {
            static T default_value = T();
            return default_value;
        }
        size_t actual_index = (m_head - 1 - index + m_capacity) % m_capacity;
        return m_buffer[actual_index];
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

private:
    std::vector<T> m_buffer;
    size_t m_capacity;
    size_t m_size;
    size_t m_head;
};

#endif // RING_BUFFER_H
