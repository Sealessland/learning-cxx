#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

int main(int argc, char **argv) {
    // 1. 构造大小为 100，默认值为 true
    std::vector<bool> vec(100, true);

    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");

    // NOTICE: 平台相关！CI:Ubuntu (libstdc++) 上通常是 40 字节。
    // 普通 vector 是 24 字节 (3个指针)，但 vector<bool> 需要记录位偏移(offset)，
    // 它的迭代器包含 {指针, 偏移量}，导致结构变大。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");

    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // 关键点：auto 推导出的类型不是 bool，而是 std::vector<bool>::reference
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 初始是 true

        ref = false; // 这里通过代理对象修改了 vec 内部的那个 bit

        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        // 因为 ref 是 vec[30] 的引用代理，修改 ref 就是修改 vec[30]
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}