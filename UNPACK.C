#include <stdio.h>
/*
 *  This program is designed to unpack the individual files that have
 *  been combined in .pak files to facilitate file transfer. In a .pak
 *  file, there are heading lines consisting of
 *
 *	##########
 *
 *  followed by a file name, followed by the lines of the file up to
 *  the next heading line.
 *
 *  This program expects the .pak file as standard input and creates
 *  the unpacked file at the local it is run.
 *
 *  This program is not particularly sophisticated and it may need modification
 *  for the local environment.  In particular, it uses gets(s) to get the
 *  next line into s without a line terminator.  The alternative is to use
 *  fgets(s,n,stdin) and replace the line terminator by a null.
 */

/*
 *  Maximum line length; some test output has very long lines.
 */
#define maxlen 1000

main()
   {
   char line[maxlen+2];
   char name[30];
   int first;
   FILE *outfile;

   while (fgets(line, maxlen+2, stdin)) {	/* get the next line */
      if (!strcmp("##########\n", line)) {	/* look for heading line */
         if (first == 1)
            fclose(outfile);			/* close currently open file */
         first = 1;
         if (gets(name) == NULL) {		/* get file name */
            fprintf(stderr,"premature eof on input\n");
            fflush(stderr);
            exit();
            }
         outfile = fopen(name, "w");		/* open file for writing */
         if (outfile == NULL) {
            fprintf(stderr,"cannot open file \"%s\"\n", name);
            abort();
            }
         }
      else {
         fputs(line,outfile);			/* else write line to file */
         if (ferror(outfile)) {
            fprintf(stderr,"error writing \"%s\"\n");
            fflush(stderr);
            abort();
            }
         }
      }
   exit();
   }
