/*
$Id: bin2c.c 833 2005-06-26 20:02:14Z eric $
Copyright 2005 Eric L. Smith <eric@brouhaha.com>

Nonpareil is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.  Note that I am not
granting permission to redistribute or modify Nonpareil under the
terms of any later version of the General Public License.

Nonpareil is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program (in the file "COPYING"); if not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111, USA.
*/


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"


void usage (FILE *f)
{
  fprintf (f, "%s:  Microcode-level calculator simulator\n",
	   nonpareil_release);
  fprintf (f, "Copyright 2005 Eric L. Smith\n");
  fprintf (f, "http://nonpareil.brouhaha.com/\n");
  fprintf (f, "\n");
  fprintf (f, "usage: %s binfile arrayname [-h header] [-c source]\n", progname);
}


#define LINE_MAX_BYTES 8

int main (int argc, char *argv[])
{
  FILE *bin_f;
  char *bin_fn = NULL;
  char *array_name = NULL;
  char *header_fn = NULL;
  char *source_fn = NULL;
  bool need_comma = false;
  int line_pos = 0;
  int size = 0;

  progname = newstr (argv [0]);

  while (--argc)
    {
      argv++;
      if (*argv [0] == '-')
	{
	  if (strcmp (argv [0], "-h") == 0)
	    {
	      if (--argc == 0)
		fatal (1, "-h option must be followed by filename\n");
	      header_fn = argv [1];
	      argv++;
	    }
	  else if (strcmp (argv [0], "-c") == 0)
	    {
	      if (--argc == 0)
		fatal (1, "-c option must be followed by filename\n");
	      source_fn = argv [1];
	      argv++;
	    }
	  else
	    fatal (1, "unrecognized option '%s'\n", argv [0]);
	}
      else if (! bin_fn)
	bin_fn = argv [0];
      else if (! array_name)
	array_name = argv [0];
      else
	fatal (1, NULL);
    }

  if (! (bin_fn && array_name))
    fatal (1, "Input filename and array name must be specified.\n");

  bin_f = fopen (bin_fn, "rb");
  if (! bin_f)
    fatal (2, "Can't open input file\n");

  if (header_fn)
    {
      FILE *header_f = fopen (header_fn, "w");
      if (! header_f)
	fatal (2, "Can't open output header file\n");

      fprintf (header_f, "extern const unsigned char %s [];\n", array_name);
      fprintf (header_f, "extern unsigned long %s_size;\n", array_name);
      fclose (header_f);
    }

  if (source_fn)
    {
      FILE *source_f = fopen (source_fn, "w");
      if (! source_f)
	fatal (2, "Can't open output source file\n");

      fprintf (source_f, "const unsigned char %s [] =\n", array_name);
      fprintf (source_f, "{\n");

      while (true)
	{
	  int b = fgetc (bin_f);
	  if (b == EOF)
	    {
	      if (ferror (bin_f))
		fatal (3, "Error reading input file\n");
	      break;
	    }
	  size++;
	  if (need_comma)
	    fprintf (source_f, ",");
	  if (line_pos == LINE_MAX_BYTES)
	    {
	      fprintf (source_f, "\n");
	      line_pos = 0;
	    }
	  if (line_pos == 0)
	    fprintf (source_f, "  ");
	  fprintf (source_f, "0x%02x", b & 0xff);
	  line_pos++;
	  need_comma = true;
	}

      fprintf (source_f, "\n};\n");
      fprintf (source_f, "unsigned long %s_size = %d;\n", array_name, size);
      fclose (source_f);
    }

  exit (0);
}
