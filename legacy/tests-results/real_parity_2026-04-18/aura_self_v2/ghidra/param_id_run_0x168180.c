
undefined8 param_id_run(long param_1,long param_2,long param_3)

{
  undefined8 uVar1;
  
  if ((param_2 == 0 || param_3 == 0) || param_1 == 0) {
    return 1;
  }
  uVar1 = param_id_run_part_0();
  return uVar1;
}

