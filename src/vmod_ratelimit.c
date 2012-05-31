#include <stdlib.h>
#include <sys/time.h>
#include <bits/time.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"


double 
vmod_lastseen(struct sess *sp, struct vmod_priv *pc, struct vmod_priv *pv, struct sockaddr_storage *ip, const char *id, const char *tag)
/* pc = private data for the call - we use it for storing the timestamp */
/* pv = private data for the vmod */
{
  double last_seen;

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
  gettimeofday(pv->priv, NULL);

  /* set pc->priv to current time */
  *((double *)pc->priv) = (*((struct timeval *)pv->priv)).tv_sec+((*((struct timeval *)pv->priv)).tv_usec/1000000.0);

  /* return the difference between current time and last seen time */
  return *((double *)pc->priv) - last_seen;
}

/* for performance reasons, we allocate space for a timeval globally
   and once and reference it by the vmod private pointer */
/* TODO ... reconsider?  this causes some needless thread-unsafety?
   how costly is it to allocate memory?  We already have one local
   variable in the vmod_lastseen function, it wouldn't be that costly
   to add one more, would it? */
int
init_function(struct vmod_priv *priv, const struct VCL_conf *cfg)
{
  priv->priv = malloc(sizeof(struct timeval));
  AN(priv->priv);
  priv->free = free;
  return (0);
}

