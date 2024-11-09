#include "sort.h"
#define MAXWIN 10000//10 us window to check
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,ref;
  int  trig;
  unsigned long pos;
  unsigned long long dt;
  unsigned long long tsmin;
  int find_new_ref,found;
  
  son=sizeof(node);
  memset(&ref,0,son);

  if(argc!=2)
    {
      printf("griflist_final_trigger fragment_list\n");
      exit(-1);
    }
  
  printf("Program assignes final trigger numbers based on trig_ts[ns] in a fragment list\n");
    
  if((fl=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
 
  //in the first pass assigned ordered trigger numbers to the first event with trig_tsns in a chronological order
    
    while(1)
      {
	if(fread(&ref,son,1,fl)!=1) break; //stop on incorrect reading
	if(ref.trig_tsns>0) break;
      }
    trig=0;
    pos=ftell(fl);//save current position
  
    while(1)
      {
	if(feof(fl)) break;
   

	tsmin=ref.trig_tsns;

	//     	printf("==> ");print_list(1,0,&ref);getc(stdin);

	while(1)//find the lowest trig_tsns in the window
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading

	    if(curr.trig==-1)
	      if(curr.trig_tsns>0)
		if(curr.trig_tsns<tsmin)
		  {
		    tsmin=curr.trig_tsns;
		    //		    printf("--> ");print_list(1,0,&curr);getc(stdin);
		  }
	    
	    dt=curr.tsns-ref.tsns;
	    if(dt>MAXWIN) //out of coincidence window
	      break;
	  }
	//	printf("tsmin %lld \n",tsmin);getc(stdin);
	fseek(fl,pos,SEEK_SET);//back to the reference positon */

	trig++;
	find_new_ref=0;
	if(ref.trig_tsns==tsmin)
	  {
	    ref.trig=trig;
	    fseek(fl,-son,SEEK_CUR);
	    fwrite(&ref,son,1,fl);
	    find_new_ref=1;
	  }

	
	//	printf("fnr %1d trig %d",find_new_ref,trig);print_list(1,0,&ref);getc(stdin);
	while(1)
	  {
	    if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	    
	    if(curr.trig_tsns==tsmin)
	      {
		curr.trig=trig;
		fseek(fl,-son,SEEK_CUR);
		fwrite(&curr,son,1,fl);
	      }
	    
	    dt=curr.tsns-ref.tsns;
	    if(dt>MAXWIN) //out of coincidence window
	      break;
	  }

	fseek(fl,pos,SEEK_SET);//back to the reference positon */
	

	if(find_new_ref==1)
	  {
	    found=0;
	    while(1)
	      {
		if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
		
		if(curr.trig_tsns>0)
		  if(curr.trig==-1)
		    if(curr.trig_tsns>ref.trig_tsns) //found next time stamp
		      {
			memcpy(&ref,&curr,son);
			pos=ftell(fl);//save current position
			found=1;
			break;
		      }
	      }
	    if(found==0) break;
	  }
	if((trig%1000)==0)
	  printf("Done with trigger %d\r",trig);
      }
    printf("Done with trigger %d\n",trig);
    fclose(fl);    
}

