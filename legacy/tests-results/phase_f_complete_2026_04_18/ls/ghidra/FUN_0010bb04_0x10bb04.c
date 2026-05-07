
undefined8 FUN_0010bb04(long param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  
  pfVar1 = *(float **)(param_1 + 0x28);
  if (pfVar1 == (float *)&DAT_001184a0) {
    return 1;
  }
  fVar2 = pfVar1[2];
  if ((((0.1 < fVar2) && (fVar2 < 0.9)) && (1.1 < pfVar1[3])) && (0.0 <= *pfVar1)) {
    fVar3 = *pfVar1 + 0.1;
    if (((fVar3 < pfVar1[1]) && (pfVar1[1] <= 1.0)) && (fVar3 < fVar2)) {
      return 1;
    }
  }
  *(undefined **)(param_1 + 0x28) = &DAT_001184a0;
  return 0;
}

