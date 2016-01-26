/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/** General purpose utility functions @file */


#include <stdio.h>
#include <string.h>

#include "luasandbox/util/util.h"

size_t lsb_lp2(unsigned long long x)
{
  if (x == 0) return 0;
  x = x - 1;
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  x = x | (x >> 32);
  return (size_t)(x + 1);
}


double lsb_timespec_delta(const struct timespec* s, const struct timespec* e)
{
  double delta;
  if (e->tv_nsec - s->tv_nsec < 0) {
    delta = e->tv_sec - s->tv_sec - (e->tv_nsec - s->tv_nsec) / -1e9;
  } else {
    delta = e->tv_sec - s->tv_sec + (e->tv_nsec - s->tv_nsec) / 1e9;
  }
  return delta;
}


char* lsb_read_file(const char *fn)
{
  char *str = NULL;
  FILE *fh = fopen(fn, "rb");
  if (!fh) return str;

  if (fseek(fh, 0, SEEK_END)) goto cleanup;
  long pos = ftell(fh);
  if (pos == -1) goto cleanup;
  rewind(fh);

  str = malloc(pos + 1);
  if (!str) goto cleanup;

  size_t b = fread(str, 1, pos, fh);
  if ((long)b == pos) {
    str[pos] = 0;
  }

cleanup:
  fclose(fh);

  return str;
}