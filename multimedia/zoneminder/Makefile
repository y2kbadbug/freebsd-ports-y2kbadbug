# $FreeBSD$

PORTNAME=	zoneminder
PORTVERSION=	1.32.2
CATEGORIES=	multimedia

MAINTAINER=	bsd@abinet.ru
COMMENT=	Complete security camera solution, fully web based with image analysis

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

CONFLICTS_INSTALL=	zoneminder-h264

ZM_DEPENDS=	p5-DBI>=0:databases/p5-DBI \
		p5-DBD-mysql>=0:databases/p5-DBD-mysql \
		p5-Date-Manip>=0:devel/p5-Date-Manip \
		p5-Test-LWP-UserAgent>=0:www/p5-Test-LWP-UserAgent \
		p5-Sys-Mmap>=0:devel/p5-Sys-Mmap \
		p5-LWP-Protocol-https>=0:www/p5-LWP-Protocol-https \
		p5-Sys-CPU>=0:devel/p5-Sys-CPU \
		p5-Sys-MemInfo>=0:devel/p5-Sys-MemInfo \
		p5-Data-Dump>=0:devel/p5-Data-Dump \
		p5-SOAP-WSDL>=0:devel/p5-SOAP-WSDL \
		p5-Data-UUID>=0:devel/p5-Data-UUID \
		p5-Module-CoreList>=0:devel/p5-Module-CoreList \
		p5-IO-Socket-Multicast>=0:net/p5-IO-Socket-Multicast \
		ffmpeg:multimedia/ffmpeg
BUILD_DEPENDS=	${ZM_DEPENDS}

LIB_DEPENDS=    libx264.so:multimedia/libx264 \
                libmp4v2.so:multimedia/mp4v2 \
		libgcrypt.so:security/libgcrypt \

RUN_DEPENDS=	${ZM_DEPENDS} \
		sudo:security/sudo \
		p5-Device-SerialPort>=0:comms/p5-Device-SerialPort \
                p5-JSON-MaybeXS>=0:converters/p5-JSON-MaybeXS \
                p5-Number-Bytes-Human>=0:devel/p5-Number-Bytes-Human \
		zip:archivers/zip

USE_GITHUB=	yes
GH_PROJECT=	ZoneMinder
GH_TUPLE=	ZoneMinder:CakePHP-Enum-Behavior:ea90c0cd7f:cakephp_enum_behavior/web/api/app/Plugin/CakePHP-Enum-Behavior \
		FriendsOfCake:crud:0bd63fb:crud/web/api/app/Plugin/Crud

USES=		cmake:noninja jpeg mysql perl5 php shebangfix ssl gettext
USE_RC_SUBR=	zoneminder
USE_PHP=	json pdo_mysql session gd sockets ctype opcache

ONLY_FOR_ARCHS=	amd64 i386

OPTIONS_DEFINE=	NLS V4L DOCS
OPTIONS_SUB=	yes
NLS_USES=	gettext
NLS_CONFIGURE_ENABLE=	nls
V4L_BUILD_DEPENDS=	${LOCALBASE}/include/linux/videodev2.h:multimedia/v4l_compat
V4L_LIB_DEPENDS=	libv4l2.so:multimedia/libv4l

PLIST_SUB=	WWWOWN="${WWWOWN}" WWWGRP="${WWWGRP}"

SHEBANG_REGEX=	./scripts/.*\.pl.in

PORTDOCS=	AUTHORS BUGS ChangeLog INSTALL NEWS README.FreeBSD TODO

CMAKE_ARGS+=	-DZM_PERL_MM_PARMS=INSTALLDIRS=site \
		-DZM_CONFIG_DIR=${PREFIX}/etc/zoneminder \
		-DZM_WEBDIR=${WWWDIR} \
		-DZM_CGIDIR=${WWWDIR}/cgi-bin \
		-DZM_CONTENTDIR=${WWWDIR} \
		-DHAVE_SENDFILE=0 \
		-DZM_NO_CURL=ON \
		-DZM_NO_LIBVLC=ON \
		-DPCRE_LIBRARIES=0 \
		-DGNUTLS_LIBRARIES=0 \
		-DCMAKE_REQUIRED_INCLUDES:STRING="${LOCALBASE}/include"

.include <bsd.port.pre.mk>

.if ${PHP_VER} >= 70
RUN_DEPENDS+= ${PHPBASE}/lib/php/${PHP_EXT_DIR}/apcu.so:devel/pecl-APCu@${PHP_FLAVOR}
.else
RUN_DEPENDS+= ${PHPBASE}/lib/php/${PHP_EXT_DIR}/apcu.so:devel/pecl-APCu4@${PHP_FLAVOR}
.endif

PKGMESSAGE=	${WRKDIR}/pkg-message

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}

post-extract:
	${CP} ${FILESDIR}/README.FreeBSD ${WRKSRC}
	${CP} ${FILESDIR}/README.FreeBSD ${PKGMESSAGE}
	${REINPLACE_CMD} -e 's|E_ALL|E_ALL^E_NOTICE|g' ${WRKSRC}/web/index.php

pre-install:
	${MKDIR} ${STAGEDIR}${WWWDIR}/images
	${MKDIR} ${STAGEDIR}${WWWDIR}/events
	${MKDIR} ${STAGEDIR}${WWWDIR}/temp
	${MKDIR} ${STAGEDIR}${WWWDIR}/api/app/tmp
	${MKDIR} ${STAGEDIR}/var/run/zm
	${MKDIR} ${STAGEDIR}/var/tmp/zm

post-install:
	${INSTALL_DATA} ${STAGEDIR}${PREFIX}/etc/zoneminder/zm.conf ${STAGEDIR}${PREFIX}/etc/zoneminder/zm.conf.sample

post-install-DOCS-on:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${PORTDOCS} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.post.mk>
