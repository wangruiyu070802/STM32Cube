# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

STM32CubeMX-generated firmware projects targeting **STM32F401xC** (Nucleo-64 board) using the **STM32F4 HAL** library. Each project under `2026/` is a CubeMX-generated template with only GPIO initialized for onboard LEDs (PA8-LD2, PA9-LD1).

## Projects

| Project | Description |
|---------|-------------|
| **Demo** | Main project template |
| **Demo-KEY_LED** | LED demo variant (KEY) |

## Build System & Toolchain

- **IDE/Toolchain**: Keil MDK-ARM (uVision5)
- **MCU**: STM32F401xC (startup file: `MDK-ARM/startup_stm32f401xc.s`)
- **HAL Config**: `Core/Inc/stm32f4xx_hal_conf.h` — only basic HAL modules enabled (GPIO, EXTI, DMA, RCC, FLASH, PWR, CORTEX)
- **CubeMX Config**: `<ProjectName>.ioc` — regenerate code from this file using STM32CubeMX

## Key Commands

```bash
# Open Demo project in Keil uVision
D:\Keil_v5\UV4\UV4.exe 2026/Demo/MDK-ARM/Demo.uvprojx

# Open Demo-KEY_LED project in Keil uVision
D:\Keil_v5\UV4\UV4.exe "2026/Demo-KEY_LED/MDK-ARM/Demo-KEY_LED.uvprojx"

# Regenerate code from CubeMX configuration (requires STM32CubeMX CLI)
# Open <ProjectName>.ioc file in STM32CubeMX GUI, then generate code
```

## Project Structure (per project)

```
2026/<ProjectName>/          # e.g. Demo or Demo-KEY_LED
├── Core/                    # User application code
│   ├── Inc/                 # Headers
│   │   ├── main.h           # Main header, pin defines (LD1=PA9, LD2=PA8)
│   │   ├── gpio.h           # GPIO initialization prototype
│   │   ├── stm32f4xx_it.h   # Interrupt handler declarations
│   │   └── stm32f4xx_hal_conf.h  # HAL module enable/disable
│   └── Src/                 # Source files
│       ├── main.c           # Entry point, system clock config (84MHz via HSE+PLL)
│       ├── gpio.c           # MX_GPIO_Init() — LED pins as push-pull outputs
│       ├── stm32f4xx_it.c   # Default interrupt handlers (HardFault, SysTick, etc.)
│       ├── stm32f4xx_hal_msp.c  # HAL MSP initialization (empty)
│       └── system_stm32f4xx.c   # System clock setup (CubeMX-managed)
├── Drivers/                 # HAL & CMSIS library code (do not edit manually)
│   ├── CMSIS/               # Cortex-M core headers and DSP library
│   └── STM32F4xx_HAL_Driver/  # STM32F4 HAL peripheral drivers
├── MDK-ARM/                 # Keil uVision project files
│   ├── <ProjectName>.uvprojx   # Project file (double-click to open)
│   └── startup_stm32f401xc.s   # Reset vector table, stack/heap init
└── <ProjectName>.ioc        # CubeMX hardware configuration file
```

## Architecture Notes

- **CubeMX Code Generation**: All CubeMX-generated files use `/* USER CODE BEGIN n */` / `/* USER CODE END n */` markers. User code must go inside these sections — code outside them is overwritten on regeneration.
- **Boot Flow**: `Reset_Handler` (startup asm) → `SystemInit` → `main()` → `HAL_Init()` → `SystemClock_Config()` → `MX_GPIO_Init()` → infinite loop.
- **System Clock**: 8MHz HSE (bypassed) → PLL (M=8, N=168, P=2) → SYSCLK = 84MHz. APB1 = 42MHz, APB2 = 84MHz.
- **No RTOS**: `USE_RTOS` is 0 in the HAL config.
- **Nucleo LEDs**: LD1 (green) on PA9, LD2 (blue) on PA8 — both driven low (GPIO_PIN_SET = initial HIGH, GPIO_MODE_OUTPUT_PP).

## Adding New Peripherals

1. Open `<ProjectName>.ioc` in STM32CubeMX to add/configure peripherals graphically
2. Regenerate code — new .c/.h files appear in Core/ with `MX_<Periph>_Init()` functions
3. Add user logic inside the generated USER CODE sections
4. Or add peripherals manually: enable the HAL module in `stm32f4xx_hal_conf.h`, write init code, call from `main()`

## Pin Mapping (STM32F401Cx on Nucleo-64)

| Pin   | Function | Label  |
|-------|----------|--------|
| PA8   | GPIO Out | LD2    |
| PA9   | GPIO Out | LD1    |
