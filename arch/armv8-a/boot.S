// To keep this in the first portion of the binary
.section ".text.boot"

.global _start

/*
 * Entry point for the kernel
 * x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
 * x1 -> 0
 * x2 -> 0
 * x3 -> 0
 * x4 -> 32 bit kernel entry point, _start location
 * Preserve these registers as argument for kernel_main
 */

_start:
	/* Check if processor ID is zero (executing on main core), else hang */
	mrs x1, mpidr_el1
	and x1, x1, #3
	cbz x1, 2f
	/* We are not on the main core, so hang in an infinite wait loop */
1:	wfe
	b 1b
2: 	/* Code executing only by main core (cpu id == 0) */

	/*
	 * With the latest firmware, only the primary core runs (core 0), and
	 * the secondary cores are awaiting in a spin loop.
	 */
	mov sp, #0x80000		// Setup the stack (64 bit).

	ldr x5, =__bss_start		// Clear out BSS.
	ldr w6, =__bss_size
3:	cbz w6, 4f
	str xzr, [x5], #8
	sub w6, w6, #1
	cbnz w6, 3b

4:	bl kernel_main			// Call kernel_main (C Code).
					// Should not return from here.

	b 1b				// For failsafe, halt this core too.
