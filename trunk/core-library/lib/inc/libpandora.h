/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 *  @file libmaple.h -> libpandora.h [ROBOTIS][CHANGE] Thanks to maple board
 *  @brief General include file for libmaple
 */

#ifndef _LIBPANDORA_H_
#define _LIBPANDORA_H_

#include "libpandora_types.h"
#include "stm32.h"
#include "util.h"
#include "delay.h"

/*
 * Where to put usercode, based on space reserved for bootloader.
 *
 * FIXME this has no business being here
 */
#define USER_ADDR_ROM 0x08005000
#define USER_ADDR_RAM 0x20000000 //#define USER_ADDR_RAM 0x20000C00 [ROBOTIS][CHANGE] for CM900
#define STACK_TOP     0x20000800
//[ROBOTS][START] add to support Pandora CM-900 board
#define NVIC_VectTab_RAM             ((u32)0x20000000)
#define NVIC_VectTab_FLASH           ((u32)0x08000000)
//[ROBOTS][END] add to support Pandora CM-900 board
#endif

