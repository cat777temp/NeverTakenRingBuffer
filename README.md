# RingBuffer

一个高效的环形缓冲区模板类实现，用于存储最近的数据项并按照从新到旧的顺序访问它们。

## 特性

- 模板实现，可以存储任何类型的数据
- 当缓冲区满时自动覆盖最旧的数据
- 通过索引从最新到最旧访问数据（at(0)返回最新数据）
- 无需担心缓冲区溢出异常
- 简单易用的接口

## 使用方法

### 基本用法

```cpp
#include "include/RingBuffer.h"
#include <iostream>

int main() {
    // 创建一个容量为5的整数环形缓冲区
    RingBuffer<int> buffer(5);
    
    // 添加数据
    buffer.append(10);
    buffer.append(20);
    buffer.append(30);
    
    // 访问数据
    std::cout << "最新的数据: " << buffer.at(0) << std::endl;  // 输出: 30
    std::cout << "次新的数据: " << buffer.at(1) << std::endl;  // 输出: 20
    std::cout << "最旧的数据: " << buffer.at(2) << std::endl;  // 输出: 10
    
    // 添加更多数据，超过缓冲区容量
    buffer.append(40);
    buffer.append(50);
    buffer.append(60);  // 这将覆盖最旧的数据(10)
    
    // 现在缓冲区包含: [60, 50, 40, 30, 20]
    std::cout << "最新的数据: " << buffer.at(0) << std::endl;  // 输出: 60
    std::cout << "最旧的数据: " << buffer.at(4) << std::endl;  // 输出: 20
    
    return 0;
}
```

### 使用自定义类型

```cpp
#include "include/RingBuffer.h"
#include <string>
#include <iostream>

int main() {
    // 创建一个容量为3的字符串环形缓冲区
    RingBuffer<std::string> buffer(3);
    
    buffer.append("first");
    buffer.append("second");
    buffer.append("third");
    
    // 访问数据
    std::cout << buffer.at(0) << std::endl;  // 输出: third
    std::cout << buffer.at(1) << std::endl;  // 输出: second
    std::cout << buffer.at(2) << std::endl;  // 输出: first
    
    // 添加更多数据，覆盖最旧的
    buffer.append("fourth");  // 覆盖 "first"
    
    // 现在缓冲区包含: [fourth, third, second]
    std::cout << buffer.at(0) << std::endl;  // 输出: fourth
    std::cout << buffer.at(1) << std::endl;  // 输出: third
    std::cout << buffer.at(2) << std::endl;  // 输出: second
    
    return 0;
}
```

## API 参考

### 构造函数

```cpp
explicit RingBuffer(size_t capacity)
```

创建一个指定容量的环形缓冲区。

**参数:**
- `capacity`: 缓冲区的最大容量（必须大于0）

### 方法

#### append

```cpp
void append(const T& item)
```

将新项添加到缓冲区。如果缓冲区已满，则覆盖最旧的项。

**参数:**
- `item`: 要添加的项

#### at

```cpp
const T& at(size_t index) const
T& at(size_t index)
```

按索引访问缓冲区中的项，其中索引0表示最新项，索引1表示次新项，依此类推。

**参数:**
- `index`: 要访问的项的索引

**返回值:**
- 如果索引有效，则返回对应项的引用
- 如果索引无效（超出范围），则返回默认构造的静态对象

#### size

```cpp
size_t size() const
```

返回缓冲区中当前项的数量。

**返回值:**
- 缓冲区中当前项的数量

#### capacity

```cpp
size_t capacity() const
```

返回缓冲区的最大容量。

**返回值:**
- 缓冲区的最大容量

## 构建和测试

本项目使用CMake构建系统。按照以下步骤构建和运行测试：

```bash
mkdir build
cd build
cmake ..
cmake --build .
./ring_buffer_test
```

## 许可证

[MIT License](LICENSE)
