
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int posix_fadvise(int __fd,__off_t __offset,__off_t __len,int __advise)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_posix_fadvise_0011fec0)(__fd,__offset,__len,__advise);
  return iVar1;
}

