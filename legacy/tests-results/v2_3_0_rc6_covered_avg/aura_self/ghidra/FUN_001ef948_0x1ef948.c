
void FUN_001ef948(long param_1,byte *param_2,ulong *param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  
  if ((*param_2 & 0x3f) != 1) {
    iVar3 = FUN_001f2768(*(undefined4 *)(param_1 + 4));
    bVar2 = FUN_001e8850(*(undefined4 *)(param_1 + 4),iVar3);
    if (((iVar3 == 1) && (8 < *(uint *)(param_1 + 4))) && (*(uint *)(param_1 + 4) < 0xd)) {
      *param_3 = *param_3 | 4;
    }
    pbVar4 = (byte *)FUN_001f2f18(param_2);
    bVar1 = *pbVar4 & 0x3f;
    if (bVar1 == 6) {
      *(byte *)((long)param_3 + 0x13) = bVar2;
    }
    else {
      if (6 < bVar1) {
LAB_001efb2c:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xf8b,
                      "ZydisBuildRegisterOperand");
      }
      if (bVar1 == 5) {
        *(undefined1 *)((long)param_3 + 0x22) = 8;
        param_3[6] = (long)(int)((uint)bVar2 << 4);
      }
      else {
        if (5 < bVar1) goto LAB_001efb2c;
        if (bVar1 == 4) {
          *(byte *)((long)param_3 + 0x11) = bVar2;
        }
        else {
          if (4 < bVar1) goto LAB_001efb2c;
          if (bVar1 == 3) {
            *(byte *)(param_3 + 2) = (char)param_3[2] + (bVar2 & 7);
            *(byte *)((long)param_3 + 0x17) = bVar2;
          }
          else {
            if (3 < bVar1) goto LAB_001efb2c;
            if (bVar1 == 1) {
              *param_3 = *param_3 | 1;
              *(byte *)((long)param_3 + 0x16) = bVar2;
            }
            else {
              if (bVar1 != 2) goto LAB_001efb2c;
              *param_3 = *param_3 | 1;
              *(byte *)((long)param_3 + 0x17) = bVar2;
              if (iVar3 - 7U < 3) {
                *(undefined1 *)((long)param_3 + 0x1c) = 1;
              }
            }
          }
        }
      }
    }
  }
  return;
}

