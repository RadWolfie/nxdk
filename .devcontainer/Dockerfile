FROM alpine

# Requirement for build and use nxdk toolchain
RUN apk add --update --no-cache clang llvm lld cmake make pkgconf
RUN apk add --update --no-cache build-base flex bison

# NOTE: curl-dev is require to workaround unknown option failure from libcurl (assumed is old version)
RUN apk add --update cmake ninja zip unzip curl-dev curl git

# Initial env variable for vcpkg path
ENV VCPKG_ROOT="/usr/local/vcpkg"
ENV PATH="${PATH}:${VCPKG_ROOT}"

# Install vcpkg
RUN git clone --depth 1 https://github.com/microsoft/vcpkg ${VCPKG_ROOT} \
    && ${VCPKG_ROOT}/bootstrap-vcpkg.sh

ENV NXDK_DIR=/workspaces/nxdk

# Include missing path to nxdk's bin directory.
ENV PATH="${NXDK_DIR}/bin:${PATH}"
