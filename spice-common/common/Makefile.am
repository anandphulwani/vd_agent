NULL =

# Avoid need for python(pyparsing) by end users
CLIENT_MARSHALLERS =				\
	generated_client_demarshallers.c	\
	generated_client_marshallers.c		\
	generated_client_marshallers.h		\
	$(NULL)

SERVER_MARSHALLERS =				\
	generated_server_demarshallers.c	\
	generated_server_marshallers.c		\
	generated_server_marshallers.h		\
	$(NULL)

BUILT_SOURCES = $(CLIENT_MARSHALLERS) $(SERVER_MARSHALLERS)

noinst_LTLIBRARIES = libspice-common.la libspice-common-server.la libspice-common-client.la
libspice_common_la_SOURCES =		\
	agent.c				\
	agent.h				\
	backtrace.c			\
	backtrace.h			\
	canvas_utils.c			\
	canvas_utils.h			\
	demarshallers.h			\
	draw.h				\
	lines.c				\
	lines.h				\
	log.c				\
	log.h				\
	lz.c				\
	lz.h				\
	lz_common.h			\
	lz_config.h			\
	macros.h			\
	marshaller.c			\
	marshaller.h			\
	mem.c				\
	mem.h				\
	messages.h			\
	pixman_utils.c			\
	pixman_utils.h			\
	quic.c				\
	quic.h				\
	quic_config.h			\
	rect.h				\
	region.c			\
	region.h			\
	ring.h				\
	rop3.c				\
	rop3.h				\
	snd_codec.c			\
	snd_codec.h			\
	utils.c				\
	utils.h				\
	verify.h			\
	recorder.h			\
	$(NULL)

if ENABLE_RECORDER
libspice_common_la_SOURCES += \
	recorder/recorder.c		\
	recorder/recorder.h		\
	recorder/recorder_ring.c	\
	recorder/recorder_ring.h	\
	$(NULL)
endif

if ENABLE_AGENT_INTERFACE
libspice_common_la_SOURCES += \
	agent_interface.c		\
	agent_interface.h		\
	$(NULL)
endif

# These 2 files are not build as part of spice-common
# build system, but modules using spice-common will build
# them with the appropriate options. We need to let automake
# know that these are source files so that it can properly
# track these files dependencies
EXTRA_libspice_common_la_SOURCES = 	\
	sw_canvas.c			\
	sw_canvas.h			\
	$(NULL)

libspice_common_client_la_SOURCES =		\
	client_marshallers.h			\
	ssl_verify.c				\
	ssl_verify.h				\
	$(CLIENT_MARSHALLERS)			\
	$(NULL)

libspice_common_server_la_SOURCES =		\
	$(SERVER_MARSHALLERS)			\
	$(NULL)

AM_CPPFLAGS =				\
	-I$(top_srcdir)			\
	-I$(top_builddir)		\
	$(SPICE_COMMON_CFLAGS)		\
	$(PROTOCOL_CFLAGS)		\
	$(NULL)

libspice_common_la_LIBADD =				\
	$(SPICE_COMMON_LIBS)				\
	$(NULL)

MARSHALLERS_DEPS =					\
	$(top_srcdir)/python_modules/__init__.py	\
	$(top_srcdir)/python_modules/codegen.py		\
	$(top_srcdir)/python_modules/demarshal.py	\
	$(top_srcdir)/python_modules/marshal.py		\
	$(top_srcdir)/python_modules/ptypes.py		\
	$(top_srcdir)/python_modules/spice_parser.py	\
	$(top_srcdir)/spice_codegen.py			\
	$(NULL)

# Note despite being autogenerated these are not part of CLEANFILES, they are
# actually a part of EXTRA_DIST, to avoid the need for pyparser by end users
generated_client_demarshallers.c generated_messages.h: $(top_srcdir)/spice.proto $(MARSHALLERS_DEPS)
	$(AM_V_GEN)$(PYTHON) $(top_srcdir)/spice_codegen.py --generate-demarshallers --client --include common/messages.h \
	--generated-declaration-file generated_messages.h $< $@ >/dev/null

generated_client_marshallers.c generated_client_marshallers.h: $(top_srcdir)/spice.proto $(MARSHALLERS_DEPS)
	$(AM_V_GEN)$(PYTHON) $(top_srcdir)/spice_codegen.py --generate-marshallers -P --include common/client_marshallers.h --client \
	--generate-header $< $@ >/dev/null

generated_server_demarshallers.c: $(top_srcdir)/spice.proto $(MARSHALLERS_DEPS)
	$(AM_V_GEN)$(PYTHON) $(top_srcdir)/spice_codegen.py --generate-demarshallers --server --include common/messages.h $< $@ >/dev/null

STRUCTS = -M String -M Rect -M Point -M DisplayBase -M Fill -M Opaque -M Copy -M Blend -M Blackness -M Whiteness -M Invers -M Rop3 -M Stroke -M Text -M Transparent -M AlphaBlend -M Composite
generated_server_marshallers.c generated_server_marshallers.h: $(top_srcdir)/spice.proto $(MARSHALLERS_DEPS)
	$(AM_V_GEN)$(PYTHON) $(top_srcdir)/spice_codegen.py --generate-marshallers $(STRUCTS) --server --include common/messages.h \
    --generate-header $< $@ >/dev/null

EXTRA_DIST =				\
	$(CLIENT_MARSHALLERS)		\
	$(SERVER_MARSHALLERS)		\
	generated_messages.h		\
	meson.build			\
	canvas_base.c			\
	canvas_base.h			\
	lz_compress_tmpl.c		\
	lz_decompress_tmpl.c		\
	quic_family_tmpl.c		\
	quic_tmpl.c			\
	$(NULL)

GITIGNOREFILES = \
	generated_messages.h \
	$(NULL)

-include $(top_srcdir)/git.mk
