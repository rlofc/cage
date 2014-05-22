BEGIN {
   block=0;
   printf(".. highlight:: c\n\n");
}

{
   spos=match($0,"^[/][*]");
   mpos=match($0,"^[ ][*][ ]|^[ ][*]$");
   epos=match($0,"^[ ][*][/]");

   if(spos > 0 && epos ==0)
   {
      printf("%s\n",substr($0,spos+3,length($0)));
      block=0;
   }
   else if ( spos == 0 && epos > 0)
   {
      printf("%s\n",substr($0,spos+3,epos-3));
      block=1;
   }
   else if(mpos > 0)
   {
      printf("%s\n",substr($0,mpos+3,length($0)));
      block=0;
   }
   else if (epos > 0)
   {
      block=1;
   }
   else if ( epos == 0 && mpos == 0 && spos == 0 )
   {
      if (block==1)
      {
          block = 0;
          printf("\n::\n\n");
      }
      printf("\t%s\n",$0);
   }
}

END {
   if(found==1)
   {
       print "there is unmatched comment"
   }
}
