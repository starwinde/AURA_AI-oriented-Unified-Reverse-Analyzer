
int reader(UI *ui,UI_STRING *uis)

{
  long in_x2;
  
  if ((ulong)(in_x2 - *(long *)(ui + 0x10)) < *(ulong *)(ui + 8)) {
    *uis = *(UI_STRING *)(*(long *)ui + (in_x2 - *(long *)(ui + 0x10)));
    return 0;
  }
  return -1;
}

