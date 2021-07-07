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
RUN pacman -S --needed git gcc --noconfirm
#Add editor
RUN pacman -S vim --noconfirm
# launch bash by default?
RUN bash
