
void SStream_concat(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                   undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  undefined1 *local_120;
  undefined1 *puStack_118;
  undefined8 *puStack_110;
  undefined8 uStack_108;
  undefined8 local_30;
  undefined8 uStack_28;
  undefined8 local_20;
  undefined8 uStack_18;
  undefined8 local_10;
  undefined8 uStack_8;
  
  puStack_110 = &local_30;
  lVar3 = *(long *)PTR___stack_chk_guard_005ffe88;
  uStack_108 = 0xffffff80ffffffd0;
  local_120 = (undefined1 *)register0x00000008;
  puStack_118 = (undefined1 *)register0x00000008;
  local_30 = param_3;
  uStack_28 = param_4;
  local_20 = param_5;
  uStack_18 = param_6;
  local_10 = param_7;
  uStack_8 = param_8;
  iVar2 = (**(code **)PTR_cs_vsnprintf_005ffed8)
                    (param_1 + *(int *)(param_1 + 0x200),
                     0x200 - (long)(*(int *)(param_1 + 0x200) + 1),param_2,&local_120);
  puVar1 = PTR___stack_chk_guard_005ffe88;
  *(int *)(param_1 + 0x200) = *(int *)(param_1 + 0x200) + iVar2;
  lVar3 = lVar3 - *(long *)puVar1;
  if (lVar3 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(lVar3,puVar1,0);
}

