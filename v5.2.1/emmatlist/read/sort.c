#include "sort.h"

int analyze_list(int limit, int offset,etnode* list)
{
  et_print_list(limit,offset,list);
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  size_t son;
  etnode nd;
  int offset;
  
  offset=0;
  son=sizeof(etnode);
  
  if(argc!=2)
    {
      printf("emmatlist_read list_input_data\n");
      exit(-1);
    }
  
 
  printf("Program reads an ordered list of EMMAT fragments created from a midas file.\n");
  
  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  while(fread(&nd,son,1,inp)==1)
    {
      offset++;
      analyze_list(1,offset,&nd);
    }
  
  
  fclose(inp);
}
