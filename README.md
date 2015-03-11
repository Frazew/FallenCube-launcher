# FallenCube Native Launcher
##whoami
The FallenCube native launcher is basically just a little Qt5 application inspired by the new Minecraft launcher which downloads a custom jre/jdk based on the system and keeps the FallenCube launcher up-to-date. It is a work in progress for now. I guess it doesn't really have any particular interest but hey, I like open source and so do you, right ?
##Who is making this ?
I'm Frazew, developper for FallenCube, if you want to contact me, just feel free to send a message to frazew@fallencube.fr, I'm also @Frazew on Twitter !
##How do I build this thing ?
For now, it has only been tested on Windows and isn't yet planned for Linux (And even less for OSX !). In order to build, clone the repository and install Qt5. The best way to compile it is to import the .pro into QtCreator but you could use qmake manually though !
##Hey ! I get tons of DLLs missing !
That is because Qt needs all its libraries in order to work. If you want, you can distribute the DLLs alongside with the executable but the best is to follow [this guide](http://qt-project.org/wiki/How-to-build-a-static-Qt-for-Windows-MinGW) in order to compile Qt in static mode which will then allow you to pack the libraries into the executable.
##What about licensing ?
This program is licensed under the GNU GPL and respects Qt's licensing conditions, please be sure to do the same if you ever build something upon it !
##What's FallenCube ?
[This is FallenCube !](http://fallencube.fr) (Warning, french incoming !)
