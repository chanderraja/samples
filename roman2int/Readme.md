roman2int
=========
`roman2int` is a utility for converting strings representing Roman numbers into its integral value.

Usage
-----
`roman2int <roman number string>`

E.g. 
*roman2int MCD*
1400

*roman2int MCMLXXXIV*
1984

*roman2int foo*
Invalid Roman number

How to build
------------
	*tar xvzf roman2int.tgz*
	*cd roman2int*
	*make*
	
To build and run the included unit test:
	*make test*
	*./test*
