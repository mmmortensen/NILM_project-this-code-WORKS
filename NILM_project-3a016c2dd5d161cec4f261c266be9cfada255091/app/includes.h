/***************************************************************************
 **
 **
 **    Master inlude file
 **
 **    Used with ARM IAR C/C++ Compiler
 **
 **    (c) Copyright IAR Systems 2007
 **
 **    $Revision: 28 $
 **
 ***************************************************************************/

#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <intrinsics.h>
#include <assert.h>
#include <nxp/iolpc2478.h>
#include <drv_glcd.h>

#include "arm_comm.h"
#include "board.h"

#include "usb_cnfg.h"
#include "usb_desc.h"
#include "usb_hw.h"
#include "usb_t9.h"
#include "usb_hooks.h"
#include "usb_dev_desc.h"
#include "usb_hooks.h"
#include "usb_buffer.h"

#include "cd_class.h"
#include "cdc_desc.h"
#include "cdc_cmd.h"

#include "uart.h"

#include "sys.h"
#include "sdram_64M_32bit_drv.h"
#include "drv_glcd.h"
#include "iar_logo.h"
#include "algo.h"
#include "main.h"

//GUI includes
#include "gui.h"
#include "cursor_arrow.h"
#include <lamp_on.h>
#include <lamp_off.h>
#include <button_back.h>
#include <button_devices.h>
#include <button_info.h>
#include <button_learn.h>
#include <button_monitor.h>
#include <button_server.h>
#include <button_settings.h>

#include "drv_touch_scr.h"



#endif  // __INCLUDES_H
