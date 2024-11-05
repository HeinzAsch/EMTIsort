#include "sort.h"

int main(int argc, char *argv[])
{
  FILE* inp;
  size_t son;
  node nd;
  static gmap map;
  int found;
  son=sizeof(node);

  if(argc!=3)
    {
      printf("griflist_check_HPGe_CC_Seg_map griflist_input_data map\n");
      exit(-1);
    }
  
  found=0;
  printf("Program checks consistency of HPGe CC and Seg mapping\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  read_map(argv[2],&map);

  while(1)
    {
      if(feof(inp)!=0) break;
      if(fread(&nd,son,1,inp)!=1) break; //stop on incorrect reading
 
      if(CC_channel(&nd,&map)==1)
	if(Seg_channel(&nd,&map)==1)
	  {
	    printf("Error: overlap in CC/Seg mapping\n");
	    print_list(1,0,&nd);
	    found=1;
	    getc(stdin);
	  }
    }
  
  if(found==0)
    printf("\nNo HPGe CC/Seg overlaps identified in the map\n");
  
  fclose(inp);
}
