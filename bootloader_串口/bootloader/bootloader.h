#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__
#include "sys.h"

extern u16 LEN_APP;

void flash_clean(u16 LEN_APP);
void start_app(void);
void write_flash(u16 LEN_APP);
void boot_start(void);

#endif

