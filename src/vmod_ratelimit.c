#include <stdlib.h>
#include <sys/time.h>
#include <bits/time.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"


double 
vmod_lastseen(struct sess *sp, struct vmod_priv *pc, struct sockaddr_storage *ip, const char *id, const char *tag)
/* pc = private data for the call - we use it for storing the timestamp */
{
  double last_seen;
  struct timeval tv;

  if (!pc->priv) {
    /* if varnish hasn't seen the function parameters before (or after
       garbage collection?) pc->priv will be NULL.  Allocate.
       last_seen=0 (epoch) => never seen before */
    pc->priv = malloc(sizeof(double));
    AN(pc->priv);
    pc->free = free;
    last_seen = 0;
  } else {
    /* copy out last_seen from pc->priv */
    last_seen = *((double *)pc->priv);
  }

  /* return time is supposed to be a double ... so to get higher
     precision than integer seconds, will need to use gettimeofday
     instead of a simple time */
  gettimeofday(&tv, NULL);

  /* set pc->priv to current time */
  *((double *)pc->priv) = tv.tv_sec+tv.tv_usec/1000000.0;

  /* return the difference between current time and last seen time */
  return *((double *)pc->priv) - last_seen;
}

