
undefined1 * FUN_001bac8c(long param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  ushort uVar2;
  
  uVar2 = insn_find(insns,0xa7a,param_2,param_1 + 0x70);
  puVar1 = &insn_ops + ((ulong)uVar2 * 8 - (ulong)uVar2);
  if (uVar2 == 0) {
    puVar1 = (undefined1 *)0x0;
  }
  return puVar1;
}

