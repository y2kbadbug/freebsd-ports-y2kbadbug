# $FreeBSD$

PORTNAME=	gnome-shell-extension-screenshot
PORTVERSION=	0.0.0.20180924
CATEGORIES=	deskutils gnome
DIST_SUBDIR=	gnome

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Gnome Shell extension for making and uploading screenshots

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas \
		zip:archivers/zip

RUN_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		gsettings-desktop-schemas>=3.12.0:devel/gsettings-desktop-schemas

USES=		gettext gmake gnome localbase pkgconfig
USE_GNOME=	glib20
USE_GITHUB=	yes

GLIB_SCHEMAS=	org.gnome.shell.extensions.screenshot.gschema.xml

GH_ACCOUNT=	OttoAllmendinger
GH_PROJECT=	gnome-shell-screenshot
GH_TAGNAME=	8ababf7 

PKGMESSAGE=	../gnome-shell-extra-extensions/pkg-message.slaves

ALL_TARGET=	install
NO_ARCH=	yes

do-install:
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		@${MKDIR} ${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/gnome-shell-screenshot@ttll.de
		${INSTALL_DATA} ${WRKSRC}/src/schemas/org.gnome.shell.extensions.screenshot.gschema.xml \
			${STAGEDIR}${PREFIX}/share/glib-2.0/schemas/
		cd ${WRKSRC}/src/ && ${COPYTREE_SHARE} . \
			${STAGEDIR}${PREFIX}/share/gnome-shell/extensions/gnome-shell-screenshot@ttll.de

.include <bsd.port.mk>
