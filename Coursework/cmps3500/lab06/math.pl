% math.pl
% use various math operators


% integer division
idiv(X,Y,R) :- Y>0, R is X // Y.

% Examples of Prolog arithmetic operations using recursion
% =========================================================================
% Predicate to return the factorial where
%   fac(0) =	1
%   fac(n) =	n*fac(n-1), when n>0 

fac(0,1). 

fac(N,R) :-  N>0, N1 is N-1, fac(N1,F1), R is N * F1.

% test with: fac(5,X).

% =========================================================================
/* return the exponential where
  X^0 is 1
  X^1 is X 
  X^N is X * X^N-1  */

power( X, 0, R ) :- X, R is 1.
power( X, 1, R ) :- R is X.  
power( X, N, R ) :- N2 is N - 1, power( X, N2, R2 ), R is X * R2.

% test with: power(10,2,X).
% =========================================================================
/* will be satisfied if R is an integer sqrt of X */

sqrt(X,R) :- X >= 4, N is X//2, isSqrt(X,N,R).
isSqrt(X,N,R) :- X1 is N*N, X=X1, R is N; N>2, N2 is N-1, isSqrt(X,N2,R).

% =========================================================================
/* will display the counting numbers from X down to 1 */
% show(X) :- X > 0, write(X), X2 is X-1, show(X2).
show(X) :- write(X), X2 is X-1, show(X2), X>0.
% =========================================================================
/* Euclid's algorithm to calculate greatest common divisor of two numbers:
gcd(X,Y) = X, when X=Y
gcd(X-Y,Y), when X>Y
gcd(X,Y-X), when Y>X */

gcd(X,Y,R) :- X = Y, R is X.
gcd(X,Y,R) :- X > Y,  X1 is X-Y, gcd(X1,Y,R). 
gcd(X,Y,R) :- Y > X,  Y1 is Y-X, gcd(X,Y1,R). 

% test with: gcd(38,10,X).

% =========================================================================
/* return the Fibonacci number where
 fib(0) = 1
 fib(1) = 1
 fib(n) = fib(n-1)+fib(n-2), for n>1   */

/* this would also work for trivial cases 
fib(0,1).
fib(1,1). */

fib(N,R) :- N = 0, R is 1.
fib(N,R) :- N = 1, R is 1.
fib(N,R) :- N > 1, T1 is N - 1, T2 is N-2, fib(T1,R1), fib(T2,R2), R is R1 + R2.

% test with: fib(7,X).

% =========================================================================
% Towers of Hanoi - 3 towers - A,B,C

move(A,B) :-
   nl, write('Move top disc from '),
   write(A), write(' to '), write(B).

towers(1,A,B,C) :- move(A,B).

% Recursive case - N discs
towers(N,A,B,C) :-
    M is N-1, 
    towers(M,A,C,B),  % Transfer topmost N-1 discs from A to I
    move(A,B),        % Move biggest disc from A to B
    towers(M,C,B,A).  % Transfer remaining N-1 discs from I to B

% Test with:   towers(3,t1,t2,t3).

% =========================================================================
