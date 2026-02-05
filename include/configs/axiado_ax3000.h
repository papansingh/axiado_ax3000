#ifndef __CONFIG_AXIADO_AX3000_H
#define __CONFIG_AXIADO_AX3000_H

#include <config_distro_bootcmd.h>
/* * Assuming your SoC has 128KB of internal SRAM starting at 0x10000000.
 * CHECK YOUR DATASHEET for the actual 'Internal SRAM' or 'OCRAM' address!
 */
#define CFG_SYS_INIT_RAM_ADDR        0x10000000

#define CFG_SYS_INIT_RAM_SIZE        0x20000    /* 128 KB */
#define CFG_SYS_INIT_SP_ADDR \
    (CFG_SYS_INIT_RAM_ADDR + CFG_SYS_INIT_RAM_SIZE)
#endif
