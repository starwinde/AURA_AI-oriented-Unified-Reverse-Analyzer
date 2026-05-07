
undefined4
fd_ehframe_add_end_candidates
          (long param_1,long param_2,ulong param_3,ulong param_4,long param_5,undefined4 param_6)

{
  undefined4 uVar1;
  long lVar2;
  
  if (((param_5 != 0 && param_3 < param_4) && (param_1 != 0 && param_2 != 0)) &&
     (lVar2 = eh_frame_parse(), lVar2 != 0)) {
    uVar1 = fd_ehframe_add_end_candidates_core
                      (*(undefined8 *)(lVar2 + 0x10),*(undefined4 *)(lVar2 + 0x18),param_2,param_3,
                       param_4,param_5,param_6);
    eh_frame_info_destroy(lVar2);
    return uVar1;
  }
  return 0;
}

