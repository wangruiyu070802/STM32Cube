# STM32Cube 项目集

个人 STM32 嵌入式开发项目仓库。基于 STM32CubeMX 生成，使用 Keil MDK-ARM (uVision5) 开发。

## 目录结构

```
├── 2026/
│   └── Project_index/    ← 当前项目（STM32F401xC / Nucleo-64）
│       ├── Core/          — 用户代码（main.c, gpio.c 等）
│       ├── Drivers/       — ST 官方 HAL + CMSIS 库
│       ├── MDK-ARM/       — Keil 项目文件（.uvprojx）
│       └── Project_index.ioc — CubeMX 配置文件
├── 2027/                  ← 以后的新项目放在这里
├── .gitignore
└── README.md
```

## 我的工作方式

每个新项目从上个项目的文件夹复制而来，再修改添加新内容：

1. 复制整个 `202X/XXX/` 文件夹
2. 改名为新项目名
3. 在 CubeMX 中打开 `.ioc` 文件修改配置
4. 重新生成代码并添加用户逻辑

## 当前项目

| 项目 | 年份 | MCU | 板子 |
|------|------|-----|------|
| Project_index | 2026 | STM32F401Cx | Nucleo-64 |

## 开发环境

- MCU: STM32F401xC (Cortex-M4F, 84MHz)
- IDE: Keil MDK-ARM v5 (uVision5)
- HAL: STM32F4xx HAL Driver (CubeMX 生成)
