# 嵌入式 Rust 开发环境完全指南

> 基于 B站视频：[【中文配音】嵌入式Rust开发环境完全指南](https://www.bilibili.com/video/BV14gfVBFEKo/)（BV14gfVBFEKo）
---

## 一、背景

### 传统嵌入式开发的痛点

十年前嵌入式开发只能依赖厂商提供的 C 工具链，存在以下问题：

- **厂商锁定**：Keil（ARM MDK）只能用于 ARM 芯片，IAR 价格昂贵，换了芯片厂就要换一套工具链和 IDE
- **C 语言内存安全问题**：悬垂指针、缓冲区溢出、未定义行为在运行时才暴露，调试困难
- **缺乏现代化工具**：没有包管理器，依赖手动移植；代码补全、静态分析体验远落后于 Web/后端开发生态

### 为什么 Rust 适合嵌入式？

| 特性 | 说明 |
|------|------|
| 零成本抽象 | `no_std` 环境下无运行时开销，与手写 C/汇编性能相当 |
| 内存安全 | 所有权和借用检查在编译时保证内存安全，无 GC |
| 跨平台 | 一套 Rust 工具链支持 ARM Cortex-M、RISC-V、Xtensa 等多种架构 |
| 现代化生态 | cargo 包管理、crates.io 生态、rust-analyzer IDE 支持、版本锁定 |
|  fearless concurrency | Send/Sync trait 在编译时保证并发安全 |

---

## 二、硬件平台

本教程选用的硬件是 **BBC micro:bit v2**。

### 开发板参数

| 参数 | 规格 |
|------|------|
| SoC | Nordic nRF52833 |
| CPU | ARM Cortex-M4 (带 FPU，单精度浮点) |
| 主频 | 64 MHz |
| RAM | 128 KB |
| Flash | 512 KB |
| 调试接口 | SWD (通过 USB 内置调试器) |
| 板载外设 | 5×5 LED 矩阵、2个可编程按钮、蓝牙 5.0、加速度计、磁力计、扬声器、麦克风 |

### 为什么选 micro:bit v2？

- USB 直连即用，板载 CMSIS-DAP 调试器，无需额外购买 J-Link/ST-Link
- Cortex-M4 架构，Rust 生态完善（nrf51、nrf52 系列有成熟的 PAC 和 HAL）
- 价格低廉，适合入门

> 其他 Cortex-M 开发板（STM32、GD32、nRF52 系列）流程完全一致，只需调整 `memory.x` 中的 Flash/RAM 参数和目标三元组。

---

## 三、环境搭建

### 3.1 开发环境总览

```
应用层：  固件代码 (Rust)
工具链：  rustc + cargo (通过 rustup 管理)
目标架构：thumbv7em-none-eabihf (ARM Cortex-M4F)
IDE：     VS Code + rust-analyzer
调试器：  probe-rs 或 OpenOCD + GDB
硬件：    BBC micro:bit v2 (板载 CMSIS-DAP)
```

### 3.2 安装 Rust 工具链

```bash
# 安装 rustup（Rust 工具链管理器）
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# 重新登录 shell 或手动加载环境
source "$HOME/.cargo/env"

# 验证安装
rustup --version      # rustup 版本
rustc --version       # Rust 编译器版本
cargo --version       # 包管理器版本
```

### 3.3 添加交叉编译目标

嵌入式开发需要在**开发机（x86_64）上编译，在目标芯片（ARM Cortex-M）上运行**，因此需要安装交叉编译目标：

```bash
# micro:bit v2 是 Cortex-M4 带 FPU
rustup target add thumbv7em-none-eabihf
```

**ARM Cortex-M 系列目标三元组对照表：**

| 目标三元组 | ARM 架构 | 典型芯片 |
|-----------|---------|---------|
| `thumbv6m-none-eabi` | Cortex-M0, M0+, M1 | STM32F0, nRF51, GD32F1x0 |
| `thumbv7m-none-eabi` | Cortex-M3 | STM32F1, STM32F2, GD32F3x0 |
| `thumbv7em-none-eabi` | Cortex-M4 (无 FPU) | 部分 STM32F4 |
| `thumbv7em-none-eabihf` | Cortex-M4 (有 FPU) | **nRF52833**, STM32F4xx, i.MX RT |
| `thumbv8m.base-none-eabi` | Cortex-M23 | 部分低功耗安全芯片 |
| `thumbv8m.main-none-eabi` | Cortex-M33, M55, M85 | STM32L5, STM32U5, nRF5340 |

> `eabihf` 中的 `hf` 表示**硬件浮点**（Hard Float），即使用 FPU 硬件单元执行浮点运算。如果选错（如用 `eabi` 而芯片有 FPU），编译器仍能工作但会软件模拟浮点，性能下降。

### 3.4 配置 VS Code 及扩展

#### 必装扩展

| 扩展 | 功能 |
|------|------|
| **rust-analyzer** | Rust 语言支持 — 代码补全、跳转定义、类型提示、内联错误、重构 |
| **Dependi** | Cargo.toml 依赖管理辅助（原 crates 扩展已废弃，官方推荐替换为此扩展） |

#### 选装扩展

| 扩展 | 功能 |
|------|------|
| **Cortex-Debug** | ARM Cortex-M 调试支持（断点、变量查看、外设寄存器） |
| **Even Better TOML** | Cargo.toml 语法高亮和校验 |
| **Error Lens** | 内联显示诊断错误信息 |

#### VS Code 设置 (.vscode/settings.json)

```json
{
    "rust-analyzer.cargo.target": "thumbv7em-none-eabihf",
    "rust-analyzer.checkOnSave.allTargets": false,
    "[rust]": {
        "editor.formatOnSave": true
    }
}
```

`checkOnSave.allTargets: false` 避免 rust-analyzer 同时检查宿主架构导致报错。

### 3.5 安装调试烧录工具

#### 方案一：probe-rs（推荐，视频中使用）

```bash
cargo install probe-rs-tools

# 验证安装
probe-rs list
```

probe-rs 是纯 Rust 实现的调试/烧录工具链，一套命令完成烧录、运行、调试，支持 CMSIS-DAP、J-Link、ST-Link 等多种调试器。

#### 方案二：OpenOCD + GDB（通用方案）

```bash
# Ubuntu/Debian
sudo apt update
sudo apt install openocd gdb-multiarch

# 验证安装
openocd --version
gdb-multiarch --version
```

---

## 四、项目代码

### 4.1 创建项目

```bash
cargo new --bin microbit-rust-demo
cd microbit-rust-demo
```

### 4.2 配置文件：Cargo.toml

```toml
[package]
name = "microbit-rust-demo"
version = "0.1.0"
edition = "2021"

[dependencies]
# Cortex-M 运行时：提供 Reset Handler、向量表、
# 中断入口、内存初始化等底层启动代码
cortex-m-rt = "0.7"

# semihosting：将调试输出重定向到主机控制台
# 调试阶段用于打印日志（无需串口线）
cortex-m-semihosting = "0.5"

# panic 处理：发生 panic 时进入死循环
# 替代方案：panic-itm / panic-semihosting（输出错误信息）
panic-halt = "0.2"
```

### 4.3 配置文件：.cargo/config.toml

```toml
[target.thumbv7em-none-eabihf]
# 传给链接器的参数：-T 表示使用指定的链接脚本
rustflags = ["-C", "link-arg=-Tmemory.x"]

# cargo run / cargo embed 时自动执行的烧录命令
runner = "probe-rs run --chip nRF52833 --speed 4000"

[build]
# 默认编译目标，无需每次指定 --target
target = "thumbv7em-none-eabihf"
```

### 4.4 链接脚本：memory.x

```ld
/* memory.x - 链接器脚本 */
/* 定义 nRF52833 的物理存储布局 */

MEMORY
{
  /* 说明：Flash 存放代码和只读数据，RAM 存放变量和栈 */
  FLASH : ORIGIN = 0x00000000, LENGTH = 512K
  RAM   : ORIGIN = 0x20000000, LENGTH = 128K
}

/* cortex-m-rt 会从这里读取栈顶地址 */
/* 栈放在 RAM 末尾（栈向下增长，避免与变量区冲突） */
_stack_start = ORIGIN(RAM) + LENGTH(RAM);
```

#### 各芯片常见 memory.x 参数

| 芯片系列 | Flash 起始 | Flash 大小 | RAM 起始 | RAM 大小 |
|---------|-----------|-----------|---------|---------|
| nRF52833 (micro:bit v2) | 0x00000000 | 512K | 0x20000000 | 128K |
| STM32F103C8 ("Blue Pill") | 0x08000000 | 64K | 0x20000000 | 20K |
| STM32F407VE | 0x08000000 | 512K | 0x20000000 | 128K |
| RP2040 (Raspberry Pi Pico) | 0x10000000 | 2M | 0x20000000 | 264K |

### 4.5 主程序：src/main.rs

```rust
//! 嵌入式 Rust 最小固件框架
//!
//! 这是一个 no_std 环境下的最小可运行程序

// #![no_std]
// 功能：告诉 Rust 编译器不使用标准库 std
// 原因：std 依赖操作系统（文件系统、堆内存管理、线程等），
//       嵌入式 bare-metal 环境下没有操作系统，只有裸硬件
// 替代：改用 core 库（提供基本类型、迭代器、panic 处理等语言级功能，
//       不依赖任何操作系统抽象）
#![no_std]

// #![no_main]
// 功能：告诉 Rust 编译器不使用默认的 main 入口函数
// 原因：默认的 main 函数签名是 fn main() -> ()，需要 Rust 运行时
//       初始化（堆、栈、全局构造器等），这在裸机环境下不适用
// 替代：使用 cortex-m_rt 提供的 #[entry] 宏来标记真正的入口函数，
//       该宏会生成符合 Cortex-M 规范的 Reset Handler 签名 fn() -> !
#![no_main]

use cortex_m_rt::entry;
use panic_halt as _;
// 说明：panic_halt 是 panic 处理策略
// 当程序发生 panic 时，进入无限循环（halt）
// 其他可选策略：
//   - panic-semihosting：通过调试器输出 panic 信息到主机
//   - panic-itm：通过 ITM 引脚输出 panic 信息

// #[entry] - 由 cortex-m-rt 提供的入口宏
// 功能：将函数标记为 Reset Handler（芯片上电后执行的第一段代码）
// 约束：只能标记一个函数，返回值必须是 !
// 作用：宏内部会生成向量表、初始化 .bss/.data 段、设置栈指针
#[entry]
fn main() -> ! {
    // 程序入口：芯片上电/复位后从这里开始执行
    // 此时已经完成：
    //   1. 栈指针 SP 已设置（从 memory.x 读取 _stack_start）
    //   2. .bss 段已清零（未初始化的全局变量）
    //   3. .data 段已从 Flash 拷贝到 RAM（已初始化的全局变量）

    loop {
        // 主循环：嵌入式程序通常永不返回
        // 后续可以在这里添加外设初始化、任务调度等
    }
}
```

### 4.6 构建脚本：build.rs

```rust
//! build.rs - Cargo 构建脚本
//!
//! 功能：在编译时将 memory.x 链接脚本复制到 cargo 的输出目录，
//!       确保链接器能找到它

use std::env;
use std::fs::File;
use std::io::Write;
use std::path::PathBuf;

fn main() {
    // 当 memory.x 文件发生变化时，自动触发重新编译
    println!("cargo:rerun-if-changed=memory.x");

    // 获取 cargo 的输出目录（OUT_DIR 环境变量）
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());

    // 将 memory.x 复制到输出目录，链接器会在这里查找
    File::create(out_dir.join("memory.x"))
        .unwrap()
        .write_all(include_bytes!("memory.x"))
        .unwrap();
}
```

### 4.7 编译项目

```bash
# 编译（自动使用 .cargo/config.toml 中的默认目标）
cargo build

# 指定目标编译（如果 config.toml 中未设置 [build] target）
cargo build --target thumbv7em-none-eabihf

# release 模式（开启优化，固件体积更小）
cargo build --release
```

编译产物位于 `target/thumbv7em-none-eabihf/debug/microbit-rust-demo`（ELF 格式）。

### 4.8 项目完整结构

```
microbit-rust-demo/
├── .cargo/
│   └── config.toml          # cargo 配置：目标、链接器参数、runner
├── .vscode/
│   ├── settings.json         # VS Code 设置：rust-analyzer 目标
│   └── launch.json           # （可选）调试配置
├── src/
│   └── main.rs               # 主程序入口（no_std + no_main）
├── build.rs                  # 构建脚本：复制 memory.x
├── Cargo.toml                # 项目元数据和依赖
├── memory.x                  # 链接脚本：Flash/RAM 布局
├── Embed.toml                # （可选）cargo embed 配置
└── rust-toolchain.toml       # （可选）锁定 Rust 版本和组件
```

---

## 五、代码调试

### 5.1 调试工具链选择

| 方案 | 安装方式 | 优点 | 缺点 |
|------|---------|------|------|
| **probe-rs** | `cargo install probe-rs-tools` | 纯 Rust，命令统一，无需额外配置 | 部分旧芯片支持不完善 |
| **OpenOCD + GDB** | `apt install openocd gdb-multiarch` | 通用，几乎支持所有芯片 | 需要手动启动服务器，配置繁琐 |

### 5.2 方式一：使用 cargo embed（推荐）

`cargo embed` 是 probe-rs 提供的集成烧录+调试命令，自动检测芯片和调试器。

```bash
# 烧录并运行
cargo embed

# 烧录并启动 RTT 日志（实时日志输出）
cargo embed --rtt

# 烧录 release 版本
cargo embed --release
```

#### Embed.toml 配置

```toml
[default.general]
# 芯片型号（probe-rs 会自动检测，但指定更可靠）
chip = "nRF52833"

[default.flashing]
# 烧录完成后是否复位芯片并运行
enabled = true

[default.rtt]
# 启用 RTT（Real-Time Transfer）日志输出
# 可以在终端实时查看芯片打印的日志
enabled = true

[default.reset]
# 烧录完成后硬件复位
enabled = true
```

### 5.3 方式二：使用 probe-rs 命令行

```bash
# 查看连接的调试器和芯片
probe-rs list

# 烧录并运行
probe-rs run --chip nRF52833 target/thumbv7em-none-eabihf/debug/microbit-rust-demo

# 调试模式（进入 GDB 会话）
probe-rs debug --chip nRF52833 target/thumbv7em-none-eabihf/debug/microbit-rust-demo
```

### 5.4 方式三：OpenOCD + GDB

```bash
# 终端1：启动 OpenOCD（连接到 micro:bit v2 的板载调试器）
openocd -f interface/cmsis-dap.cfg -f target/nrf52.cfg

# 终端2：启动 GDB 并连接 OpenOCD
gdb-multiarch target/thumbv7em-none-eabihf/debug/microbit-rust-demo

# 在 GDB 中执行：
(gdb) target remote localhost:3333      # 连接到 OpenOCD
(gdb) load                                # 烧录固件
(gdb) break main                          # 在 main 入口设断点
(gdb) continue                            # 运行到断点
(gdb) step                                # 单步执行
(gdb) info registers                      # 查看寄存器
(gdb) monitor reset init                  # 复位芯片
```

### 5.5 VS Code 图形化调试 (.vscode/launch.json)

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "cortex-debug",
            "request": "launch",
            "name": "Debug micro:bit v2 (probe-rs)",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/target/thumbv7em-none-eabihf/debug/microbit-rust-demo",
            "device": "nRF52833",
            "interface": "swd",
            "servertype": "probe-rs",
            "runToMain": true
        },
        {
            "type": "cortex-debug",
            "request": "launch",
            "name": "Debug micro:bit v2 (OpenOCD)",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/target/thumbv7em-none-eabihf/debug/microbit-rust-demo",
            "device": "nRF52833",
            "interface": "swd",
            "servertype": "openocd",
            "configFiles": [
                "interface/cmsis-dap.cfg",
                "target/nrf52.cfg"
            ],
            "runToMain": true
        }
    ]
}
```

### 5.6 调试技巧

#### 使用 semihosting 打印日志

在没有串口的裸机环境下，通过调试器向主机控制台输出日志：

```rust
// 在 Cargo.toml 中添加依赖
// cortex-m-semihosting = "0.5"

use cortex_m_semihosting::hprintln;

#[entry]
fn main() -> ! {
    hprintln!("Hello from micro:bit v2!").unwrap();
    loop {}
}
```

运行方式（必须通过调试器启动，直接运行无效）：
```bash
# 需要先启动 OpenOCD，然后通过 GDB/target remote 运行
probe-rs run --chip nRF52833 target/.../microbit-rust-demo
```

#### 使用 RTT 日志（更高效）

RTT (Real-Time Transfer) 比 semihosting 更快，不阻塞程序执行：

```rust
// 需要 rtt-target crate 和 Embed.toml 中 [default.rtt] enabled = true
use rtt_target::{rtt_init_print, rprintln};

#[entry]
fn main() -> ! {
    rtt_init_print!();
    rprintln!("Hello via RTT!");
    loop {}
}
```

#### 常用 GDB 调试命令

| 命令 | 缩写 | 功能 |
|------|------|------|
| `target remote :3333` | — | 连接 OpenOCD |
| `load` | — | 烧录固件到 Flash |
| `break main` | `b main` | 在 main 函数设断点 |
| `continue` | `c` | 继续运行到下一个断点 |
| `next` | `n` | 单步跳过（不进入函数） |
| `step` | `s` | 单步进入（进入函数内部） |
| `print var` | `p var` | 打印变量值 |
| `info registers` | `i r` | 查看所有寄存器 |
| `monitor reset` | — | 复位芯片 |

---

## 附录

### A. 视频中使用的所有组件一览

| 类别 | 组件 | 版本/参数 | 用途 |
|------|------|----------|------|
| **硬件** | BBC micro:bit v2 | nRF52833 | 目标开发板 |
| **SoC** | Nordic nRF52833 | Cortex-M4F @64MHz | 主控芯片 |
| **调试器** | 板载 CMSIS-DAP | 集成在 micro:bit v2 | 烧录和调试接口 |
| **操作系统** | 无 (bare-metal) | — | 裸机环境 |
| **工具链管理器** | rustup | 最新稳定版 | 管理 Rust 编译器/组件 |
| **Rust 编译器** | rustc | 通过 rustup 安装 | 代码编译 |
| **包管理器** | cargo | 通过 rustup 安装 | 依赖管理、项目构建 |
| **交叉编译目标** | thumbv7em-none-eabihf | 通过 rustup target add | ARM Cortex-M4F 目标 |
| **IDE** | VS Code | 最新稳定版 | 代码编辑 |
| **LSP** | rust-analyzer | VS Code 扩展 | 代码补全、分析 |
| **依赖管理** | Dependi | VS Code 扩展 | Cargo.toml 可视化 |
| **运行时** | cortex-m-rt | 0.7 | Reset Handler、向量表、入口宏 |
| **panic 处理** | panic-halt | 0.2 | panic 时死循环 |
| **日志输出** | cortex-m-semihosting | 0.5 | 通过调试器输出日志 |
| **烧录/调试** | probe-rs-tools | cargo install | 烧录、运行、调试 |
| **调试协议** | SWD (Serial Wire Debug) | 硬件协议 | 调试器与芯片通信 |

### B. 视频中未涉及但推荐的工具

| 工具 | 用途 | 安装方式 |
|------|------|---------|
| cargo-edit | 命令行管理依赖（add/rm/upgrade） | `cargo install cargo-edit` |
| cargo-generate | 根据模板生成项目 | `cargo install cargo-generate` |
| flip-link | 栈溢出保护链接器（避免静默栈溢出） | `cargo install flip-link` |

### C. 常见问题排查

**Q: `cargo build` 报错 `file not found for memory.x`？**

A: 检查项目中是否存在 `memory.x` 文件，以及 `.cargo/config.toml` 中是否配置了 `rustflags = ["-C", "link-arg=-Tmemory.x"]`。

**Q: rust-analyzer 报错 `can't find crate for core`？**

A: 确保 `.vscode/settings.json` 中设置了 `"rust-analyzer.cargo.target": "thumbv7em-none-eabihf"`，rust-analyzer 默认使用宿主架构找不到 `core` 库。

**Q: `probe-rs run` 报错 `could not find any debug probes`？**

A: 检查 USB 连接，运行 `probe-rs list` 查看是否识别到调试器。micro:bit v2 需要在 Windows 上安装驱动，Linux/Mac 即插即用。

**Q: 烧录后芯片无反应？**

A: 检查 `memory.x` 的 Flash/RAM 地址是否正确，以及 `#[entry]` 宏是否只标记了一个函数。