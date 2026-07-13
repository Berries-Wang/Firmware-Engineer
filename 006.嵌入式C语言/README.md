# 嵌入式C语言

> 本目录收录嵌入式C语言相关的系列文章，涵盖 GCC 编译器属性、C 语言底层机制、Linux 开发工具等核心主题。

---

## 文章索引

| 编号 | 文章 | 核心技术 | 使用场景 | 功能概要 |
|:---:|:---|:---|:---|:---|
| 01 | [用 section 属性把代码搬出 Flash，让关键函数在 RAM 里飞起来](001.用%20section%20属性把代码搬出%20Flash，让关键函数在%20RAM%20里飞起来.png) | `__attribute__`((section)) | 高频中断、实时性要求高的关键代码 | 将关键函数/变量从Flash搬移到RAM执行，消除Flash等待周期，配合链接脚本实现启动时自动搬运。 |
| 02 | [不改一行源码，用 --wrap 给库函数装上监控](002.不改一行源码，用%20--wrap%20给库函数装上监控.png) | --wrap 链接器选项 | 库函数监控、调试、打桩测试 | 不改源码劫持库函数调用，通过 `__wrap_xxx` 和 `__real_xxx` 机制为函数装上监控层。 |
| 03 | [用 alias 给函数做分身，让旧接口悄悄变成新实现](003.用%20__attribute__((alias))给函数做"分身"，让旧接口悄悄变成新实现.png) | `__attribute__`((alias)) | 接口升级兼容旧版本 | 为函数创建别名，旧接口名自动转发到新实现，实现零成本的接口平滑升级。 |
| 04 | [用 cleanup 在 C 语言里优雅地自动释放资源](004.用%20__attribute__((cleanup))%20在%20C%20语言里优雅地自动释放资源.png) | `__attribute__`((cleanup)) | 资源自动释放、RAII风格C代码 | 变量离开作用域时编译器自动调用清理函数，优雅释放锁、内存、文件句柄等资源。 |
| 05 | [用 weak 写出可覆盖的函数，让框架优雅地留出后门](005.用%20__attribute__((weak))%20写出"可覆盖"的函数，让框架优雅地留出后门.png) | `__attribute__`((weak)) | 框架默认实现、用户覆盖 | 定义弱符号提供默认实现，用户通过同名强符号覆盖，常见于STM32 HAL库的弱回调机制。 |
| 06 | [用 error/warning 属性让危险调用连编译都过不去](006.用两个编译器属性，让危险调用连编译都过不去.png) | `__attribute__`((error/warning)) | 禁止危险调用、编译期安全 | 让危险函数调用在编译阶段直接报错或警告，从根源上阻止不安全代码进入生产环境。 |
| 07 | [用 malloc 属性给内存分配器贴标签，让编译器多省几条指令](./020.给内存分配器贴个标签，让编译器多省几条指令——%20malloc%20属性的妙用.png) | `__attribute__`((malloc)) | 自定义内存分配器优化 | 标记函数返回指针不与任何指针别名，帮助编译器生成更优的指令调度和寄存器分配。 |
| 08 | [用 always_inline 把关键路径融进代码里](008.用%20always_inline%20把关键路径"融"进代码里，让速度飞起来.png) | `__attribute__`((always_inline)) | 高频调用函数性能优化 | 强制编译器内联函数，消除压栈/出栈调用开销，在实时系统中显著提升性能。 |
| 09 | [C 语言柔性数组：为什么协议栈喜欢把 data[] 放在结构体最后](009.C%20语言柔性数组是什么？为什么网络协议栈喜欢把%20data%20放在结构体最后.png) | C语言柔性数组 | 网络协议栈、变长数据包 | C99标准特性，结构体末尾定义 `data[]`，在协议栈中管理变长数据包，节省内存访问高效。 |
| 10 | [用 constructor 让硬件在 main() 之前自动备妥](010.让硬件在%20main()%20之前自动备妥——用%20constructor%20属性实现模块自初始化.png) | `__attribute__`((constructor)) | 模块自初始化、驱动注册 | 函数在 main() 之前自动执行，适合硬件模块自初始化和驱动注册，自动备妥硬件环境。 |
| 11 | [用 warn_unused_result 让每个返回值都被签收](011.用%20warn_unused_result%20让每个返回值都被"签收"——编译器帮你堵住遗漏的错误检查.png) | `__attribute__`((warn_unused_result)) | 错误处理保障、健壮性提升 | 强制调用者检查返回值，忽略时编译器警告，防止漏掉错误码检查。 |
| 12 | [malloc 申请的内存，free 怎么知道要释放多少](012.malloc申请的内存，free是怎么知道要释放多少内存的？.png) | malloc/free 内部实现 | 理解动态内存分配原理 | free 通过读取 malloc 分配时在内存头部存储的元数据得知释放大小，无需传递长度参数。 |
| 13 | [为什么 int **p 不能指向 int a[3][4]](013.为什么%20int%20p%20不能指向%20int%20a%203%204%20？问题藏在"一整行"里.png) | 二维数组与指针类型系统 | 理解C数组与指针深层原理 | 二维数组退化为 `int (*)[4]` 而非 `int**`，两者内存布局完全不同，解释类型不兼容的根因。 |
| 14 | [用 noreturn 告诉编译器此路不通，让优化器自动清理冗余代码](014.用%20noreturn%20告诉编译器"此路不通"，让优化器自动清理冗余代码.png) | `__attribute__`((noreturn)) | 无限循环、异常处理函数 | 标记不返回的函数，帮助编译器清理死代码、优化寄存器分配，消除对返回路径的冗余处理。 |
| 15 | [用 used 保住那些编译器以为没用的关键符号](015.用%20__attribute__((used))%20保住那些编译器以为"没用"的关键符号.png) | `__attribute__`((used)) | 中断向量表、自初始化、调试符号 | 强制保留符号防止被优化掉，适合中断向量表、自初始化函数等看似无用但必须存在的符号。 |
| 16 | [用 naked 剥掉函数外套，写出最纯粹的中断响应](016.用%20__attribute__((naked))%20剥掉函数的"外套"，写出最纯粹的中断响应.png) | `__attribute__`((naked)) | 中断服务函数、底层硬件操作 | 编译器不生成序言/尾声，开发者用内联汇编完全控制栈帧，适合精确控制寄存器状态的中断处理。 |
| 17 | [5人面试0人答对：nohup 和 & 的区别](017.5人面试，0人答对nohup和%20&.png) | nohup 与 & 后台进程 | Linux后台进程管理 | & 将进程转为后台但不忽略SIGHUP；nohup 忽略SIGHUP使进程在终端关闭后继续运行。最佳实践：nohup command &。 |
| 18 | [嵌入式 C 里的 container_of：一个反向寻址的小把戏](018.嵌入式%20C%20里的%20container_of：一个反向寻址的小把戏.png) | container_of 宏 | Linux内核驱动、嵌入式反向寻址 | 通过成员偏移量从结构体成员指针反算结构体首地址，广泛用于Linux内核驱动模型中。 |
| 19 | [Linux 基础：软硬链接的使用场景](019.Linux%20基础：软硬链接的使用场景.png) | Linux软链接与硬链接 | 文件管理、备份、配置管理 | 硬链接共享inode不能跨分区；软链接是路径快捷方式可跨分区。从inode角度讲解本质区别和使用场景。 |
| 20 | [为什么编译通过、逻辑全对，代码还是跑飞了？](021.为什么编译通过、逻辑全对，代码还是跑飞了？.png) | 编译器优化、volatile | 嵌入式调试、优化问题排查 | 编译器优化导致代码执行顺序与源码不一致，volatile 关键字防止优化器"重排"关键操作。 |
| 21 | [为什么0x08000000要映射到0x00000000？](022.为什么0x08000000要映射到0x00000000？不是地址变换，是给CPU交一份"它认的作业".png) | 地址映射、CPU启动 | 嵌入式启动原理、链接脚本 | 0x08000000→0x00000000 的映射是给CPU一份"它认的作业"，而非简单的地址变换，解释取址与重映射机制。 |
| 22 | [用 do{...}while(0) 包装宏，让语法绝对安全](023.用%20do{...}while(0)%20包装宏，让语法绝对安全.png) | do-while(0)宏封装 | 宏定义安全编程 | 用 do{...}while(0) 包装多语句宏，解决宏展开后的语法歧义，让宏像函数一样安全使用。 |
| 23 | [用 __builtin_constant_p 实现编译期与运行时双路径优化](024.用%20__builtin_constant_p%20实现编译期与运行时双路径优化.png) | `__builtin_constant_p` | 编译期优化、运行时双路径 | 编译期判断参数是否为常量，自动选择常量折叠优化路径或运行时路径，提升性能。 |
| 24 | [用 C11 _Generic 写出"类型重载"宏](025.用%20C11%20_Generic%20写出"类型重载"宏，让代码自动适配.png) | C11 _Generic 泛型 | 类型重载、泛型编程 | 利用 C11 _Generic 关键字实现函数重载效果，让宏根据参数类型自动选择对应实现。 |
| 25 | [两个符号 # 和 ##，让编译器帮你拼出寄存器名和变量名](026.两个符号%20%23%20和%20%23%23，让编译器帮你拼出寄存器名和变量名.png) | # 和 ## 预处理运算符 | 寄存器定义、代码生成 | # 将宏参数字符串化，## 连接宏参数生成标识符，实现寄存器名和变量名的编译期拼接。 |
| 26 | [把 sizeof 和 static_assert 变成缓冲区容量安检员](027.把%20sizeof%20和%20static_assert%20变成缓冲区容量安检员.png) | sizeof + static_assert | 缓冲区安全、编译期检查 | 利用 sizeof 计算缓冲区大小，配合 static_assert 在编译期验证容量，防止缓冲区溢出。 |
| 27 | [用 #pragma message 在编译日志里写下永不丢失的 TODO](028.让编译器替你喊"记得改这里！"——用%20%23pragma%20message%20在编译日志里写下永不丢失的%20TODO.png) | #pragma message | 编译期提醒、TODO管理 | 在编译日志中输出自定义消息，用于遗留提醒、版本标记和编译期提示，永不丢失。 |
| 28 | [用两个编译器属性，让危险调用连编译都过不去](029.用两个编译器属性，让危险调用连编译都过不去.png) | `__attribute__`((error/warning)) | 禁止危险函数调用 | 标记危险函数为编译错误或警告，从根源上阻止不安全代码进入生产环境。 |
| 29 | [用 #pragma GCC poison 把危险标识符变成毒药](030.用%20%23pragma%20GCC%20poison%20把危险标识符变成毒药，谁碰谁编译失败.png) | #pragma GCC poison | 禁用危险标识符 | 将危险标识符"毒化"，任何使用它的代码都会编译失败，彻底禁用不安全的函数/宏。 |
| 30 | [用 __attribute__((weak)) 写出"可覆盖"的函数](031.用%20%60__attribute__((weak))%60%20写出"可覆盖"的函数，让框架优雅地留出后门.png) | `__attribute__`((weak)) | 弱符号、框架默认实现 | 定义弱符号函数提供默认实现，用户可通过同名强符号覆盖，实现框架的扩展点。 |
| 31 | [让硬件在 main() 之前自动备妥——用 constructor 属性](032.让硬件在%20main()%20之前自动备妥——用%20constructor%20属性实现模块自初始化.png) | `__attribute__`((constructor)) | 模块自初始化 | 函数在 main() 之前自动执行，适合硬件模块自初始化和驱动注册，自动备妥硬件环境。 |
| 32 | [用 __attribute__((cleanup)) 优雅地自动释放资源](033.用%20__attribute__((cleanup))%20在%20C%20语言里优雅地自动释放资源.png) | `__attribute__`((cleanup)) | RAII风格C代码 | 变量离开作用域时自动调用清理函数，优雅释放锁、内存、文件句柄等资源。 |
| 33 | [用 __attribute__((naked)) 剥掉函数的"外套"](034.用%20__attribute__((naked))%20剥掉函数的"外套"，写出最纯粹的中断响应.png) | `__attribute__`((naked)) | 中断服务函数 | 编译器不生成序言/尾声，开发者用内联汇编完全控制栈帧，适合精确控制寄存器状态的中断处理。 |
| 34 | [用 noinline 驯服优化，守护调试与栈帧](035.故意不让编译器内联——用%20noinline%20驯服优化，守护调试与栈帧.png) | `__attribute__`((noinline)) | 调试优化、栈帧保护 | 禁止编译器内联指定函数，保持调用栈完整性，便于调试和性能分析。 |
| 35 | [用 always_inline 把关键路径"融"进代码里](036.用%20always_inline%20把关键路径"融"进代码里，让速度飞起来.png) | `__attribute__`((always_inline)) | 高频调用函数优化 | 强制编译器内联函数，消除压栈/出栈调用开销，在实时系统中显著提升性能。 |
| 36 | [用 noreturn 告诉编译器"此路不通"](037.用%20noreturn%20告诉编译器"此路不通"，让优化器自动清理冗余代码.png) | `__attribute__`((noreturn)) | 无限循环优化 | 标记不返回的函数，帮助编译器清理死代码、优化寄存器分配，消除对返回路径的冗余处理。 |
| 37 | [两个心脏不能同时跳动——ROM 库为何必须剪掉向量表与 main](038.两个心脏不能同时跳动——ROM%20库为何必须剪掉向量表与%20main.png) | ROM库裁剪、向量表 | 链接脚本、库移植 | 解释ROM库中为何必须剪掉中断向量表和 main 函数，避免多个"心脏"导致启动冲突。 |
| 38 | [用 __builtin_unreachable 和 assume 让编译器优化出"不可能"的速度](039.用%20__builtin_unreachable%20和%20assume%20让编译器为你优化出"不可能"的速度.png) | `__builtin_unreachable` | 极致性能优化 | 告诉编译器某段代码不可达，帮助优化器消除冗余分支判断，生成更紧凑的指令序列。 |
| 39 | [不改一行源码，用 --wrap 给库函数装上监控](040.不改一行源码，用%20--wrap%20给库函数装上监控.png) | --wrap 链接器选项 | 库函数监控、打桩测试 | 不改源码劫持库函数调用，通过 `__wrap_xxx` 和 `__real_xxx` 机制为函数装上监控层。 |
| 40 | [用 .init_array 和 .fini_array 让模块在 main 前后自动"苏醒"和"沉睡"](041.用%20.init_array%20和%20.fini_array%20让模块在%20main%20前后自动"苏醒"和"沉睡".png) | .init_array /.fini_array | 模块初始化/清理 | 利用链接器段的 .init_array 和 .fini_array 实现模块在 main 之前自动初始化、在 exit 时自动清理。 |
| 41 | [用 -ffunction-sections 和 --gc-sections 给固件"剪枝"](042.用%20-ffunction-sections%20和%20--gc-sections%20给固件"剪枝"，把死代码统统踢出去.png) | -ffunction-sections / --gc-sections | 固件大小优化 | 每个函数独立成段，链接时自动剔除未使用的函数段，有效减小固件体积。 |
| 42 | [用 objcopy 把版本号、校验码甚至文件系统"烙"进固件里](043.用%20objcopy%20把版本号、校验码甚至文件系统"烙"进固件里.png) | objcopy 二进制嵌入 | 固件信息嵌入 | 用 objcopy 将版本号、校验码、文件系统等数据直接链接进固件，实现运行时读取。 |
| 43 | [X-Macro——一个宏表，同时生成枚举、字符串和查找函数](044.X‑Macro——一个宏表，同时生成枚举、字符串和查找函数.png) | X-Macro 宏表 | 枚举/字符串同步生成 | 用 X-Macro 技法维护一个宏表，自动生成枚举常量、字符串数组和查找函数，消除不一致。 |
| 44 | [地址映射原理：CPU 如何把地址翻译成寄存器访问](045.地址映射原理：CPU%20如何把地址翻译成寄存器访问.png) | 地址映射、MMU | 嵌入式底层原理 | CPU 通过 MMU 或内存映射将地址翻译成寄存器访问，解释地址总线与外围设备通信的底层原理。 |

---

## 分类导航

### GCC 编译器属性系列
| 编号 | 文章 | 属性 |
|:---:|:---|:---|
| 01 | section 属性把代码搬出 Flash | `__attribute__`((section)) |
| 03 | alias 属性给函数做分身 | `__attribute__`((alias)) |
| 04 | cleanup 属性自动释放资源 | `__attribute__`((cleanup)) |
| 05 | weak 属性写出可覆盖函数 | `__attribute__`((weak)) |
| 06 | error/warning 属性拦截危险调用 | `__attribute__`((error/warning)) |
| 07 | malloc 属性优化分配器 | `__attribute__`((malloc)) |
| 08 | always_inline 属性强制内联 | `__attribute__`((always_inline)) |
| 10 | constructor 属性实现自初始化 | `__attribute__`((constructor)) |
| 11 | warn_unused_result 强制检查返回值 | `__attribute__`((warn_unused_result)) |
| 14 | noreturn 属性优化不返回函数 | `__attribute__`((noreturn)) |
| 15 | used 属性保住关键符号 | `__attribute__`((used)) |
| 16 | naked 属性写纯粹的中断响应 | `__attribute__`((naked)) |

### C 语言底层机制
| 编号 | 文章 | 主题 |
|:---:|:---|:---|
| 09 | C语言柔性数组 | 变长结构体设计 |
| 12 | malloc/free 内存管理 | 动态内存分配实现原理 |
| 13 | 二维数组与指针 | 类型系统与内存布局 |
| 18 | container_of 宏 | 反向寻址技巧 |

### 链接器与开发工具
| 编号 | 文章 | 主题 |
|:---:|:---|:---|
| 02 | --wrap 给库函数装上监控 | 链接器函数劫持 |
| 17 | nohup 与 & 后台运行 | Linux 进程管理 |
| 19 | Linux 软硬链接 | 文件系统管理 |

---

## 原文链接

| 编号 | 原文 |
|:---:|:---|
| 01 | [用 section 属性把代码搬出 Flash，让关键函数在 RAM 里飞起来](https://mp.weixin.qq.com/s/yR5PG9G-zGH6Aw6AnjGi_w) |
| 02 | [不改一行源码，用 --wrap 给库函数装上监控](https://mp.weixin.qq.com/s/jsqhz_48Tz6t80CX9__3gg) |
| 03 | [用 alias 给函数做分身，让旧接口悄悄变成新实现](https://mp.weixin.qq.com/s/uFG-ggc5h5PnrQeFaIEMYQ) |
| 04 | [用 cleanup 在 C 语言里优雅地自动释放资源](https://mp.weixin.qq.com/s/s7BojfES5wXudtWShTiENg) |
| 05 | [用 weak 写出可覆盖的函数，让框架优雅地留出后门](https://mp.weixin.qq.com/s/bVN-aOjQTQwl-y7yrcICXA) |
| 06 | [用 error/warning 属性让危险调用连编译都过不去](https://mp.weixin.qq.com/s/yFqqtKHlUDoJtdcIyXVstw) |
| 07 | [用 malloc 属性给内存分配器贴标签，让编译器多省几条指令](https://mp.weixin.qq.com/s/SMWEAWugffKxn9WlBzOeSg) |
| 08 | [用 always_inline 把关键路径融进代码里](https://mp.weixin.qq.com/s/bvuifaWLda_OgEXpeEMrWQ) |
| 09 | [C 语言柔性数组：为什么协议栈喜欢把 data[] 放在结构体最后](https://mp.weixin.qq.com/s/I8zbMGVimUWo0-eNZYYIdA) |
| 10 | [用 constructor 让硬件在 main() 之前自动备妥](https://mp.weixin.qq.com/s/prrD607SjpZRfCycNEEZ_A) |
| 11 | [用 warn_unused_result 让每个返回值都被签收](https://mp.weixin.qq.com/s/VfmD9eM9Ng_l5OfCKlQgaA) |
| 12 | [malloc 申请的内存，free 怎么知道要释放多少](https://mp.weixin.qq.com/s/z0OmYayoEecP2vTN_-09XA) |
| 13 | [为什么 int **p 不能指向 int a[3][4]](https://mp.weixin.qq.com/s/ZUdAWuSD8AMh_ZBTeBxUHA) |
| 14 | [用 noreturn 告诉编译器此路不通，让优化器自动清理冗余代码](https://mp.weixin.qq.com/s/m4-BSbxstJ4wXjHTKXoaug) |
| 15 | [用 used 保住那些编译器以为没用的关键符号](https://mp.weixin.qq.com/s/OQz32wJcDHkKp8yc8nYKEA) |
| 16 | [用 naked 剥掉函数外套，写出最纯粹的中断响应](https://mp.weixin.qq.com/s/Pce4aRorVGg33ngAChBUYw) |
| 17 | [5人面试0人答对：nohup 和 & 的区别](https://mp.weixin.qq.com/s/vv4jnbwScNnb3zwSt64rJg) |
| 18 | [嵌入式 C 里的 container_of：一个反向寻址的小把戏](https://mp.weixin.qq.com/s/M4xIhP_6MeQ6kczvq8wajA) |
| 19 | [Linux 基础：软硬链接的使用场景](https://mp.weixin.qq.com/s/fVpn0VZpep6IDd0GwFYBCA) |