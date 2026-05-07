
bool FUN_001ed104(long param_1)

{
  bool bVar1;
  long lVar2;
  
  if ((*(ulong *)(param_1 + 0x20) & 0x7fff8000000) == 0) {
    bVar1 = true;
  }
  else if (((*(byte *)(*(long *)(param_1 + 0x10) + 0xb) & 0x80) == 0) &&
          ((*(ulong *)(param_1 + 0x20) & 0x7e000000000) != 0)) {
    bVar1 = false;
  }
  else if ((*(byte *)(*(long *)(param_1 + 8) + 6) & 7) == 0) {
    lVar2 = *(long *)(param_1 + 0x10);
    if (((*(byte *)(lVar2 + 0xc) & 2) == 0) && ((*(ulong *)(param_1 + 0x20) & 0x8000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xc) & 4) == 0) && ((*(ulong *)(param_1 + 0x20) & 0x10000000) != 0)
            ) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xc) & 8) == 0) && ((*(ulong *)(param_1 + 0x20) & 0x20000000) != 0)
            ) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xc) & 0x10) == 0) &&
            ((*(ulong *)(param_1 + 0x20) & 0x40000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xc) & 0x20) == 0) &&
            ((*(ulong *)(param_1 + 0x20) & 0x80000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xc) & 0x40) == 0) &&
            ((*(ulong *)(param_1 + 0x20) & 0x100000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xc) & 0x80) == 0) &&
            ((*(ulong *)(param_1 + 0x20) & 0x200000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xd) & 4) == 0) &&
            ((*(ulong *)(param_1 + 0x20) & 0xc00000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xd) & 1) == 0) &&
            ((*(ulong *)(param_1 + 0x20) & 0x1000000000) != 0)) {
      bVar1 = false;
    }
    else if (((*(byte *)(lVar2 + 0xd) & 2) == 0) &&
            (((*(ulong *)(param_1 + 0x20) & 0x300000000) != 0 &&
             ((*(ulong *)(param_1 + 0x20) & 0x8000000) == 0)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  }
  else {
    bVar1 = (*(ulong *)(param_1 + 0x20) & 0x1ff8000000) == 0;
  }
  return bVar1;
}

