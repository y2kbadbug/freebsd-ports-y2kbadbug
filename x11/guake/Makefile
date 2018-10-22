# $FreeBSD: head/x11/guake/Makefile 465584 2018-03-26 12:38:56Z bapt $

PORTNAME=	guake
PORTVERSION=	3.4.0
CATEGORIES=     x11 python
MASTER_SITES=   CHEESESHOP
DISTNAME=       Guake-${PORTVERSION}

MAINTAINER=	daniel@shafer.cc
COMMENT=	Dropdown terminal made for the GNOME desktop

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pbr>0:devel/py-pbr@${PY_FLAVOR}

RUN_DEPENDS=	glib>2.0:devel/glib20 \
		gnome-settings-daemon>0:sysutils/gnome-settings-daemon \
		gsettings-desktop-schemas>0:devel/gsettings-desktop-schemas \
		keybinder-gtk3>0:x11/keybinder-gtk3 \
		keybinder>0:x11/keybinder \
		libnotify>0:devel/libnotify \
		${PYTHON_PKGNAMEPREFIX}gobject3>0:devel/py-gobject3@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}dbus>0:devel/py-dbus@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pbr>0:devel/py-pbr@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}notify2>0:devel/py-notify2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}xdg>0:devel/py-xdg@${PY_FLAVOR} \
		vte3>=0.42:x11-toolkits/vte3

USES=		gmake gnome libtool desktop-file-utils python:3.5+ localbase \
		shebangfix pathfix
USE_GNOME=	gtk30 intltool gconf2
USE_PYTHON=	distutils

GLIB_SCHEMAS=	org.guake.gschema.xml

NO_ARCH=	yes
INSTALLS_ICONS=	yes

MANPAGES_MAKE_ENV_OFF=	man_MANS=""

OPTIONS_DEFINE=	MANPAGES NLS
OPTIONS_DEFAULT=	MANPAGES NLS
OPTIONS_SUB=	yes

NLS_USES=               gettext
NLS_CONFIGURE_ENABLE=   nls

post-extract:
	${REINPLACE_CMD} -e 's|PYTHON_INTERPRETER=python3|PYTHON_INTERPRETER=${PYTHON_CMD}|g' ${WRKSRC}/Makefile

post-install:
	cd ${WRKSRC}; ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} install-schemas install-locale

.include <bsd.port.options.mk>
.include <bsd.port.mk>
