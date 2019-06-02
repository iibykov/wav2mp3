# wav2mp3
C++ cross-platform wav-mp3 encoder utilising Qt &amp; Lame library &amp; POSIX threads.

## Requirements
*  Qt - https://www.qt.io/download-qt-installer (choose Mingw version). The Qt installation package includes Mingw.
   It is assumed to use this version of Mingw. If for some reason you cannot use Mingw from this package, you need 
   to complete the next step, otherwise skip the next step.
*  MingGW - https://sourceforge.net/projects/mingw/files/Installer/
   *  GCC C++ compiler
   *  MSYS Basic System
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
* pthreads ```mingw-get install pthreads``` (Mingw supplied with Qt already contains pthreads)

*  Compile using `make` 

## Usage
### For Windows
   `wav2mp3.exe C:/PathToWavFiles`
   
### For Linux
   `wav2mp3 /usr/local/pathtowavfiles`
