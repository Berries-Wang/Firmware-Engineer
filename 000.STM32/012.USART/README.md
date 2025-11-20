# USART<sup>Universal synchronous asynchronous receiver transmitter.通用同步异步收发传输器</sup>
> 还是得学会看文档!!!: [RM0008 Reference manual#Universal synchronous asynchronous receiver transmitter (USART)](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

---

## 具体电路
![999.IMGS/wechat_2025-11-19_225501_375.png](./999.IMGS/wechat_2025-11-19_225501_375.png)

## USART结构框图
![wechat_2025-11-19_225701_998.png](./999.IMGS/wechat_2025-11-19_225701_998.png)
> FROM:[RM0008 Reference manual](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

---

## 通信方式
Any USART bidirectional communication requires a minimum of two pins: Receive Data In (RX) and Transmit Data Out (TX).(任何USART双向通信至少需要两个引脚：接收数据输入（RX）和发送数据输出（TX）)

阅读:[27.3 USART functional description](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) + [第4章 串口通信U(S)ART.pdf](../../002.REF_DOCS/第4章%20串口通信U(S)ART.pdf),可以知晓USART级别工作原理

## 通信方式
结合图[具体电路](#具体电路) + 图[USART结构框图](#usart结构框图) 来分析USART通信方式

### 发送数据 <sup>参考:[27.3.2 Transmitter](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)</sup>
- 发送过程: 写入数据到 TDR(Transmit Data register) , 再通过串并转换电路，数据由TDR(Transmit Data register) 复制到'Transmit Shift register' , 再通过TX pin发送出去.
  + 所以，总体发送流程: 编程接口 -> TDR -> Transmit Shift register -> TX pin -> 接收方
  + 'TXE' 标识位，是 TDR 的标识位 , 若当前 TXE 为1，则说明数据已经移动到移位寄存器(Transmit Shift Register)中，那么就可以向TDR中写入下一轮要发送的数据了。

### 接收数据

### 异步通信方式

### 串口流控

### 数据帧<sup>参考:[27.3.1 USART character description](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)</sup>

起始位、数据位、校验位、停止位 




---

## 波特率
### 波特率产生原理<sup>在时钟信号的上升沿到来时，移位寄存器(Shift register )才会向右移动一位</sup>
由波特率来触发操作移位寄存器来发送/接收数据,所以调整时钟频率，就可以调整波特率

---

## 串并转换 是什么、原理

---

## 各个概念
### 码元 & 波特率
- 传输的每个bit位就称为码元
- 每秒传输码元的个数，就是波特率


### 数据帧


---

## 参考资料
- [STM32G0-Peripheral-USART-interface-USART.pdf](../../002.REF_DOCS/STM32G0-Peripheral-USART-interface-USART.pdf)
- [stm32l4_peripheral_usart.pdf](../../002.REF_DOCS/stm32l4_peripheral_usart.pdf)
- [第4章 串口通信U(S)ART.pdf](../../002.REF_DOCS/第4章%20串口通信U(S)ART.pdf)