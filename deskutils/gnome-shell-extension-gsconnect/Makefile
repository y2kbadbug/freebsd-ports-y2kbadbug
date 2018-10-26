# $FreeBSD$

PORTNAME=	gnome-shell-extension-gsconnect
DISTVERSIONPREFIX=	v
DISTVERSION=	13
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
		folks-import:net-im/folks \
		sshfs:sysutils/fusefs-sshfs \
		gsound-play:audio/gsound \
		libcanberra-gtk3>0:audio/libcanberra-gtk3

USES=		gnome meson ninja pkgconfig python:3.5+ shebangfix localbase
USE_GNOME=	glib20

SHEBANG_FILES=	src/service/components/folks.py

GLIB_SCHEMAS=   org.gnome.Shell.Extensions.GSConnect.gschema.xml

USE_GITHUB=     yes
GH_ACCOUNT=     andyholmes
GH_PROJECT=     gnome-shell-extension-gsconnect
MESON_ARGS=	--sysconfdir=${PREFIX}/etc

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

NO_ARCH=	yes

post-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
	@${MV} "${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/gsconnect@andyholmes.github.io/schemas/org.gnome.Shell.Extensions.GSConnect.gschema.xml" \
		${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
	@${RMDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/gsconnect@andyholmes.github.io/schemas

.include <bsd.port.mk>
