# $FreeBSD$

PORTNAME=	chrome-gnome-shell
PORTVERSION=	10.1
CATEGORIES=     www gnome
MASTER_SITES=	GNOME

MAINTAINER=	daniel@shafer.cc
COMMENT=	GNOME Shell integration for Chrome

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	base64:converters/base64 \
		jq:textproc/jq

RUN_DEPENDS=	gnome-shell>=3.28:x11/gnome-shell \
		${PYTHON_PKGNAMEPREFIX}requests>0:www/py-requests@${PY_FLAVOR} \
		unzip>=6.0:archivers/unzip

USES=           cmake:outsource gnome python:2.7+ tar:xz
USE_GNOME=      pygobject3

CMAKE_OFF=	BUILD_EXTENSION
CMAKE_ARGS=	-DCMAKE_INSTALL_LIBDIR=lib

INSTALL_TARGET=         install

NO_ARCH=        yes

.include <bsd.port.mk>
