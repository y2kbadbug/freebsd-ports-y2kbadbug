# $FreeBSD$

PORTNAME=	nautilus-python
DISTVERSION=	1.2.2
CATEGORIES=	x11-fm gnome python
MASTER_SITES=	GNOME

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Python nautilus bindings

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		gmake gnome libtool localbase pathfix pkgconfig python:3.6+ tar:xz
USE_GNOME=	cairo gdkpixbuf2 nautilus3 pygobject3

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	GTKDOC

GTKDOC_MESON_TRUE=	gtk_doc
GTKDOC_DESC=		Build documentation
GTKDOC_BUILD_DEPENDS=	gtkdocize:textproc/gtk-doc
GTKDOC_CONFIGURE_ENABLE=	gtk-doc

GNU_CONFIGURE=	yes

.include <bsd.port.mk>
