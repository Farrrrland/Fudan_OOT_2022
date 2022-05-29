# Fudan_OOT_2022
复旦大学面向对象技术 2022 年春季学期课程 Lab，要求实现⼀个根据绘图指令在内存中绘图的程序，程序读⼊写在脚本⽂件中的指令，打印后给出输出的结果。

### 项目结构
`files` 文件夹中为课程提供的 Lab 相关文件，包括要求和部分测试样例。

`include` 文件夹包括所有 `.h` 和 `.hpp` 为后缀的头文件。

`src` 文件夹包括所有 `.h` 后缀的头文件对应的源文件

`test` 文件夹包括所有测试用例及其标准输出模板，满足以下格式：
1. 所有自动测试用例按测试的指令类别归档
2. 手动测试用例存放于 `test/manual` 文件夹下，亦可以通过自动测试脚本进行测试
3. 测试用例命名为 `testi-g[2/256].txt` 或 `test-g[2/256].txt` 或 `scripti-g[2/256].txt`
4. 标准输出模板在对应的测试用例名称后添加后缀 `_result`

### 如何开始

#### 编译项目
```bash
bash make.sh
```

#### 手动测试
执行如下代码手动运行生成的可执行文件进行测试:
```bash
cd build
./draw -g [2/256] [input]
```
其中 `[2/256]` 指定使用的灰度级别，`[input]` 指定输入的指令脚本文件，手动测试脚本文件存放于 `/test/manual` 文件夹下，按 `files/testcase.md` 编写。执行命令后可以在终端看到对应的输出矩阵。

#### 自动化测试脚本
成功编译项目后执行自动化测试脚本可以进行自动化测试。自动化测试使用 CMake 集成的测试工具 CTest 实现，执行如下代码即可进行自动测试：
```bash
bash autotest.sh
```

执行自动化测试脚本**成功**后，命令行输出:
```bash
Test project /home/ec2-user/Fudan_OOT_2022/build
    Start 1: manual
1/7 Test #1: manual ...........................   Passed    0.02 sec
    Start 2: line
2/7 Test #2: line .............................   Passed    0.02 sec
    Start 3: text
3/7 Test #3: text .............................   Passed    0.01 sec
    Start 4: macro
4/7 Test #4: macro ............................   Passed    0.00 sec
    Start 5: color
5/7 Test #5: color ............................   Passed    0.01 sec
    Start 6: undo
6/7 Test #6: undo .............................   Passed    0.01 sec
    Start 7: redo
7/7 Test #7: redo .............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.10 sec
```

自动化测试**不通过**时，命令行输出:
```bash
Test project /home/ec2-user/Fudan_OOT_2022/build
    Start 1: manual
1/7 Test #1: manual ...........................   Passed    0.02 sec
    Start 2: line
2/7 Test #2: line .............................***Failed  Required regular expression not found. Regex=[OK]  0.01 sec
    Start 3: text
3/7 Test #3: text .............................   Passed    0.01 sec
    Start 4: macro
4/7 Test #4: macro ............................   Passed    0.00 sec
    Start 5: color
5/7 Test #5: color ............................   Passed    0.01 sec
    Start 6: undo
6/7 Test #6: undo .............................   Passed    0.01 sec
    Start 7: redo
7/7 Test #7: redo .............................   Passed    0.01 sec

86% tests passed, 1 tests failed out of 7

Total Test time (real) =   0.09 sec

The following tests FAILED:
          2 - line (Failed)
Errors while running CTest
Output from these tests are in: /home/ec2-user/Fudan_OOT_2022/build/Testing/Temporary/LastTest.log
Use "--rerun-failed --output-on-failure" to re-run the failed cases verbosely.
```
并在对应的输入文件所在的文件夹下生成 `test.failure` 文件，其中包含错误输出对应的输入文件以及标准输出格式的信息。