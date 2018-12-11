# $FreeBSD$

PORTNAME=	nautilus-python
DISTVERSION=	1.2.2
CATEGORIES=	x11-fm gnome python
MASTER_SITES=	GNOME
PKGNAMEPREFIX= ${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Python nautilus bindings

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		gmake gnome libtool localbase pathfix pkgconfig python tar:xz
USE_GNOME=	cairo gdkpixbuf2 nautilus3 pygobject3
USE_PYTHON=	flavors

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	GTKDOC

GTKDOC_MESON_TRUE=	gtk_doc
GTKDOC_DESC=		Build documentation
GTKDOC_BUILD_DEPENDS=	gtkdocize:textproc/gtk-doc
GTKDOC_CONFIGURE_ENABLE=	gtk-doc

GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes

INSTALL_TARGET=	install-strip

.include <bsd.port.mk>
