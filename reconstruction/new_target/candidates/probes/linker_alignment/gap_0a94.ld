SECTIONS
{
  .text 0x080009f4 :
  {
    *(.text)
    *(.text.FUN_08000a98)
  }
  /DISCARD/ :
  {
    *(.ARM.exidx*)
    *(.ARM.extab*)
    *(.comment*)
    *(.note*)
    *(.debug*)
    *(.data*)
    *(.bss*)
    *(.rodata*)
  }
}
