# CLion + xmake 配置指南

本项目已创建 CMakeLists.txt 文件，完全对标原有的 xmake.lua 配置。

## 快速开始（CLion）

### 方法 1：直接在 CLion 中使用 CMakeLists.txt（推荐）

1. **打开项目**
   - File → Open → 选择 `/home/sealessland/learning-tools/exercises/learning-cxx`

2. **配置 CMake**
   - Settings → Build, Execution, Deployment → CMake
   - 确保 CMake 版本 ≥ 3.15
   - Build directory: 默认或自定义（如 `cmake-build-debug`）

3. **重新加载项目**
   - CLion 会自动检测到 CMakeLists.txt
   - 等待 CMake 配置完成（右下角进度条）

4. **运行目标**
   - 在编辑器右上角或 Run 菜单选择要执行的目标
   - 例如：`learn`, `summary`, `exercise00` 等

### 方法 2：在 CLion 中继续使用 xmake

如果您想保留 xmake，可以在 CLion 中配置外部构建工具：

1. **Settings → Build, Execution, Deployment → Custom Build Targets**

2. **添加新的构建目标**：
   ```
   Program: xmake
   Arguments: build
   Working directory: $ProjectFileDir$
   ```

3. **添加运行配置**：
   - Run → Edit Configurations
   - 点击 `+` → Custom Build Application
   - Build: `xmake build exercise00`
   - Executable: `build/linux/x86_64/debug/exercise00`

## 文件对应关系

| xmake.lua | CMakeLists.txt |
|-----------|----------------|
| `add_rules("mode.debug", "mode.release")` | CMake 自动处理 |
| `set_encodings("utf-8")` | 已配置 `-finput-charset=UTF-8` |
| `set_warnings("all")` | 已配置 `-Wall` |
| `set_languages("cxx17")` | `CMAKE_CXX_STANDARD 17` |
| `target("test")` | `add_library(test STATIC ...)` |
| `target("learn")` | `add_executable(learn ...)` |
| `target("exercise00")` | `add_executable(exercise00 ...)` |

## 项目结构

```
learning-cxx/
├── CMakeLists.txt           ← 新建（主配置）
├── xmake.lua                ← 原配置（可选保留）
├── learn/
│   ├── test.cpp
│   ├── learn.cpp
│   └── summary.cpp
└── exercises/
    ├── CMakeLists.txt       ← 新建（子配置）
    ├── xmake.lua            ← 原配置
    ├── 00_hello_world/
    ├── 01_variable&add/
    ├── ...
    └── 33_std_accumulate/
```

## CLion 快速操作

### 编译目标
- **Ctrl+F9** (Windows/Linux) / **Cmd+F9** (macOS)：编译当前目标
- **Ctrl+Shift+F9**：编译全部

### 运行目标
- **Shift+F10** (Windows/Linux) / **Ctrl+R** (macOS)：运行当前配置

### 创建运行配置
1. Run → Edit Configurations
2. 点击 `+` → Executable
3. Name: `exercise00`
4. Executable: `exercise00`
5. Click Run

## 常见问题

### 问题 1：CMake 找不到编译器
**解决**：Settings → Build, Execution, Deployment → Toolchains
- 确保 GCC/Clang 路径正确
- 点击 "Reload CMake Project"

### 问题 2：Include 文件报错
**解决**：
- Right-click 文件夹 → Mark Directory As → Sources Root
- Settings → Editor → File Encodings 设为 UTF-8

### 问题 3：要在 xmake 和 CMake 之间切换
**解决**：
- 两个配置文件都已提供，可以同时存在
- xmake：`xmake build exercise00`
- CMake：CLion 直接运行

## 编译和运行示例

### 使用 CMake
```bash
# 配置
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# 编译
cmake --build build

# 运行
./build/exercise00
./build/learn
```

### 使用 xmake（原方式）
```bash
xmake
xmake run exercise00
xmake run learn
```

## 配置文件说明

### CMakeLists.txt 特点
- ✅ 完全对标 xmake.lua
- ✅ CLion 原生支持
- ✅ 跨平台兼容
- ✅ 支持所有 exercise 目标

### 保留的兼容性
- `__XMAKE__` 宏已映射到 CMake（虽然未被使用）
- C++17 标准
- UTF-8 编码
- 所有警告开启

## 推荐工作流

1. **开发阶段**：使用 CMake + CLion IDE（更方便的断点调试）
2. **CI/CD 阶段**：使用 xmake（更便于自动化脚本）
3. **两者并行**：项目中两个配置文件都可以保留

---

如有问题，检查：
1. CMake 版本是否 ≥ 3.15
2. C++ 编译器是否支持 C++17
3. 文件路径中是否包含中文（可能导致编码问题）

