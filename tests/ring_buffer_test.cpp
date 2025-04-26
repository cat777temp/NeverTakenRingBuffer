#include <iostream>
#include <string>
#include <cassert>
#include "RingBuffer.h"

void test_int_buffer() {
    std::cout << "Testing integer buffer..." << std::endl;

    RingBuffer<int> buffer(5);

    // 测试初始状态
    assert(buffer.size() == 0);
    assert(buffer.capacity() == 5);

    // 添加元素
    buffer.append(10);
    buffer.append(20);
    buffer.append(30);

    // 测试大小
    assert(buffer.size() == 3);

    // 测试at方法
    assert(buffer.at(0) == 30); // 最新的元素
    assert(buffer.at(1) == 20); // 次新的元素
    assert(buffer.at(2) == 10); // 最旧的元素

    // 添加更多元素
    buffer.append(40);
    buffer.append(50);
    buffer.append(60); // 这将覆盖最旧的元素(10)

    // 测试大小（应该等于容量）
    assert(buffer.size() == 5);

    // 测试at方法（环形缓冲区已满）
    assert(buffer.at(0) == 60); // 最新的元素
    assert(buffer.at(1) == 50);
    assert(buffer.at(2) == 40);
    assert(buffer.at(3) == 30);
    assert(buffer.at(4) == 20); // 现在最旧的元素

    std::cout << "Integer buffer test passed!" << std::endl;
}

void test_string_buffer() {
    std::cout << "Testing string buffer..." << std::endl;

    RingBuffer<std::string> buffer(3);

    buffer.append("first");
    buffer.append("second");
    buffer.append("third");

    assert(buffer.at(0) == "third");
    assert(buffer.at(1) == "second");
    assert(buffer.at(2) == "first");

    buffer.append("fourth"); // 覆盖 "first"

    assert(buffer.at(0) == "fourth");
    assert(buffer.at(1) == "third");
    assert(buffer.at(2) == "second");

    std::cout << "String buffer test passed!" << std::endl;
}

void test_boundary_conditions() {
    std::cout << "Testing boundary conditions..." << std::endl;

    // 测试零容量
    try {
        RingBuffer<int> buffer(0);
        assert(false); // 不应该到达这里
    } catch (const std::invalid_argument& e) {
        // 预期的异常
    }

    // 测试越界访问 - 现在会抛出异常
    RingBuffer<int> buffer(3);
    buffer.append(10);

    // 测试越界访问应该抛出异常
    try {
        int value = buffer.at(1); // 只有一个元素，索引1应该越界
        assert(false); // 不应该到达这里
    } catch (const std::out_of_range& e) {
        // 预期的异常
    }

    // 测试修改元素
    buffer[0] = 20; // 使用operator[]修改元素
    assert(buffer.at(0) == 20); // 验证修改成功

    std::cout << "Boundary conditions test passed!" << std::endl;
}

class TestClass
{
public:
    TestClass() : buffer(3) {}
private:
    RingBuffer<std::string> buffer;
};

void testUsingRingBufferInClass() {
    std::cout << "Testing using RingBuffer in a class..." << std::endl;
    TestClass testClass;
    std::cout << "Using RingBuffer in a class test passed!" << std::endl;
}

int main() {
    std::cout << "Running RingBuffer tests..." << std::endl;

    test_int_buffer();
    test_string_buffer();
    test_boundary_conditions();
    testUsingRingBufferInClass();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
