#riack_++

##Status
Usable but no links, mapredure or 2i yet.

##Requirements
### Riack
Follow the compilation instructions here https://github.com/trifork/riack

#### Linux or mac
When riack is compiled do a 'sudo make install'.

#### Windows
On windows riack need to be placed in  
C:/Development/precompiled-riack  
Headers here:  
C:/Development/precompiled-riack/include  
Library here:  
C:/Development/precompiled-riack/lib  
If this is not what you want you can change the paths in src/cmake/Modules/Findriack.cmake  
This can be made smart I just have not gotten around to it yet (pull request very welcome).

##Compiling
###linux and mac  
move to project folder and do  
cmake src/  
make  

###Windows
In a command prompt move to project folder and do the following if you are using visual studio 10  
cmake src/ -G "Visual Studio 10"  
This will generate a solution file which can be opened and compiled in Visual Studio 10.

##Usage
###Linux or mac
run 'sudo make install'
this should install all headers and lib file.  

Link your project with libriack++.a or .dylib  
Include  
```
<riack++/Client.h>
<riack++/Object.h>
```
and so on as needed.

###Windows
Either pull in all the sources to your project or take the .a/.lib and the headers.

##Examples
Right now there is no examples, but some simple unit tests in src/tests



