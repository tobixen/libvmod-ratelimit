==============
vmod_ratelimit
==============

Development has been put on hold - there is a competing project out there, https://github.com/nand2/libvmod-throttle that seems to have more traction.

If the backend is the bottle neck (which usually is the case in our situation) I think it would be smarter to put the rate limiting into vcl_miss and/or vcl_pass and/or vcl_pipe rather than vcl_recv.
