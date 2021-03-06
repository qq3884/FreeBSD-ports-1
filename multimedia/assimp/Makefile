# $FreeBSD$

PORTNAME=	assimp
DISTVERSIONPREFIX=	v
DISTVERSION=	4.0.1
CATEGORIES=	multimedia

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Library to import various 3D model formats in a uniform manner

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libminizip.so:archivers/minizip

BROKEN_powerpc64=	Does not build: error: ByteSwap has not been declared

USES=		cmake compiler:c++11-lib localbase:ldflags pkgconfig
USE_GITHUB=	yes
USE_LDCONFIG=	yes

# CMAKE_ARGS instructs cmake to skip runtime path removal during install
CMAKE_ARGS+=	-DCMAKE_SKIP_RPATH:BOOL=ON -DASSIMP_BUILD_TESTS:BOOL=OFF

PLIST_SUB=	SHLIB_VER=${DISTVERSION}

.include <bsd.port.pre.mk>

.if ${CHOSEN_COMPILER_TYPE} == gcc
# GCC C++11 support is broken on FreeBSD (see PR 193528 for details)
CXXFLAGS+=	-D_GLIBCXX_USE_C99
.endif

.include <bsd.port.post.mk>
