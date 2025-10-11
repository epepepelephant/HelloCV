# HelloCV
* 语雀笔记链接在note.md里 包含
    Linux学习
    Git版本控制
    任务
    双系统
## 环境配置
## 省流
| 任务         | 实现方案                          | 验证方法                     |
|---------------|---------------------------------|------------------------------|
| ROS2安装      | 小鱼ros2                         | ros2 --version            |
| OpenCV        | 无脑APT(4.5.4)                   | pkg-config --modversion opencv4 |
| VS Code配置   | 完成ROS2和OpenCV的路径配置        | 可以运行（                     |
| Git配置       | SSH密钥                          | git config --list         |

### 1.ROS2安装
用鱼香写好的安装包一键安装
wget http://fishros.com/install -O fishros && . fishros
用humble版本即可
### 2.OpenCV
sudo apt-get update    #更新检查
sudo apt-get install libcv-dev   /*安装opencv
sudo apt-get install libopencv-dev    */
### 3.VSC配置
大致思路：先疯狂apt，把编译器啥的都下载下来，再把tasks.json文件（编译任务配置）修改位OpenCV专用设置，然后创建launch.json文件让他帮我能自动编译和调试
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build OpenCV",  // 任务名称（需与launch.json的preLaunchTask一致）
      "type": "shell",         // 用shell执行命令（支持管道、变量）
      "command": "g++",        // 编译器（g++）
      "args": [
        "-g",                // 生成调试信息（必须，否则无法调试）
        "${file}",           // 当前编辑的.cpp文件（输入文件）
        "-o",                // 输出可执行文件
        "${fileDirname}/${fileBasenameNoExtension}",  // 可执行文件路径（如./test）
        // OpenCV编译参数（通过pkg-config获取，必须正确）
        "$(pkg-config --cflags opencv4)",  // OpenCV头文件路径（如-I/usr/include/opencv4）
        "$(pkg-config --libs opencv4)"     // OpenCV库文件路径（如-lopencv_core -lopencv_highgui）
      ],
      "group": {
        "kind": "build",     // 将任务归到"build"组（可通过Ctrl+Shift+B运行）
        "isDefault": true    // 设置为默认build任务
      },
      "problemMatcher": ["$gcc"],  // 识别gcc的错误输出（显示在"问题"面板）
      "detail": "Compiler: g++ (OpenCV 4.5.x)"  // 任务描述（可选）
    }
  ]
}
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Launch OpenCV",  // 调试配置名称（显示在调试面板）
            "type": "cppdbg",        // 调试类型（C++调试，使用gdb）
            "request": "launch",     // 启动调试（而非附加到已运行程序）
            "program": "${fileDirname}/${fileBasenameNoExtension}",  // 可执行文件路径（与tasks.json的输出一致）
            "args": [],              // 程序运行的命令行参数（可选，如图片路径）
            "stopAtEntry": false,    // 是否在main函数入口处停止（可选，设为true方便调试）
            "cwd": "${fileDirname}", // 当前工作目录（程序运行的路径，如./）
            "environment": [],       // 环境变量（可选）
            "externalConsole": false,// 是否使用外部控制台（可选，设为true显示命令行窗口）
            "MIMode": "gdb",         // 调试器模式（gdb）
            "miDebuggerPath": "/usr/bin/gdb",  // 调试器路径（WSL Ubuntu的默认路径，必须正确）
            "preLaunchTask": "Build OpenCV",   // 调试前运行的任务（必须与tasks.json的label一致）
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",  // 启用gdb的漂亮打印（显示结构体等）
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
### 4.Git配置
1. sudo apt update
sudo apt install git
2. 设置用户名和邮箱
3. 生成SSH密钥
ssh-keygen -t rsa -b 4096 -C "your.email@example.com"
4. 把公钥丢到GitHub里
cat ~/.ssh/id_rsa.pub
5. 连接ssh
问题分析：配置GitHub使用备用端口，本来是22端口报错了😰
总结下来就是修改～/.ssh/config，把端口改为443（GitHub备用端口），反正教程是这么教的
