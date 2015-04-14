#Opencv Projects

This repository contains project based on opencv.

These programs can be compiled in a general proupose computer or in raspberry pi. Inside the code there are #ifdefines that determine architecture.

## Makefile

This makefile include all necesary for compiling. The syntax you use is:

make name_of_program

## object_tracking.cpp

This program permit tracking a object with a determined color.

Part of this code is based in the post http://opencv-srf.blogspot.com.es/2010/09/object-detection-using-color-seperation.html.

###The possible colors to follow are:

- Orange -o
- Yellow -y
- Green  -g
- Blue   -b
- Violet -v
- Red    -r

###Compiling the program
	make object_tracking
	
	generate a binary file called object_tracking.

###Run the program
	
	./object_tracking

You can include the flag for following determiden color object.

### Help of this program

	./object_tracking -h

## Licence MIT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.	
