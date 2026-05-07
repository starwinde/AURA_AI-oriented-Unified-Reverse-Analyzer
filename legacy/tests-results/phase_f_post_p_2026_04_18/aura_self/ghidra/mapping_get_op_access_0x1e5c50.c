
byte mapping_get_op_access(long param_1,ulong param_2,long param_3)

{
  byte bVar1;
  ulong uVar2;
  
  bVar1 = *(byte *)(param_3 + (ulong)*(uint *)(param_1 + 8) * 0xc0 +
                    ((param_2 & 0xffffffff) * 2 + (param_2 & 0xffffffff)) * 4 + 1);
  uVar2 = MCInst_opIsTied();
  if (((uVar2 & 1) == 0) &&
     (uVar2 = MCInst_opIsTying(param_1,param_2 & 0xffffffff), (uVar2 & 1) == 0)) {
    return bVar1;
  }
  return bVar1 | (bVar1 == 1) + 1U;
}

