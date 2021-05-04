
#include "CommandLineArguments.h"

int main(int argc, char **argv)
{    
    time_t start = time(NULL);
    CommandLineArguments cmlarg;
    if (cmlarg.parser(argc,argv))
    {
        if (!cmlarg.execute())
        {
            if ( strcmp(cmlarg.getErrorString(),"") != 0 )
                printf ("%s\n",cmlarg.getErrorString());
        }        
    }
    else
    {
        if ( strcmp(cmlarg.getErrorString(),"") != 0 )
            printf ("%s",cmlarg.getErrorString());
        printf ("usage: %s --input-file <file-name> --output-file <file-name> --mappers <# of mappers> --reducers <# of reducers> --sample-size <# of records in sample>\n",argv[0]);
        exit(1);
   }
    time_t end = time(NULL);
    printf ("Total time: %lu\n",end-start);
    
 
    return 0;
}