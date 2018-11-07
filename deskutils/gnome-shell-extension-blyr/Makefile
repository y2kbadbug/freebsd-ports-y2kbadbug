# $FreeBSD$

PORTNAME=	gnome-shell-extension-blyr
PORTVERSION=	0.0.0.20180918
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Apply a Blur Effect to GNOME Shell UI elements

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas
RUN_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas

USES=		gettext gmake gnome localbase pkgconfig
USE_GNOME=	glib20
USE_GITHUB=	yes

GLIB_SCHEMAS=	org.gnome.shell.extensions.blyr.gschema.xml

GH_ACCOUNT=	yozoon
GH_PROJECT=	gnome-shell-extension-blyr
GH_TAGNAME=	07c60d0 

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

NO_ARCH=	yes

do-install:
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/blyr@yozoon.dev.gmail.com
		${INSTALL_DATA} ${WRKSRC}/blyr@yozoon.dev.gmail.com/schemas/org.gnome.shell.extensions.blyr.gschema.xml \
			${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		cd ${WRKSRC}/blyr@yozoon.dev.gmail.com && ${COPYTREE_SHARE} . \
			${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/blyr@yozoon.dev.gmail.com

.include <bsd.port.mk>
