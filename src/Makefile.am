INCLUDES = $(VMOD_INCLUDES)

vmoddir = $(VMOD_DIR)
vmod_LTLIBRARIES = libvmod_example.la

libvmod_example_la_LDFLAGS = -module -export-dynamic -avoid-version

libvmod_example_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_example.c

vcc_if.c vcc_if.h: $(VMOD_TOOL) $(top_srcdir)/src/vmod_example.vcc
	@PYTHON@ $(VMOD_TOOL) $(top_srcdir)/src/vmod_example.vcc

tests/*.vtc: libvmod_example.la
	$(VARNISHTEST) -Dvarnishd=$(VARNISHD) -Dvmod_topbuild=$(abs_top_builddir) $@

TESTS_PARALLELISM = 3
check: libvmod_example.la
	$(VARNISHTEST) -j$(TESTS_PARALLELISM) -Dvarnishd=$(VARNISHD) -Dvmod_topbuild=$(abs_top_builddir) $(srcdir)/tests/*.vtc
	@echo "==================="
	@echo "All tests succeeded"
	@echo "==================="

EXTRA_DIST = \
	vmod_example.vcc \
	$(top_srcdir)/src/tests/*.vtc

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
