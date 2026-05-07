
void * clone_leaf(void *param_1)

{
  void *__dest;
  
  if (param_1 != (void *)0x0) {
    __dest = calloc(1,0x130);
    if (__dest != (void *)0x0) {
      memcpy(__dest,param_1,0x130);
    }
    return __dest;
  }
  return (void *)0x0;
}

