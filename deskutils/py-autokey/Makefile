# Created by: Daniel Shafer <daniel@shafer.cc>
# $FreeBSD$

PORTNAME=	autokey
PORTVERSION=	0.95.4
DISTVERSIONPREFIX=	v
CATEGORIES=	deskutils python
# Using GitHub until they update the version in pypi.
# MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	daniel@shafer.cc
COMMENT=	Desktop automation utility for Linux and X11

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}dbus>0:devel/py-dbus@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyinotify>0:devel/py-pyinotify@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}xlib>0:x11-toolkits/py-xlib@${PY_FLAVOR}

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}dbus>0:devel/py-dbus@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyinotify>0:devel/py-pyinotify@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}xlib>0:x11-toolkits/py-xlib@${PY_FLAVOR}

USES=		desktop-file-utils python:3.5+
USE_GITHUB=	yes
USE_PYTHON=	distutils shebangfix

GH_ACCOUNT=	autokey

INSTALLS_ICONS=	yes
NO_ARCH=	yes

OPTIONS_SUB=	yes
OPTIONS_MULTI=	UI
OPTIONS_MULTI_UI=	GTK QT

GTK_DESC=	Enable support for GTK
QT_DESC=	Enable support for QT5

OPTIONS_DEFAULT=	GTK

GTK_RUN_DEPENDS=	libappindicator>0:devel/libappindicator
GTK_USES=	gnome
GTK_USE=	GNOME=gtk30 pygobject3 gtksourceview3

GTK_BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}qt5-xml>0:textproc/py-qt5-xml@${PY_FLAVOR}
QT_USES=	qt:5 pyqt:5
QT_USE=		PYQT=qscintilla2 svg xml sip

post-patch:
	${REINPLACE_CMD} 's|share/man|man|g' ${WRKSRC}/setup.py

# setup.py installs both gtk and qt files no matter what, need to clean that up.
post-install-GTK-off:
	${RM} ${STAGEDIR}${PREFIX}/share/applications/autokey-gtk.desktop
	${RM} ${STAGEDIR}${PREFIX}/bin/autokey-gtk
	${RM} ${STAGEDIR}${PREFIX}/man/man1/autokey-gtk.1
post-install-QT-off:
	${RM} ${STAGEDIR}${PREFIX}/share/applications/autokey-qt.desktop
	${RM} ${STAGEDIR}${PREFIX}/bin/autokey-qt
	${RM} ${STAGEDIR}${PREFIX}/man/man1/autokey-qt.1

.include <bsd.port.mk>
