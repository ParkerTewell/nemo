/*
 *  SNAPIDL: tabulate a snapshot in binary mode for IDL
 *
 *      26-nov-2002    Test example for Walter Dehnen             Peter Teuben
 */

#include <stdinc.h>
#include <getparam.h>
#include <math.h>
#include <vectmath.h>
#include <filestruct.h>
#include <history.h>

#include <snapshot/snapshot.h>	
#include <snapshot/body.h>
#include <snapshot/get_snap.c>

string defv[] = {		/* DEFAULT INPUT PARAMETERS */
    "in=???\n			Input file (snapshot)",
    "options=x,y,z,vx,vy,vz\n	Things to output",
    "times=all\n		Times to select snapshot",
    "out=-\n                    Output file - normally a pipe for IDL",
    "VERSION=1.0\n		26-nov-02 PJT",
    NULL,
};

string usage="tabulate a snapshot for IDL in binary mode";

#define MAXOPT    50

void nemo_main()
{
    stream instr, outstr;
    real   tsnap, dr, aux;
    string times;
    Body *btab = NULL, *bp, *bq;
    float  *vec, sca;
    int i, n, nbody, bits, nsep, isep, nopt, ParticlesBit;
    char fmt[20],*pfmt;
    string *burststring(), *opt;
    rproc btrtrans(), fopt[MAXOPT];

    ParticlesBit = (MassBit | PhaseSpaceBit | PotentialBit | AccelerationBit |
            AuxBit | KeyBit | DensBit | EpsBit);
    instr = stropen(getparam("in"), "r");	
    outstr = stropen(getparam("out"), "w");
    setbuf(outstr,(char *)0);                   /* suggested by IDL, inc */

    opt = burststring(getparam("options"),", ");
    nopt = 0;					/* count options */
    while (opt[nopt]) {				/* scan through options */
        fopt[nopt] = btrtrans(opt[nopt]);
        nopt++;
        if (nopt==MAXOPT) {
            dprintf(0,"\n\nMaximum number of options = %d exhausted\n",MAXOPT);
            break;
        }
    }
    times = getparam("times");

    for(;;) {                /* repeating until first or all times are read */
	get_history(instr);
        if (!get_tag_ok(instr, SnapShotTag))
            break;                                  /* done with work */
        get_snap(instr, &btab, &nbody, &tsnap, &bits);
        if (!streq(times,"all") && !within(tsnap,times,0.0001))
            continue;                   /* skip work on this snapshot */
        if ( (bits & ParticlesBit) == 0)
            continue;                   /* skip work, only diagnostics here */
	vec = (float *) allocate(nbody*sizeof(float));

	fwrite(&nbody, sizeof(int), 1, outstr);
	sca = tsnap;
	fwrite(&sca, sizeof(float), 1, outstr);
	for (n=0; n<nopt; n++) {
	  for (bp = btab, i=0; bp < btab+nbody; bp++, i++) {
	    vec[i] = (float) fopt[n](bp,tsnap,i);
	  }
	  fwrite(vec, sizeof(float), nbody, outstr);
	}
	free(vec);
    }
    strclose(instr);
    strclose(outstr);
}
