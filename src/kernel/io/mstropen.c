/*
 * MSTROPEN:   aid opening multiple files serially using a template
 *             useful if you want to split simulation files in
 *             pieces under your own control
 *
 *    8-may-2002  created on Amtrak,  Amar suggesting this for the 2GB problem   PJT
 */

#include <stdinc.h>

mstr *mstr_init(string template)
{
  mstr *mp = allocate(sizeof(mstr));

  mp->template = allocate(strlen(template)+1);
  mp->filename = allocate(strlen(template)+20);
  strcpy(mp->template,template);
  mp->status = 0;
  mp->count = 0;
  mp->mode = (strchr(template,'%') != NULL);
  if (mp->mode) {
    int n;
    n = sprintf(mp->filename,mp->template,mp->count);
    if (n < 0) error("Problem using %s as template filename",mp->template);
  } else
    strcpy(mp->filename,mp->template);
  dprintf(1,"mstr_init: %s\n",mp->filename);

  mp->ostr = stropen(mp->filename,"w");
  return mp;
}

stream mstr_open(mstr *mp)
{
  if (mp->count == 0) {
    mp->count++;
    return mp->ostr;
  }
  if (mp->mode) {
    sprintf(mp->filename,mp->template,mp->count);
    strclose(mp->ostr);
    mp->ostr = stropen(mp->filename,"w");
  }
  dprintf(1,"mstr_open: %s count=%d\n",mp->filename,mp->count);
  mp->count++;
  return mp->ostr;
}

void mstr_close(mstr *mp)
{
  dprintf(1,"mstr_close: %s count=%d\n",mp->template,mp->count);
  if (mp->ostr) strclose(mp->ostr);
  free(mp->filename);
  free(mp->template);
  free(mp);
}


#if defined(TESTBED)

#include <getparam.h>

string defv[] = {
  "out=test%03d.dat\n     template name",
  "n=10\n                 number to write",
  "VERSION=1.0\n          8-may-2002 PJT",
  NULL,
};

string usage="testing mstropen";

nemo_main()
{
  mstr *mp;
  int i, n = getiparam("n");


  mp = mstr_init(getparam("out"));
  for (i=0; i<n; i++) {
    stream ostr = mstr_open(mp);
    fprintf(ostr,"Hello world, i=%d\n",i);
  }
  mstr_close(mp);
}
#endif
