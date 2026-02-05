// SPDX-License-Identifier: GPL-2.0+ 
/* 
 * Copyright (c) 2021-25 Axiado Corporation (or its affiliates). All rights reserved.
*/  
#include <config.h>          /* For your CFG_ macros */
#include <init.h>            /* For board_init and dram_init */
#include <asm/global_data.h> /* For gd and the DECLARE_GLOBAL_DATA_PTR */
#include <asm/io.h>          /* For readl/writel if you're touching registers */
#include <linux/types.h> 

DECLARE_GLOBAL_DATA_PTR;

int board_init(void) 
{  
	return 0; 
} 


/**
 * dram_init - Calculate the total capacity of all RAM
 */
int dram_init(void)
{
	/* Bank 1: 0x23000000 (560MB)
	   Bank 2: 0x80000000 (2GB)
	   Total:  0xA3000000 (~2.5GB) */
	gd->ram_size = 0xA3000000;
	return 0;
}

/**
 * dram_init_banksize - Map the physical locations of RAM banks
 */
int dram_init_banksize(void)
{
	/* Bank 0: The 32-bit accessible region */
	gd->bd->bi_dram[0].start = 0x3d000000;
	gd->bd->bi_dram[0].size  = 0x23000000;

	/* Bank 1: The high memory region (64-bit address) */
	gd->bd->bi_dram[1].start = 0x400000000ULL; // Note the ULL for 64-bit
	gd->bd->bi_dram[1].size  = 0x80000000;

	return 0;
}

#include <asm/armv8/mmu.h>

static struct mm_region ax3000_mem_map[] = {
	{
		.virt = 0x3d000000UL,    /* Bank 0 RAM */
		.phys = 0x3d000000UL,
		.size = 0x23000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	},
	{
		.virt = 0x400000000ULL,  /* Bank 1 RAM (64-bit) */
		.phys = 0x400000000ULL,
		.size = 0x80000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	},
	{
		.virt = 0x0UL,           /* IO/Registers region */
		.phys = 0x0UL,
		.size = 0x3d000000UL,    /* Map everything below RAM as device memory */
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	},
	{
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = ax3000_mem_map;

void reset_cpu(void)
{
	/* For now, just a loop. Real SoC reset logic goes here later. */
	while (1);
}

int print_cpuinfo(void)
{
	printf("CPU: Axiado AX3000\n");
	return 0;
}
