# Makefile: 
#        It uses the GNU C++ Compiler with debugging
#        will create a single executable called 'lab01'
# ---------------------------------------------------------------
# the compiler
CPP = gfortran
# compiler flags
CFLAGS = -Wall -std=legacy
# this linker flag will link in the math library libm.a 
LFLAGS = 
#
RM = rm -f
# ----------------------------------------------------------------
# Explanation of macros:
#     $< is any dependent file which is out of file1
#     $@ is the target's fullname
#
# add suffix .cpp since it is not a default with make utility 
.SUFFIXES:	.f .o
#

TARGET = circle array1 array2 array3

# dependencies 
#
default:	${TARGET}
#
circle:		circleinput.f 
	${CPP} -o circle circleinput.f

array1:		array1.f
	${CPP} -o array1 array1.f

array2:		array2.f
	${CPP} -o array2 array2.f

array3:		array3.f
	${CPP} -o array3 array3.f

#
clean:
	${RM} ${TARGET} 

