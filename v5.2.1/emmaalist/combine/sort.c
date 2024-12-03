#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE** subrun;
  int    n;
  FILE* subrun_list;
  char name[132];
  FILE* input;
  int i,k;
  unsigned long long tsns;
  eanode* eanodes;
  size_t son;
  eanode  store;
  
  if(argc!=3)
    {
      printf("griflist_combine griflist_of_subrun_lists output_griflist_name\n");
      exit(-1);
    }

  printf("Program combines a list of fragments from lists sorted from GRIF3/GRIF4 midas files.\n");
  
  /* open the list of subrun midas files */
  if((subrun_list=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open the subrun midas file list %s\n",argv[1]);
      exit(-2);
    }
  son=sizeof(eanode);
  n=0;
  subrun=NULL;
  /* process input file list*/
  while(fscanf(subrun_list,"%s",name)!=EOF)
    if(( input=fopen(name,"r"))==NULL)
      {
	printf("\nI can't open input file %s\n",name);
	exit(-2);	  
      }
    else
      {
	
	if(n==0)
	  subrun=(FILE**)malloc(sizeof(FILE*));
	else	  
	  subrun=(FILE**)realloc((FILE**)subrun,(n+1)*sizeof(FILE*));
	
	subrun[n]=input;
	n++;
	printf("File %3d named %s opened for processing\n",n,name);	  

	
      }
  
  fclose(subrun_list);
  
    if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

    eanodes=(eanode*)malloc(n*son);

    //read the first event from each subrun file
    for(i=0;i<n;i++)
      if(feof(subrun[i])==0)
	{
	  if(fread(&store,son,1,subrun[i])==1)
	      memcpy(&eanodes[i],&store,son);
	  else
	    eanodes[i].tsns=-1;
	}

 
    while(1)
      {
	tsns=LLONG_MAX;//set to the number beyond the clock range
	k=-1;
	//find the file with the minimum tsns

	for(i=0;i<n;i++)
	  if(eanodes[i].tsns>=0)
	    if(eanodes[i].tsns<tsns)
	      {
		tsns=eanodes[i].tsns;
		k=i;
	      }
	if(k==-1) break;

	if(fwrite(&eanodes[k],son,1,out)!=1)
	  {
	    printf("Error in writing to the output file, exiting\n");
	    fclose(out);
	    exit(0);
	  }

	eanodes[k].tsns=-1;
	if(!feof(subrun[k]))
	  if(fread(&store,son,1,subrun[k])==1)
	    memcpy(&eanodes[k],&store,son);
      }
    
    for(i=0;i<n;i++)
      fclose(subrun[i]);
      
    fclose(out);
   

}
