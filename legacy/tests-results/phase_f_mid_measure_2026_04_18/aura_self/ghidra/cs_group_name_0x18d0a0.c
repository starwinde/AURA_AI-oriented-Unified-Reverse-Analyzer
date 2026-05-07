
undefined8 cs_group_name(long param_1)

{
  undefined8 uVar1;
  
  if ((param_1 != 0) && (*(code **)(param_1 + 0x38) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0018d0b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x38))();
    return uVar1;
  }
  return 0;
}

