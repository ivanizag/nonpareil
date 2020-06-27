/*
$Id: symtab.c 637 2005-05-21 21:12:18Z eric $
Copyright 1995, 2004 Eric L. Smith <eric@brouhaha.com>

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

#include "symtab.h"
#include "util.h"


typedef struct sym_t
{
  char *name;
  int value;
  int lineno;
  struct sym_t *left;
  struct sym_t *right;
} sym_t;


struct symtab_t
{
  sym_t *root;
};


symtab_t *alloc_symbol_table (void)
{
  symtab_t *table;
  table = calloc (1, sizeof (symtab_t));
  return (table);
}

static void free_entry (sym_t *p)
{
  if (p->left)
    free_entry (p->left);
  if (p->right)
    free_entry (p->right);
  free (p);
}

void free_symbol_table (symtab_t *t)
{
  free_entry (t->root);
  free (t);
}

static int insert_symbol (sym_t **p, sym_t *newsym)
{
  int i;

  if (! *p)
    {
      (*p) = newsym;
      return (1);
    }

  i = strcasecmp (newsym->name, (*p)->name);

  if (i == 0)
    return (0);
  else if (i < 0)
    return (insert_symbol (& ((*p)->left), newsym));
  else
    return (insert_symbol (& ((*p)->right), newsym));
}


/* returns 1 for success, 0 if duplicate name */
int create_symbol (symtab_t *table, char *name, int value, int lineno)
{
  sym_t *newsym;

  newsym = calloc (1, sizeof (sym_t));
  if (! newsym)
    {
      fprintf (stderr, "memory allocation failure\n");
      exit (2);
    }

  newsym->name = newstr (name);
  newsym->value = value;
  newsym->lineno = lineno;

  return (insert_symbol (& table->root, newsym));
}

/* returns 1 for success, 0 if not found */
int lookup_symbol (symtab_t *table, char *name, int *value)
{
  sym_t *p = table->root;
  int i;

  while (p)
    {
      i = strcasecmp (name, p->name);
      if (i == 0)
	{
	  *value = p->value;
	  return (1);
	}
      if (i < 0)
	p = p->left;
      else
	p = p->right;
    }
  return (0);
}

static void print_symbols (FILE *f, sym_t *p)
{
  if (! p)
    return;
  print_symbols (f, p->left);
  fprintf (f, "%05o %s %d\n", p->value, p->name, p->lineno);
  print_symbols (f, p->right);
}

void print_symbol_table (symtab_t *table, FILE *f)
{
  print_symbols (f, table->root);
}
