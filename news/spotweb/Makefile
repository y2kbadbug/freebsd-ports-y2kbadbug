# $FreeBSD$

PORTNAME=	spotweb
DISTVERSION=	1.3.9
CATEGORIES=	news www

MAINTAINER=	daniel@shafer.cc
COMMENT=	One of the most-featured Spotnet clients currently available

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.md

USES=	php:web
USE_PHP=	curl dom gettext mbstring xml zip zlib gd openssl

USE_GITHUB=	yes

NO_BUILD= yes
NO_ARCH=	yes

OPTIONS_MULTI=		DB
OPTIONS_MULTI_DB=	MYSQL PGSQL SQLITE
OPTIONS_DEFAULT=	MYSQL

MYSQL_USE=			php=mysqli
PGSQL_USE=			php=pgsql
SQLITE_USE=			php=sqlite3

PLIST_SUB=      WWWOWN=${WWWOWN} WWWGRP=${WWWGRP}
SUB_FILES=      pkg-message

do-install:
				@${MKDIR} ${STAGEDIR}${WWWDIR}
				(cd ${WRKSRC} && \
								${COPYTREE_SHARE} . ${STAGEDIR}${WWWDIR} "! -name .gitignore ! -name .gitattributes ! -name .scrutinizer.yml")
				@${FIND} -s ${STAGEDIR}${WWWDIR} -not -type d | \
								${SED} -e 's#^${STAGEDIR}${PREFIX}/##' > ${TMPPLIST}

.include <bsd.port.mk>
