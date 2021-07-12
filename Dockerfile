# Build image:
# docker build -t doumu-cpp-env -o out/ . > buildLog
#
# Create container:
# docker run --name dmcpp -it doumu-cpp-env bash
FROM archlinux

RUN rm /etc/pacman.d/mirrorlist
RUN echo "# Mirrorlist chosen for Eastern-Asia region" > /etc/pacman.d/mirrorlist
RUN echo "Server = https://ftp.jaist.ac.jp/pub/Linux/ArchLinux/\$repo/os/\$arch" >> /etc/pacman.d/mirrorlist
RUN echo "Server = http://archlinux.ccns.ncku.edu.tw/archlinux/\$repo/os/\$arch" >> /etc/pacman.d/mirrorlist
RUN echo "Server = https://shadow.ind.ntou.edu.tw/archlinux/\$repo/os/\$arch" >> /etc/pacman.d/mirrorlist
RUN pacman -Syyu --noconfirm
# Install Dev Env
RUN pacman -S --needed base-devel git gcc --noconfirm
RUN pacman -S --needed autoconf-archive --noconfirm
RUN pacman -S --needed sagemath --noconfirm
# Add editor
RUN pacman -S vim --noconfirm
RUN ln -s /bin/vim /bin/vi
# Enable globstar
RUN shopt -s globstar
