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

uptodate "${MSGPACK_LIBRARIES}" ||
(
    rm -Rf "${BUILDDIR}/${MSGPACK_NAME}"

    download "${MSGPACK_SNAPSHOT}" "${BUILDDIR}/${MSGPACK_TARBALL}" ||
    die "unable to download the snapshot"

    cd "${BUILDDIR}" ||
    die "unable to move to the build directory '${BUILDDIR}'"

    tar xzf "${MSGPACK_TARBALL}" ||
    die "unable to extract the tarball"

    cd "${MSGPACK_NAME}" ||
    die "unable to enter the directory"

    ./configure                                                         \
        --prefix="${WORKDIR}" ||
    die "unable to configure"

    make install ||
    die "unable to build"
)
