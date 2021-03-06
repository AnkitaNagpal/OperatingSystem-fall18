#include "types.h"
#include "stat.h"
#include "user.h"


char buf[512];
int flagI = 0;
int flagD = 0;
int flagC = 0;
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
  int i, n;
  int c;
  char strRepeat[1024] = "";
  char new_string[1024] = "";
  int savedStrCounter = 0;
  int savedStrCounterEnd = 0;
  int printFlag = 1;
  int RepeatCount = 1;
  int blankCounter;
  c = 0;

  char string[1024];


  while ((n = read (fd, buf, sizeof (buf))) > 0)
    {

      for (i = 0; i < n; i++)
	{

	  if (buf[i] == '\n')
	    {

	      if (buf[i - 1] == '\n')
		{
		  blankCounter = 0;
		  if (i == 0)
		    blankCounter = 1;


		  while (buf[i] == '\n')
		    {
		      blankCounter++;
		      i++;
		    }
		  i--;
		  RepeatCount = blankCounter;
		  strcpy (strRepeat, "");
		  strcpy (new_string, "");
		}
	      if (savedStrCounterEnd != c || blankCounter > 0)
		{
		  printFlag = 0;
		}
	      if (printFlag == 0)
		{

		  if (flagC == 1)
		    {
		      printf (1, "%4d %s\n", RepeatCount, strRepeat);
		    }
		  else if (flagD == 1 && RepeatCount > 1)
		    {
		      printf (1, "%s\n", strRepeat);

		    }
		  else if (flagD == 0 && flagC == 0)
		    {
		      printf (1, "%s\n", new_string);
		    }
		  if (flagC == 2)
		    flagC = 1;

		  memset (strRepeat, 0, 512);
		  strcpy (strRepeat, new_string);
		  printFlag = 1;
		  RepeatCount = 1;
		}
	      else
		{
		  RepeatCount++;
		}
	      blankCounter = 0;
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

		      if (flagI == 1)
			{
			  if (toUpperCase (buf[i]) !=
			      toUpperCase (strRepeat[savedStrCounter]))
			    {
			      printFlag = 0;
			    }
			}
		      else
			{
			  if (buf[i] != strRepeat[savedStrCounter])
			    {
			      printFlag = 0;
			    }
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

	}

      if (flagC == 1)
	{
	  printf (1, "%d %s\n", RepeatCount, strRepeat);
	}

      if (flagD == 1 && RepeatCount > 1)
	{
	  printf (1, "%s\n", strRepeat);

	}

    }
}

int
main (int argc, char *argv[])
{
  int fd, i;
  char *name;

  fd = 0;
  name = "";

  if (argc <= 1)
    {
      uniq (fd, name);
      exit ();
    }
  else
    {
      for (i = 1; i < argc; i++)
	{
	  if (atoi (argv[i]) == 0 && *argv[i] != '0' && *argv[i] != '-')
	    {
	      if ((fd = open (argv[i], 0)) < 0)
		{
		  printf (1, "uniq: cannot open %s\n", argv[i]);
		  exit ();
		}
	    }
	  else if (strcmp (argv[i], "-c") == 0)
	    {
	      flagC = 2;
	    }
	  else if (strcmp (argv[i], "-d") == 0)
	    {
	      flagD = 1;
	    }


	  if (strcmp (argv[i], "-i") == 0)
	    {
	      flagI = 1;
	    }
	}
      uniq (fd, name);
      close (fd);
      exit ();
    }

}
