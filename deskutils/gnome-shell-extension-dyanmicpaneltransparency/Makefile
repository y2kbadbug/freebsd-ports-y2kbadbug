# $FreeBSD$

PORTNAME=	gnome-shell-extension-dynamicpaneltransparency
PORTVERSION=	0.0.0.20180922
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Adds Transparency To The Gnome Shell Panel

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas
RUN_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas

USES=		gettext gmake gnome localbase pkgconfig
USE_GNOME=	glib20
USE_GITHUB=	yes

GLIB_SCHEMAS=	org.gnome.shell.extensions.dynamic-panel-transparency.gschema.xml

GH_ACCOUNT=	rockon999
GH_PROJECT=	dynamic-panel-transparency
GH_TAGNAME=	767caed

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

NO_BUILD=	yes

do-install:
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/dynamic-panel-transparency@rockon999.github.io
		${INSTALL_DATA} ${WRKSRC}/dynamic-panel-transparency@rockon999.github.io/schemas/org.gnome.shell.extensions.dynamic-panel-transparency.gschema.xml \
			${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		cd ${WRKSRC}/dynamic-panel-transparency@rockon999.github.io && ${COPYTREE_SHARE} . \
			${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/dynamic-panel-transparency@rockon999.github.io

.include <bsd.port.mk>
