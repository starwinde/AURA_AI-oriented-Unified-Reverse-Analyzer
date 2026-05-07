
void FUN_0010ab50(undefined4 param_1,undefined8 param_2,ulong *param_3,uint param_4,uint param_5)

{
  int iVar1;
  uint local_128;
  undefined4 local_124;
  undefined4 local_118;
  ulong local_114;
  ushort local_10c;
  ulong local_108;
  ulong uStack_100;
  ulong local_f8;
  ulong local_e8;
  uint local_e0;
  ulong local_d8;
  uint local_d0;
  ulong local_c8;
  uint local_c0;
  ulong local_b8;
  uint local_b0;
  uint local_a8;
  uint uStack_a4;
  uint local_a0;
  uint uStack_9c;
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_0013ffd0;
  iVar1 = statx(param_1,param_2,param_4 | 0x800,param_5,&local_128);
  if (-1 < iVar1) {
    *param_3 = ((ulong)uStack_9c & 0xffffff00) << 0xc | (ulong)uStack_9c & 0xff |
               ((ulong)local_a0 & 0xfff) << 8 | ((ulong)local_a0 & 0xfffff000) << 0x20;
    param_3[1] = local_108;
    *(undefined4 *)((long)param_3 + 0x14) = local_118;
    param_3[3] = local_114;
    param_3[4] = ((ulong)uStack_a4 & 0xffffff00) << 0xc | (ulong)uStack_a4 & 0xff |
                 ((ulong)local_a8 & 0xfff) << 8 | ((ulong)local_a8 & 0xfffff000) << 0x20;
    param_3[6] = uStack_100;
    *(uint *)(param_3 + 2) = (uint)local_10c;
    *(undefined4 *)(param_3 + 7) = local_124;
    param_3[8] = local_f8;
    param_3[9] = local_e8;
    param_3[10] = (ulong)local_e0;
    param_3[0xb] = local_b8;
    param_3[0xc] = (ulong)local_b0;
    param_3[0xd] = local_c8;
    param_3[0xe] = (ulong)local_c0;
    if ((param_5 >> 0xb & 1) != 0) {
      if ((local_128 >> 0xb & 1) == 0) {
        param_3[0xc] = 0xffffffffffffffff;
        param_3[0xb] = 0xffffffffffffffff;
      }
      else {
        param_3[0xb] = local_d8;
        param_3[0xc] = (ulong)local_d0;
      }
    }
  }
  if (local_28 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(iVar1,PTR___stack_chk_guard_0013ffd0,0,
                   local_28 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

