#include "types.h"
#include "stat.h"
#include "user.h"


char buf[512];

char
toUpperCase (char input)
{
  if (input >= 'a' && input <= 'z')
    input = input - 32;

  return input;
}




void
uniq (int fd, char *name)
{
  int i, n;			//n means the size of the chunk read, i keeps track of index of the chunk
  int l, c;			// l means line number, c means character count in string
  char strRepeat[512] = "";
  char new_string[512] = "";
  int savedStrCounter = 0;
  int savedStrCounterEnd = 0;
  int printFlag = 1;
  l = c = 0;
  //int lines = 10;

  char string[512];


  while ((n = read (fd, buf, sizeof (buf))) > 0)
    {

      for (i = 0; i < n; i++)
	{

	  if (buf[i] == '\n')
	    {
		memset (strRepeat, 0, 512);
	      strcpy (strRepeat, new_string);	// dont do coping the string pointer
	      if (printFlag == 0)
		{
		  printf (1, "%s\n", new_string);
		  //write new_string to file  with the escape charachter
		  printFlag = 1;
		}
	      l++;		//Increment line upon new line char
		
		memset (new_string, 0, 512);
	      memset (string, 0, 512);
	      savedStrCounterEnd = c;
	      savedStrCounter = 0;
	      c = 0;
	    }
	  else
	    {

	      if (printFlag == 1)
		{
		  if (savedStrCounterEnd >= savedStrCounter)
		    {
		      if (buf[i] != strRepeat[savedStrCounter])
			{
			  printFlag = 0;
			}
		    }
		  else
		    {
		      printFlag = 0;
		    }
		}
	      new_string[c] = buf[i];
		savedStrCounter++;
	      c++;
	    }
	  //  if (l == lines) {
	  //      exit();
	  // }
	}
      /* while ((n = read(fd, buf, sizeof(buf))) > 0) {
         for (i = 0; i < n; i++) {
         if (buf[i] == '\n') {
         l++; //Increment line upon new line char
         printf(1, "%s\n", string);
         memset(string, 0, 512);
         c = 0;
         }
         else {
         string[c] = buf[i];
         c++;
         }
         if (l == lines) {
         exit();
         }
         }
         } */

    }
}
  int main (int argc, char *argv[])
  {
    int fd,i;//,lines=0;
    char *name;

    fd = 0;			//default, no file specified, so takes user input instead
    name = "";			//default, assuming no file name specified

    if (argc <= 1)
      {
	uniq (fd,"textfile.txt");
	exit ();
      }
  else {
            for (i = 1; i < argc; i++) {
                  if (atoi(argv[i]) == 0 && *argv[i] != '0' && *argv[i] != '-') {//executes if not a number
                        if ((fd = open(argv[i], 0)) < 0) {//executes if can't open the file
                        //If fd == 0, end of file, if fd == -1, error
                        printf(1, "uniq: cannot open %s\n", argv[i]);
                        exit();
                        }
                        //name = argv[i];
                  }
                  else {//it's a number
			//*argv[i] = 1;
			argv[i]++;
                        
                    //lines= atoi(argv[i]++);
                  }
/*
                  uniq(fd, name, lines);
                  close(fd);
*/
            }
           uniq(fd, name);
            close(fd);
            exit();
      }
  
}
