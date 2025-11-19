# USART<sup>Universal synchronous asynchronous receiver transmitter.通用同步异步收发传输器</sup>
> 还是得学会看文档!!!: [RM0008 Reference manual#Universal synchronous asynchronous receiver transmitter (USART)](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

## 接线方式

---

## 具体电路
![999.IMGS/wechat_2025-11-19_225501_375.png](./999.IMGS/wechat_2025-11-19_225501_375.png)


## USART结构框图 <sup>FROM:[RM0008 Reference manual](../../002.REF_DOCS/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)</sup>
![wechat_2025-11-19_225701_998.png](./999.IMGS/wechat_2025-11-19_225701_998.png)


## 通信方式
## 同步通信方式

### 异步通信方式

### 串口流控

---

## 数据帧
起始位 数据位 校验位 停止位 

### 数据校验


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