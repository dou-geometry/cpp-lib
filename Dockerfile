# Build image:
# docker build -t doumu-cuda-env -o out/ . > buildLog
#
# Create container:
# docker run --name dmcuda -it doumu-cuda-env bash
FROM archlinux

RUN rm /etc/pacman.d/mirrorlist
RUN echo "# Mirrorlist chosen for Eastern-Asia region" > /etc/pacman.d/mirrorlist
RUN echo "Server = https://ftp.jaist.ac.jp/pub/Linux/ArchLinux/\$repo/os/\$arch" >> /etc/pacman.d/mirrorlist
RUN echo "Server = http://archlinux.ccns.ncku.edu.tw/archlinux/\$repo/os/\$arch" >> /etc/pacman.d/mirrorlist
RUN echo "Server = https://shadow.ind.ntou.edu.tw/archlinux/\$repo/os/\$arch" >> /etc/pacman.d/mirrorlist
RUN pacman -Syyu --noconfirm
RUN pacman -S sudo shadow --noconfirm
# Create user "user" with sudo permission and without password (for script automation)
RUN useradd -m user -p ''
RUN echo 'user ALL=(ALL) ALL' | EDITOR='tee -a' visudo
# Install Dev Env
RUN pacman -S --needed git gcc --noconfirm
RUN pacman -S --needed sudo --noconfirm
RUN pacman -S --needed nvidia opencl-nvidia cuda --noconfirm
# Setup cuda-gdb
RUN pacman -S --needed base-devel --noconfirm
USER user
WORKDIR /home/user/
RUN git clone https://aur.archlinux.org/ncurses5-compat-libs.git
WORKDIR /home/user/ncurses5-compat-libs/
RUN gpg --keyserver pgp.mit.edu --recv-keys C52048C0C0748FEE227D47A2702353E0F7E48EDB
RUN makepkg -si --noconfirm
USER root
ENV PATH=$PATH:/opt/cuda/bin/
WORKDIR /
# Add editor
RUN pacman -S vim --noconfirm
RUN ln -s /bin/vim /bin/vi
