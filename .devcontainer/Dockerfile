# My development machines all have nvidia gpus
FROM nvidia/opengl:1.0-glvnd-devel-ubuntu18.04

# Global settings
ENV CMAKE_VERSION=3.17.2

# Configure a SUDO non-root user (no password)
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Set the non-root SUDO user as default user. 
USER $USERNAME

# Pre-requsities and development tools for c++ & magnum.
RUN sudo apt-get update \
    && sudo apt-get install -y software-properties-common \
        unzip wget git \
        build-essential gdb clang clang-format clang-tidy \
        libsdl2-dev


# Install CMake binary
RUN mkdir -p ~/temp \
    && cd ~/temp \
    && wget https://github.com/Kitware/CMake/releases/download/v$CMAKE_VERSION/cmake-$CMAKE_VERSION-Linux-x86_64.sh \
    && sudo mkdir /opt/cmake \
    && sudo sh cmake-$CMAKE_VERSION-Linux-x86_64.sh --prefix=/opt/cmake --skip-license \
    && sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake \
    && cmake --version

# Clean up
RUN sudo rm -r ~/temp \ 
    && sudo apt-get autoremove -y \
    && sudo apt-get clean -y
