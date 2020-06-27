/*
$Id: state_io.h 526 2005-05-05 03:18:55Z eric $
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

void state_read_xml (sim_t *sim, char *fn);
void state_write_xml (sim_t *sim, char *fn);

// used only for nsim_conv:
void state_read_nsim (sim_t *sim, char *fn);
void state_write_nsim (sim_t *sim, char *fn);
