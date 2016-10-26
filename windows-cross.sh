#!/usr/bin/env bash

BOLD=$(tput bold)
NORM=$(tput sgr0)

DEST=kuma-windows
X86_64BINDIR=/usr/x86_64-w64-mingw32/bin
I686BINDIR=/usr/i686-w64-mingw32/bin
X86DLLS=(SDL2 SDL2_image SDL2_ttf libfreetype-6 libbz2-1 liblzma-5 libtiff-5 libjpeg-8 libpng16-16 libwebp-6 zlib1 libstdc++-6 libgcc_s_seh-1 lua53 libwinpthread-1)
I686DLLS=(SDL2 SDL2_image SDL2_ttf libfreetype-6 libbz2-1 liblzma-5 libtiff-5 libjpeg-8 libpng16-16 libwebp-6 zlib1 libstdc++-6 libgcc_s_sjlj-1 lua53 libwinpthread-1)

run_make() {

	if [[ $1 == "x86_64" ]] ; then
		make -f Makefile-windows-x86_64 -j12
	elif [[ $1 == "i686" ]] ; then
		make -f Makefile-windows-i686 -j12
	else
		echo "${BOLD}Expected arg 'x86_64' or 'i686'${NORM}"
	fi
}

clean() {
	make clean
}

tar_the_turd() {
	mkdir -p kuma-windows
	cp -r kuma src res kuma-windows
	if [[ $1 == "x86_64" ]] ; then
		for item in ${X86DLLS[@]} ; do
			cp -v $X86_64BINDIR/$item.dll $DEST
		done
	elif [[ $1 == "i686" ]] ; then
		for item in ${I686DLLS[@]} ; do
			cp -v $I686BINDIR/$item.dll $DEST
		done
	else
		echo "${BOLD}Expected arg 'x86_64' or 'i686'${NORM}"
	fi
	tar cf kuma-windows.tar.gz kuma-windows
}

send_to_space() {
	scp kuma-windows.tar.gz $1:
}

help_print() {
	echo -e "${BOLD}windows-cross.sh\nOPTIONS:${NORM}
\t-s URL\tCopy destination to server via 'scp' where URL is the url of the remote server
\t-m ARCH\tBuild for ARCH where ARCH is either 'x86_64' or 'i686'
\t-c\tClean"
}

while getopts "s:m:ch" option ; do
	case $option in
		h)
			help_print
			;;
		c)
			clean
			;;
		m)
			run_make $OPTARG
			tar_the_turd $OPTARG
			;;
		s)
			send_to_space $OPTARG
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			;;
	esac
done
