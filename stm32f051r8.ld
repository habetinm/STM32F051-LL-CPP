/* Entry point */
ENTRY(Reset_Handler)

/* Stack and heap sizes */
_Min_Heap_Size  = 0x100;
_Min_Stack_Size = 0x200;

/* Memory layout */
MEMORY
{
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 8K
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
}

/* Initial stack pointer */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Sections */
SECTIONS
{
    /* Interrupt vector table */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Program code */
    .text :
    {
        . = ALIGN(4);

        *(.text)
        *(.text*)

        *(.rodata)
        *(.rodata*)

        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /* Exception handling tables */
    .ARM.extab :
    {
        *(.ARM.extab*)
    } > FLASH

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    /* Pre-initialization array */
    .preinit_array :
    {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } > FLASH

    /* C++ constructors */
    .init_array :
    {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
    } > FLASH

    /* C++ destructors */
    .fini_array :
    {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } > FLASH

    /* Initialized data */
    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);

        _sdata = .;
        *(.data)
        *(.data*)

        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    /* Zero-initialized data */
    .bss :
    {
        . = ALIGN(4);

        _sbss = .;
        __bss_start__ = _sbss;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } > RAM

    /* Heap and stack reservation */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE(end = .);
        PROVIDE(_end = .);

        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;

        . = ALIGN(8);
    } > RAM

    /* ARM attributes */
    .ARM.attributes 0 :
    {
        *(.ARM.attributes)
    }
}
