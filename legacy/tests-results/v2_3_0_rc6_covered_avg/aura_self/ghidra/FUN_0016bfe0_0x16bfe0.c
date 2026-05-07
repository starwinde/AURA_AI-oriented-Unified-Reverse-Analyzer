
void FUN_0016bfe0(long *param_1,long param_2)

{
  uint uVar1;
  char *pcVar2;
  uint uVar3;
  long lVar4;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"=== Embedded Media Detection (%u found) ===\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    uVar3 = 0;
    do {
      uVar3 = uVar3 + 1;
      uVar1 = *(uint *)(*param_1 + lVar4 + 0x10);
      if (uVar1 == 6) {
        pcVar2 = "ZIP";
      }
      else {
        pcVar2 = "Unknown";
        if (uVar1 < 7) {
          if (uVar1 == 3) {
            pcVar2 = "GIF";
          }
          else if (uVar1 < 4) {
            if (uVar1 == 1) {
              pcVar2 = "JPEG";
            }
            else if (uVar1 == 2) {
              pcVar2 = "PNG";
            }
          }
          else {
            pcVar2 = "BMP";
            if (uVar1 != 4) {
              pcVar2 = "PDF";
            }
          }
        }
        else if (uVar1 == 9) {
          pcVar2 = "RIFF";
        }
        else if (uVar1 < 10) {
          pcVar2 = "ELF";
          if (uVar1 != 7) {
            pcVar2 = "PE";
          }
        }
        else if (uVar1 == 10) {
          pcVar2 = "OGG";
        }
      }
      __fprintf_chk(param_2,2,"  [%u] %s (type: %s)\n",uVar3,*param_1 + lVar4 + 0x14,pcVar2);
      lVar4 = lVar4 + 0x98;
    } while (uVar3 < *(uint *)(param_1 + 1));
  }
  return;
}

