#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    // shared(1) + ptrs[0](1) + ptrs[1](1) + ptrs[2](1) = 4
    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    // ptrs[0] 释放。剩余：shared, ptrs[1], ptrs[2] = 3
    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    // ptrs[1] 释放。剩余：shared, ptrs[2] = 2
    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    // ptrs[2] 指向了一个新创建的 int(10)。
    // ptrs[2] 放弃了对原对象的引用。
    // 剩余持有原对象者：只有 shared = 1
    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    // ptrs[0] = shared (count 1->2)
    // ptrs[1] = shared (count 2->3)
    // ptrs[2] = std::move(shared)
    //    1. shared 的所有权转移给 ptrs[2]
    //    2. shared 变为空
    //    3. ptrs[2] 之前持有的那个新对象被释放，改为持有原对象
    // 此时持有者：ptrs[0], ptrs[1], ptrs[2] = 3
    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");

    // 陷阱：std::ignore = std::move(ptrs[0])
    // std::ignore 的赋值操作是空操作，它不会“吞掉”右值，所以 ptrs[0] 保持不变。
    // ptrs[1] = std::move(ptrs[1]) 是自赋值，通常无影响。
    // ptrs[1] = std::move(ptrs[2])
    //    1. ptrs[2] 的所有权转移给 ptrs[1]
    //    2. ptrs[1] 原本的引用被覆盖（计数 -1）
    //    3. ptrs[2] 变为空
    // 结果：ptrs[1] 和 ptrs[2] 指向同一个对象，现在合并了。
    // 剩余持有者：ptrs[0], ptrs[1] = 2
    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");

    // lock() 创建一个新的 shared_ptr 指向对象。 count 2 -> 3
    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    // shared 释放 (3->2)
    // 循环释放 ptrs[0] (2->1), ptrs[1] (1->0)
    // 对象被销毁。
    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    // 对象已销毁，lock() 失败返回空指针
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}