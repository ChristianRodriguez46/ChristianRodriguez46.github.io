% Facts
fact(a).
fact(b).
fact(c).
fact(d).
fact(e).

% Rules
rule(z) :- rule(y), fact(d).
rule(y) :- rule(x), fact(b), fact(e).
rule(x) :- fact(a).
rule(l) :- fact(c).
rule(n) :- fact(l), fact(m).