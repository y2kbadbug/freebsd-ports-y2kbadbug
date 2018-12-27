# $FreeBSD$

PORTNAME=	pulseeffects
DISTVERSIONPREFIX=      v
DISTVERSION=	4.4.1
CATEGORIES=	audio

MAINTAINER=	daniel@shafer.cc
COMMENT=	Audio effects for Pulseaudio applications

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE.md

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cairo>0:graphics/py-cairo@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}gstreamer1>0:multimedia/py-gstreamer1@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>0:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scipy>0:science/py-scipy@${PY_FLAVOR} \
		appstream-glib>0:devel/appstream-glib \
		calf-lv2>0:audio/calf-lv2 \
		itstool>0:textproc/itstool \
		ladspa>0:audio/ladspa \
		mda-lv2>0:audio/mda-lv2 \
		swh-lv2>0:audio/swh-lv2 \
		zam-plugins-lv2>0:audio/zam-plugins-lv2

LIB_DEPENDS=	libboost_thread.so:devel/boost-libs \
		libbs2b.so:audio/libbs2b \
		libebur128.so:audio/libebur128 \
		libgstreamer-1.0.so:multimedia/gstreamer1 \
		liblilv-0.so:audio/lilv \
		libpulse.so:audio/pulseaudio \
		librubberband.so:audio/rubberband \
		libsamplerate.so:audio/libsamplerate \
		libsndfile.so:audio/libsndfile \
		libzita-convolver.so:audio/zita-convolver

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cairo>0:graphics/py-cairo@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}gstreamer1>0:multimedia/py-gstreamer1@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>0:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scipy>0:science/py-scipy@${PY_FLAVOR} \
		calf-lv2>0:audio/calf-lv2 \
		gstreamer1-plugins-webrtcdsp>0:audio/gstreamer1-plugins-webrtcdsp \
		ladspa>0:audio/ladspa \
		mda-lv2>0:audio/mda-lv2 \
		swh-lv2>0:audio/swh-lv2 \
		zam-plugins-lv2>0:audio/zam-plugins-lv2

USES=		desktop-file-utils localbase:ldflags libtool gettext gnome meson \
		ninja pathfix pkgconfig python:3.6+ shebangfix
USE_GNOME=	cairo gconf2 glib20 gtk30 glibmm gtkmm30 libsigc++20 pygobject3
USE_GSTREAMER1=	bs2b bad good ladspa lv2 pulse
USE_GITHUB=	yes
GH_ACCOUNT=	wwmm
USE_LDCONFIG=   yes

GLIB_SCHEMAS=	com.github.wwmm.pulseeffects.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.autogain.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.bassenhancer.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.compressor.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.convolver.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.crossfeed.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.crystalizer.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.deesser.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.equalizer.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.exciter.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.filter.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.gate.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.limiter.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.loudness.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.maximizer.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.multibandcompressor.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.multibandgate.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.reverb.gschema.xml \
		com.github.wwmm.pulseeffects.sinkinputs.stereotools.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.compressor.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.deesser.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.equalizer.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.filter.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.gate.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.limiter.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.multibandcompressor.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.multibandgate.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.pitch.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.reverb.gschema.xml \
		com.github.wwmm.pulseeffects.sourceoutputs.webrtc.gschema.xml

INSTALLS_ICONS=	yes
INSTALL_TARGET= install-strip
SHEBANG_FILES=	meson_post_install.py

.include <bsd.port.mk>
