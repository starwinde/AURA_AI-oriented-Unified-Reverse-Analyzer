
void FUN_0010a130(undefined1 *param_1,undefined8 param_2,undefined4 param_3)

{
  byte local_2039;
  long local_2038;
  undefined1 *local_2030;
  undefined1 auStack_2028 [1000];
  undefined8 local_1c40;
  long local_28;
  
  local_1c40 = 0;
  local_28 = *(long *)PTR___stack_chk_guard_0013ffd0;
  local_2030 = auStack_2028;
  FUN_00112c20(&local_2030,param_1,param_2,param_3,&local_2038,&local_2039);
  if (local_2030 != param_1 && auStack_2028 != local_2030) {
    free(local_2030);
  }
  if (local_28 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail((ulong)local_2039 + local_2038,PTR___stack_chk_guard_0013ffd0,local_2038,0,
                   local_28 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

