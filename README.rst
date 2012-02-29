============
vmod_example
============

----------------------
Varnish Example Module
----------------------

:Author: Martin Blix Grydeland
:Date: 2012-04-13
:Version: 1.1
:Manual section: 3

SYNOPSIS
========

import example;

DESCRIPTION
===========

Example Varnish vmod demonstrating how to write an out-of-tree Varnish vmod.

Implements the traditional Hello World as a vmod.

FUNCTIONS
=========

hello
-----

Prototype
        ::

                hello(STRING S)
Return value
	STRING
Description
	Returns "Hello, " prepended to S
Example
        ::

                set resp.http.hello = example.hello("World");

INSTALLATION
============

This is an example skeleton for developing out-of-tree Varnish
vmods. It implements the "Hello, World!" as a vmod callback. Not
particularly useful in good hello world tradition, but demonstrates how
to get the glue around a vmod working.

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure
    -or-
 PKG_CONFIG_PATH=/my/varnish/build/directory ./configure

The configure script will search for an installed Varnish instance
through `pkg-config`, and configure the build against this instance.

Set the `PKG_CONFIG_PATH` environment variable to override the default
pkg-config search path. Note that this can also be an uninstalled
(but configured and built) Varnish source tree.

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``
* make src/tests/testcase.vtc - run the specified unit test

In your VCL you could then use this vmod along the following lines::

        import example;

        sub vcl_deliver {
                # This sets resp.http.hello to "Hello, World"
                set resp.http.hello = example.hello("World");
        }

HISTORY
=======

This manual page was released as part of the libvmod-example package,
demonstrating how to create an out-of-tree Varnish vmod.

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-example project. See LICENSE for details.

* Copyright (c) 2011 Varnish Software
