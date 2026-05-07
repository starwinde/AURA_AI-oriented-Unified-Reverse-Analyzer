
undefined8 AArch64_insn_name(undefined8 param_1,uint param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if (param_2 < 0x509) {
    uVar1 = *(undefined8 *)(insn_name_maps + (ulong)param_2 * 8);
  }
  return uVar1;
}

