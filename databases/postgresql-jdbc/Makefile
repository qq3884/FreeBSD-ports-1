# Created by: Palle Girgensohn <girgen@partitur.se>
# $FreeBSD$

PORTNAME=	postgresql
PORTVERSION=	9.2.1004
DISTVERSIONSUFFIX=.src
CATEGORIES=	databases java
MASTER_SITES=	http://jdbc.postgresql.org/download/
PKGNAMESUFFIX=	-jdbc
DISTNAME=	${PORTNAME}${PKGNAMESUFFIX}-${DISTVERSION:C/.([0-9][0-9][0-9]*)/-\1/g}${DISTVERSIONSUFFIX}

MAINTAINER=	pgsql@FreeBSD.org
COMMENT=	The Java JDBC implementation for PostgreSQL

LICENSE=	BSD3CLAUSE

DIST_SUBDIR=	postgresql

USE_ANT=	yes
USE_JAVA=	yes
NO_ARCH=	yes

PLIST_FILES=	%%JAVAJARDIR%%/postgresql.jar
PORTDOCS=	*
DOCSDIR=	${PREFIX}/share/doc/${PORTNAME}${PKGNAMESUFFIX}
SUB_FILES=	pkg-message

OPTIONS_DEFINE=	DOCS
OPTIONS_SUB=	yes

post-patch:
	${REINPLACE_CMD} 's,/usr/local/pgsql/share/java,${JAVAJARDIR},' ${WRKSRC}/README

do-install:
	${INSTALL_DATA} ${WRKSRC}/jars/postgresql.jar ${STAGEDIR}${JAVAJARDIR}/postgresql.jar

do-install-DOCS-on:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
