
void X86_reg_access(long param_1,void *param_2,undefined1 *param_3,void *param_4,undefined1 *param_5
                   )

{
  long lVar1;
  byte bVar2;
  ulong uVar3;
  void *__src;
  int *piVar4;
  byte bVar5;
  ulong uVar6;
  ulong uVar7;
  
  __src = *(void **)(param_1 + 0xf0);
  uVar7 = (ulong)*(byte *)((long)__src + 0x28);
  uVar6 = (ulong)*(byte *)((long)__src + 0x52);
  memcpy(param_2,__src,uVar7 << 1);
  memcpy(param_4,(void *)(*(long *)(param_1 + 0xf0) + 0x2a),uVar6 << 1);
  bVar2 = *(byte *)((long)__src + 0xa0);
  if (bVar2 != 0) {
    piVar4 = (int *)((long)__src + 0xa8);
    bVar5 = 0;
    do {
      if (*piVar4 == 1) {
        bVar2 = *(byte *)((long)piVar4 + 0x21);
        if ((bVar2 & 1) != 0) {
          uVar3 = arr_exist(param_2,uVar7,piVar4[2]);
          if ((uVar3 & 1) == 0) {
            lVar1 = uVar7 * 2;
            bVar2 = *(byte *)((long)piVar4 + 0x21);
            uVar7 = (ulong)((int)uVar7 + 1U & 0xff);
            *(short *)((long)param_2 + lVar1) = (short)piVar4[2];
          }
          else {
            bVar2 = *(byte *)((long)piVar4 + 0x21);
          }
        }
        if (((bVar2 >> 1 & 1) == 0) ||
           (uVar3 = arr_exist(param_4,uVar6,piVar4[2]), (uVar3 & 1) != 0)) goto LAB_001e42f4;
        lVar1 = uVar6 * 2;
        uVar6 = (ulong)((int)uVar6 + 1U & 0xff);
        *(short *)((long)param_4 + lVar1) = (short)piVar4[2];
        bVar2 = *(byte *)((long)__src + 0xa0);
      }
      else if (*piVar4 == 3) {
        if (piVar4[2] != 0) {
          lVar1 = uVar7 * 2;
          uVar7 = (ulong)((int)uVar7 + 1U & 0xff);
          *(short *)((long)param_2 + lVar1) = (short)piVar4[2];
        }
        if ((piVar4[3] != 0) && (uVar3 = arr_exist(param_2,uVar7), (uVar3 & 1) == 0)) {
          lVar1 = uVar7 * 2;
          uVar7 = (ulong)((int)uVar7 + 1U & 0xff);
          *(short *)((long)param_2 + lVar1) = (short)piVar4[3];
        }
        if ((piVar4[4] != 0) && (uVar3 = arr_exist(param_2,uVar7), (uVar3 & 1) == 0)) {
          lVar1 = uVar7 * 2;
          uVar7 = (ulong)((int)uVar7 + 1U & 0xff);
          *(short *)((long)param_2 + lVar1) = (short)piVar4[4];
        }
LAB_001e42f4:
        bVar2 = *(byte *)((long)__src + 0xa0);
      }
      bVar5 = bVar5 + 1;
      piVar4 = piVar4 + 0xc;
    } while (bVar5 < bVar2);
  }
  *param_3 = (char)uVar7;
  *param_5 = (char)uVar6;
  return;
}

