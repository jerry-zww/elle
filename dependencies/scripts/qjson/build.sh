#
# ---------- header -----------------------------------------------------------
#
# project       libraries
#
# license       infinit
#
# author        julien quintard   [fri feb 24 14:55:50 2012]
#

#
# ---------- globals ----------------------------------------------------------
#

SCRIPT=`basename "${0}"`
ROOTDIR=`python -c "import os;print(os.path.abspath(os.path.dirname('$0')))"`

#
# ---------- imports ----------------------------------------------------------
#

BASEDIR="${ROOTDIR}/../.."

source "${BASEDIR}/environment.sh"
source "${BASEDIR}/common.sh"

#
# ---------- entry point ------------------------------------------------------
#

uptodate "${QJSON_LIBRARIES}" ||
(
    rm -Rf "${BUILDDIR}/${QJSON_NAME}"

    download "${QJSON_SNAPSHOT}" "${BUILDDIR}/${QJSON_TARBALL}" ||
    die "unable to download the snapshot"

    cd "${BUILDDIR}" ||
    die "unable to move to the build directory '${BUILDDIR}'"

    tar xzf "${QJSON_TARBALL}" ||
    die "unable to extract the tarball"

    cd "${QJSON_NAME}" ||
    die "unable to enter the directory"

    mkdir build ||
    die "unable to create the build/ directory"

    cd build ||
    die "unable to move to the build/ directory"

    cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX="${WORKDIR}" .. ||
    die "unable to configure"

    make install ||
    die "unable to build"

    mkdir -p "${WORKDIR}/include/QJson" ||
    die "unable to create the QJson/ include directory"

    echo '#include "../qjson/serializer.h"' > "${WORKDIR}/include/QJson/Serializer"
    echo '#include "../qjson/parser.h"' > "${WORKDIR}/include/QJson/Parser"
    echo '#include "../qjson/qobjecthelper.h"' > "${WORKDIR}/include/QJson/QObjectHelper"
)
