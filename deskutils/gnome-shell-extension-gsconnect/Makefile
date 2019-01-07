# $FreeBSD$

PORTNAME=	gnome-shell-extension-gsconnect
DISTVERSIONPREFIX=	v
DISTVERSION=	19
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome3

MAINTAINER=	daniel@shafer.cc
COMMENT=	KDE Connect implementation for GNOME

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas \
		re2c>0:devel/re2c

LIB_DEPENDS=	libcanberra.so:audio/libcanberra \
		libcanberra-gtk3.so:audio/libcanberra-gtk3

RUN_DEPENDS=	caribou-preferences:accessibility/caribou \
		folks-import:net-im/folks \
		gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas \
		libgdata>=0:devel/libgdata \
		nautilus-actions-config-tool:deskutils/nautilus-actions \
		nautilus-python>=0:x11-fm/nautilus-python \
		nautilus-sendto:deskutils/nautilus-sendto \
		sshfs:sysutils/fusefs-sshfs

USES=		desktop-file-utils gnome localbase meson ninja pkgconfig \
		python:3.6+ shebangfix
USE_GNOME=	glib20 gsound nautilus3

USE_GITHUB=	yes
GH_ACCOUNT=	andyholmes

# Disables installing web extensions
MESON_ARGS=     --sysconfdir=${PREFIX}/etc -Dwebextension=false

GLIB_SCHEMAS=   org.gnome.Shell.Extensions.GSConnect.gschema.xml

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves pkg-message

SHEBANG_FILES=	meson/nmh.sh \
		src/service/components/folks.py \
		webextension/mkwebext.sh

OPTIONS_DEFINE= NLS
OPTIONS_SUB=    yes

NLS_USES=       gettext

NO_ARCH=        yes

post-patch-NLS-off:
	@${REINPLACE_CMD} -e "s:subdir('po'):#subdir('po'):g" ${WRKSRC}/meson.build

.include <bsd.port.mk>
