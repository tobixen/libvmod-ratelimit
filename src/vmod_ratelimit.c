#include <stdlib.h>
#include <sys/time.h>
#include <bits/time.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"


double 
vmod_lastseen(struct sess *sp, struct vmod_priv *pc, struct vmod_priv *pv, struct sockaddr_storage *ip, const char *id, const char *tag)
{
  double last_seen;
  if (!pc->priv) {
    pc->priv = malloc(sizeof(double));
    AN(pc->priv);
    pc->free = free;
    last_seen = 0;
  } else {
    last_seen = *((double *)pc->priv);
  }
  gettimeofday(pv->priv, NULL);
  *((double *)pc->priv) = (*((struct timeval *)pv->priv)).tv_sec+((*((struct timeval *)pv->priv)).tv_usec/1000000.0);
  return *((double *)pc->priv) - last_seen;
}

int
init_function(struct vmod_priv *priv, const struct VCL_conf *cfg)
{
  priv->priv = malloc(sizeof(struct timeval));
  AN(priv->priv);
  priv->free = free;
  return (0);
}

