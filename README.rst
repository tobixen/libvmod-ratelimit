==============
vmod_ratelimit
==============

----------------
Ratelimit Module
----------------

:Author: Tobias Brox <tobias@redpill-linpro.com>
:Date: 2012-05-31
:Version: 0.01
:Manual section: 3

SYNOPSIS
========

import ratelimit;

DESCRIPTION
===========

This vmod allows simple rate limiting logics to be implemented in vcl.  (this does not work out very well at the moment due to a varnish-bug or perhaps a misunderstanding - see https://www.varnish-cache.org/trac/ticket/1145 )

FUNCTIONS
=========

lastseen
--------

Prototype
        ::

                ratelimit.lastseen(IP ip, STRING url, STRING tag)
Return value
        DURATION
Description
        Returns the duration since last time the id and tag was seen - for very simple ratelimiting (i.e. "there shoud be 5 seconds between each miss from this IP").  The function doesn't care at all about the parameters, only that they are identical with some earlier call to the same function.
Example
        ::

                  sub vcl_miss {
                    if (lastseen(client.ip, "", "miss") < 5s) {
                        error 429 "enhance your calm and try again in some few secs";
                    }
                  }


INSTALLATION
============

This vmod will probably only work towards varnish 3.0 as for now.

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

HISTORY
=======

This was forked from the libvmod-example package.

Version 0.01 - lastseen implemented and tested

ROADMAP
=======

* Make sure "make check" works
* Go through the installation steps
* Spread the word
* Make a bit more complicated ratelimit func taking a parameter `n`, storing a list of length `n` and returning the duration of the last `n` calls.  ``ratelimit(client.ip, "", "sometag", 1)`` should then be equivalent to ``lastseen(client.ip, "", "sometag")``

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-example project. See LICENSE for details.

* Copyright (c) 2011 Varnish Software
* Copyright (c) 2012 Redpill-Linpro
