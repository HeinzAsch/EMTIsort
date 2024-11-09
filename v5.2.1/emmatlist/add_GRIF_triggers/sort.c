#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE *etinp, *inp;
  size_t son,etson;
  node nd;
  etnode etnd;
  static gmap map;
  int glow,ghigh,d;
  unsigned long long pos;
  int found;
  
  son=sizeof(node);
  etson=sizeof(etnode);
  
  if(argc!=6)
    {
      printf("emmatlist_add_GRIF_triggers EMMAT_list_name GRIF_list_name map gate_low_ns gate_high_ns \n");
      exit(-1);
    }
  
 
  printf("Program adds triggers from processed list of GRIF fragments to the EMMAT list.\n");
  

  if((etinp=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  if((inp=fopen(argv[2],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[2]);
      exit(-2);
    }
  
  
   read_map(argv[3],&map);
   glow=atoi(argv[4]);
   ghigh=atoi(argv[5]);

   while(1)//get to the start
     {
       if(fread(&etnd,etson,1,etinp)==1)
	 break;
     }
   
    while(1)
     {
       while(1)//gate into the range
	 {	   
	   if(fread(&nd,son,1,inp)!=1)//stop on a incorrect reading
	     break;
	   
	   if((nd.tsns+GATE)>=etnd.tsns)
	     break;
	 }
    
       pos=ftell(inp);//save current position in the GRIF list

       found=0;
       if(EMMA_channel(&nd,&map)==1)//in case this one is emmat channel
	 {
	   d=(int)(etnd.tsns-nd.tsns);	   
	   if(d>glow)
	     if(d<ghigh)
	       {
		 etnd.trig_tsns=nd.trig_tsns;
		 etnd.trig=nd.trig;
		 fseek(etinp,-etson,SEEK_CUR);
		 fwrite(&etnd,etson,1,etinp);
		 found=1;
		 pos=ftell(inp);
	       }
	 }

       if(found==0)
	 while(1)//check within the range
	   {	   
	     if(fread(&nd,son,1,inp)!=1)//stop on the incorrect reading
	       break;
	     d=(int)(etnd.tsns-nd.tsns);
	     if(-d>GATE)
	       break;
	     if(EMMA_channel(&nd,&map)==1)
	       if(d>glow)
		 if(d<ghigh)
		   {
		     etnd.trig_tsns=nd.trig_tsns;
		     etnd.trig=nd.trig;
		     fseek(etinp,-etson,SEEK_CUR);
		     fwrite(&etnd,etson,1,etinp);
		     pos=ftell(inp);
		     break;
		   }	   
	   }
       
       
 
       if(fread(&etnd,etson,1,etinp)!=1)
	 break;

	fseek(inp,pos,SEEK_SET);//back to the reference position for the next EMMAT event
     }
   
  fclose(inp);
  fclose(etinp);
}
