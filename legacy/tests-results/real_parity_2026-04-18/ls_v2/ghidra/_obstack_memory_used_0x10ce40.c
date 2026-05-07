
long _obstack_memory_used(long param_1)

{
  long lVar1;
  long *plVar2;
  
  lVar1 = 0;
  for (plVar2 = *(long **)(param_1 + 8); plVar2 != (long *)0x0; plVar2 = (long *)plVar2[1]) {
    lVar1 = lVar1 + (*plVar2 - (long)plVar2);
  }
  return lVar1;
}

