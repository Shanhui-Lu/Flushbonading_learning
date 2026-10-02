# 项目名称：基于STM32/FreeRTOS的嵌入式数据采集与设备管理系统

## 硬件平台：嘉立创-天空星STM32F4O7VET6

## 9月14号当前进度

### 建立基础工程

点亮LED，建立基础工程

实现内容：

1. STM32CubeMX生成工程。
2. 实现直接写引脚电平和翻转引脚电平两种方式点亮LED灯。

### tag:1.0

### 下一步计划

移植FreeRTOS，创建第一个任务。

---


## 9月15日当前进度

### FreeRTOS移植与任务创建

完成基于STM32CubeMX的FreeRTOS工程搭建。

实现内容：

1. 移植FreeRTOS到STM32F407VET6平台；
2. 创建LED_Task任务，实现基于RTOS调度的LED闪烁；
3. 验证FreeRTOS任务调度功能正常运行。

### tag:1.1

## 下一步计划

1. 创建多个任务；
2. 使用消息队列实现任务间通信；
3. 集成传感器数据采集任务。

---


## 10月2日当前进度

### FreeRTOS消息队列与UART调试链路

完成内容：

1. 创建 SensorTask 和 ProcessTask；
2. 使用 FreeRTOS Message Queue 实现任务间数据传递；
3. 将队列数据由 uint32_t 升级为 SensorMsg 结构体；
4. SensorMsg 包含传感器 ID、数据值和时间戳；
5. 配置 USART1，并完成 printf 串口重定向；
6. 通过 SSCOM 实现 ProcessTask 数据实时输出；
7. 解决 Keil 标准库 printf 导致系统异常的问题，启用 Use MicroLIB 后运行正常；
8. LED 独立任务正常运行，用于验证 FreeRTOS 调度状态。

### tag:1.2

## 下一步计划

1. 接入 AHT20/BMP280 真实传感器；
2. 使用 I2C 完成温湿度/气压数据采集；
3. 接入 OLED 显示；
4. 将真实传感器数据通过消息队列发送给处理任务和显示任务。