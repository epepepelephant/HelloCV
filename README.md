# HelloCV


**2025-10-19**



# 凯撒加密cpp设计思路（主要都在语雀中，这里大致说一下思路
* 指定了用面向对象的方式构建且指定了三个类
1. Crypto类
  a. 加密   就是改变字符的ASCII码
  b. 解密   同理
2. FileHandler类
  a. 读取文本   用ifstream
  b. 保存文本   用ofstream
3. Menu类
  a. 菜单显示   cout
  b. 整合前面两个函数实现功能
4. 主函数


# 运行编译（cmake）
* 采用 **源码外构建** ，把可执行文件都放在build里面
* 其余的就是cmake的基础写法（设置cmake版本，定义项目名称，生成可执行文件）
* make  编译文件
* ./kaisa 运行文件


* 这一周的语雀文档在“语雀第二周里”









**2025-10-12**

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
大致思路：先疯狂apt，把编译器啥的都下载下来，再把tasks.json文件（编译任务配置）修改位OpenCV专用设置，然后创建launch.json文件让他帮我能自动编译和调试  还有tasks.json,同时配置上了OpenCV和c/cpp。
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build_normal",  // 任务名称（需与launch.json的preLaunchTask一致）
      "type": "shell",
      "command": "g++",
      "args": [
          "-g",                  // 生成调试信息（必须）
          "${workspaceFolder}/normal_app.cpp",  // 普通程序的路径
          "-o",                  // 输出可执行文件
          "${workspaceFolder}/normal_app"       // 普通程序的可执行文件路径
      ],
      "group": "build",
      "problemMatcher": ["$gcc"]  // 识别GCC编译错误
  },
    {
      "label": "Build OpenCV",  // 任务名称，需与launch.json的preLaunchTask一致
      "type": "shell",          // 类型为shell，让Shell处理命令替换
      "command": "bash",        // 使用bash执行命令
      "args": [
        "-c",                   // 执行字符串形式的命令
        "g++ ${file} -o ${fileDirname}/${fileBasenameNoExtension} $(pkg-config --cflags --libs opencv4)"  // 完整编译命令
      ],
      "group": {
        "kind": "build",
        "isDefault": true       // 设置为默认编译任务（Ctrl+Shift+B直接运行）
      },
      "problemMatcher": ["$gcc"]  // 匹配GCC错误信息
    }
    
  ]
},
{
  "version": "0.2.0",
  "configurations": [
      // 调试配置1：普通C++程序（normal_app）
      {
          "name": "debug_normal",  // 配置名称（需在复合配置中引用）
          "type": "cppdbg",
          "request": "launch",
          "program": "${workspaceFolder}/normal_app",  // 可执行文件路径（与tasks.json一致）
          "args": [],             // 程序运行参数（无则留空）
          "stopAtEntry": false,   // 是否在main函数入口暂停（新手可设为true）
          "cwd": "${workspaceFolder}",  // 工作目录
          "externalConsole": false,      // 使用VSCode内置终端（推荐）
          "MIMode": "gdb",               // 调试器（Linux默认GDB）
          "miDebuggerPath": "/usr/bin/gdb",  // GDB路径（通过`which gdb`验证）
          "preLaunchTask": "build_normal"   // 调试前执行的构建任务（与tasks.json的label一致）
      },
    {
      "name": "Launch OpenCV",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/${fileBasenameNoExtension}", // 运行的可执行文件
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",  // gdb路径（WSL默认路径）
      "preLaunchTask": "Build OpenCV",   // 调试前执行的任务，必须和tasks.json的label一致
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    }
  ],
  "compounds": [
    {
        "name": "debug_both",  // 复合配置名称（显示在调试菜单中）
        "configurations": ["debug_normal", "Launch OpenCV"],  // 组合的调试配置名称（需与上面的name一致）
        "stopAll": true        // 停止复合配置时，同时停止所有子调试会话（推荐）
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