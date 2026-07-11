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