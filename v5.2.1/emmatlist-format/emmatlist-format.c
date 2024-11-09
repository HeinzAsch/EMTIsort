#include "emmatlist-format.h"


/*================================================================*/
int et_print_list(int limit, int offset, etnode* list)
{
  int i;

  for(i=0;i<limit;i++)
    printf("Frag: %9d Ts[ns] %16llu TrN %4d Ts_up %8u Ts %8u TrigTs[ns] %16lld Trig %8d\n",i+offset,list[i].tsns,list[i].trignum,(unsigned int)list[i].tsup,(unsigned int)list[i].ts,list[i].trig_tsns,list[i].trig);
  
  return 0;
}
/*================================================================*/
int et_store_list(int limit, etnode* list,FILE* out)
{
  int i;
  size_t son;
  son=sizeof(etnode);
  for(i=0;i<limit;i++)
    fwrite(&list[i],son,1,out);
  
  return 0;
}
