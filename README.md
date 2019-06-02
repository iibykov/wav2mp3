# wav2mp3
C++ cross-platform wav-mp3 encoder utilising Qt &amp; Lame library &amp; POSIX threads.

## Requirements
*  Qt - https://www.qt.io/download-qt-installer (choose Mingw version). The Qt installation package includes Mingw.
   It is assumed to use this version of Mingw. If for some reason you cannot use Mingw from this package, you need 
   to complete the next step, otherwise skip the next step.
*  MingGW - https://sourceforge.net/projects/mingw/files/Installer/
   *  GCC C++ compiler
   *  MSYS Basic System or MSYS2 (https://github.com/orlp/dev-on-windows/wiki/Installing-GCC--&-MSYS2)
   *  MinGW Developer Toolkit
   *  MinGW-get
   Open a MinGW shell and install the following:
   ```
	 mingw-get install gcc
	 mingw-get install mingw-utils
	 ```

*  LAME encoder source files (https://sourceforge.net/projects/lame/files/lame/).
   Go to extract folder and run the following commands:
     ```
     ./configure --prefix=/mingw --disable-shared --enable-nasm --enable-static
     make
     make install
     ```
     Note: If there is a langinfo.h error, go to http://blog.k-tai-douga.com/article/35965219.html and use lame-3.100-parse_c.diff
     ```
     patch -p1 < lame-3.100-parse_c.diff
     ```
     
* pthreads ```mingw-get install pthreads``` (Mingw supplied with Qt already contains pthreads)

*  Compile using `make` 

## Usage
### For Windows
   `wav2mp3.exe C:/PathToWavFiles`
   
### For Linux
   `wav2mp3 /usr/local/pathtowavfiles`

## Notes
By default (unless additional parameters are specified) application encodes WAV files to mono, 44,100 Hz MP3 files and saves the encoded files into the same user-defined directory.
