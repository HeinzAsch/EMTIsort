#include "emmaalist-format.h"


/*================================================================*/
int ea_print_list(int limit, int offset, eanode* list)
{
  int i;

  for(i=0;i<limit;i++)
    printf("Frag: %9d Ts[ns] %16llu TrN %4d Ts_up %8u Ts %8u TrigTs[ns] %16lld Trig %8d\n",i+offset,list[i].tsns,list[i].trignum,(unsigned int)list[i].tsup,(unsigned int)list[i].ts,list[i].trig_tsns,list[i].trig);
  
  return 0;
}
/*================================================================*/
int ea_store_list(int limit, eanode* list,FILE* out)
{
  int i;
  size_t son;
  son=sizeof(eanode);
  for(i=0;i<limit;i++)
    fwrite(&list[i],son,1,out);
  
  return 0;
}
