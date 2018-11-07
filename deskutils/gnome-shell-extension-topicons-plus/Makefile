# $FreeBSD$

PORTNAME=	gnome-shell-extension-topicons-plus
PORTVERSION=	22
DISTVERSIONPREFIX=	v
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Gnome-shell extension to put the icons back to the tray

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/gpl-2.0.txt

BUILD_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas
RUN_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas

USES=		gettext gmake gnome localbase pkgconfig
USE_GNOME=	glib20
USE_GITHUB=	yes

GLIB_SCHEMAS=	org.gnome.shell.extensions.topicons.gschema.xml

GH_ACCOUNT=	phocean
GH_PROJECT=	TopIcons-plus

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

NO_ARCH=	yes

ALL_TARGET=	install
INSTALL_PATH=	${STAGEDIR}${PREFIX}/share/gnome-shell/extensions

do-patch:
		${REINPLACE_CMD} -e 's|--preserve=timestamps|-p|g' ${WRKSRC}/Makefile

do-install:
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/TopIcons@phocean.net
		${INSTALL_DATA} ${WRKSRC}/schemas/org.gnome.shell.extensions.topicons.gschema.xml \
			${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		cd ${WRKSRC} && ${COPYTREE_SHARE} . \
			${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/TopIcons@phocean.net

.include <bsd.port.mk>
