# $FreeBSD: head/net-mgmt/prometheus-collectd-exporter/Makefile 479620 2018-09-12 21:52:47Z 0mp $

PORTNAME=	collectd_exporter
PORTVERSION=	0.4.0
DISTVERSIONPREFIX=	v
CATEGORIES=	net-mgmt

MAINTAINER=	dsp@php.net
COMMENT=	Collectd exporter for Prometheus

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		go gmake
USE_GITHUB=	yes
GH_ACCOUNT=	prometheus

GO_PKGNAME=     github.com/${GH_ACCOUNT}/${PORTNAME}
GO_TARGET=      github.com/${GH_ACCOUNT}/${PORTNAME}

PLIST_FILES=	bin/collectd_exporter

USE_RC_SUBR=    collectd_exporter

do-install:
	${INSTALL_PROGRAM} ${WRKDIR}/bin/collectd_exporter ${STAGEDIR}${PREFIX}/bin

.include <bsd.port.mk>
