# $FreeBSD$

PORTNAME=	gnome-shell-extension-gsconnect
DISTVERSIONPREFIX=	v
DISTVERSION=	17
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome3

MAINTAINER=	daniel@shafer.cc
COMMENT=	KDE Connect implementation for GNOME

LICENSE=        GPLv2
LICENSE_FILE=   ${WRKSRC}/LICENSE

BUILD_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas \
		re2c>0:devel/re2c

RUN_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas \
		libgdata>=0:devel/libgdata \
		folks-import:net-im/folks \
		sshfs:sysutils/fusefs-sshfs \
		gsound-play:audio/gsound \
		canberra-gtk-play:audio/libcanberra-gtk3 \
		caribou-preferences:accessibility/caribou \
		nautilus:x11-fm/nautilus \
		${PYTHON_PKGNAMEPREFIX}nautilus>=0:x11-fm/py-nautilus@${PY_FLAVOR} \
		nautilus-sendto:deskutils/nautilus-sendto \
		nautilus-actions-config-tool:deskutils/nautilus-actions \
		bash:shells/bash

USES=		gnome meson ninja pkgconfig python:3.5+ shebangfix localbase
USE_GNOME=	glib20

USE_GITHUB=	yes
GH_ACCOUNT=	andyholmes
GH_PROJECT=	gnome-shell-extension-gsconnect

SHEBANG_FILES=	src/service/components/folks.py \
		webextension/mkwebext.sh \
		meson/nmh.sh

GLIB_SCHEMAS=	org.gnome.Shell.Extensions.GSConnect.gschema.xml

OPTIONS_DEFINE=	NLS
OPTIONS_SUB=	yes
NLS_USES=	gettext

MESON_ARGS=	--sysconfdir=${PREFIX}/etc -Dwebextension=false

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves pkg-message

NO_ARCH=	yes

post-patch-NLS-off:
	@${REINPLACE_CMD} -e "s:subdir('po'):#subdir('po'):g" ${WRKSRC}/meson.build

.include <bsd.port.mk>
