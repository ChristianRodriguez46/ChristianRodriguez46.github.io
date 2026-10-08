/* family.pl
 * compile and run: 
 *  $ gplc family.pl
 *  $ ./family
 */

% uncomment these prolog commands to execute the 3 queries at the bottom of 
% the file - to test queries leave them commented

% :- initialization(q1).
% :- initialization(q2).
% :- initialization(q3).
% :- initialization(end).

/* BACKGROUND. A prolog program consists of predicate clauses of the form:
 * P_0 := P_1, P_2, P_3 ... P_n, where P_0 is the head of the clause and 1 or
 * more terms to the right of := comprise the body of the clause.
 * A headed clause is a rule: P_0 is true if P_1 ... P_n are true.
 * To show P_0, show P_1 and show P_2 and show P_3 and ... and show P_n
 * A headed Horn claus is a disjunction of literals with one positive literal:
 *     ~p v ~q v ... v ~t v u  
 * which is equivalent to: 
 *     (p ^ q ^ ... ^ t) -> u. <= this form is also called a definite clause
 * A bodyless Horn clause is a fact (empty right hand side).
 * A headless Horn clause is a goal/query clause (empty left hand side).
 *
 * Definite clauses are useful in a logic language because the resolution of a
 * goal clause (a query) and a definite clause (a rule) is again a goal clause.
 *
 * Prolog is based on the closed world assumption - anything that cannot be 
 * proven true is assumed false; i.e., False until proven True.
 *
 * RULES
 * Prolog rules are based on predicate logic - 
 * Variables whose first appearance is on the left hand side of the clause have
 * implicit universal quantifiers.
 * Variables whose first appearance is on the right hand side of the clause
 * have implicit existential quantifiers.
 * The implication is read right to left, where the comma is interpreted as AND
 * The Rule:
 *    teaches(P,S) :- instructor(P,C), enrolled(S,C).
 * is read:
 * "If P is the instructor of class C and S is enrolled in class C then P 
 *  teaches S."
 *
 * To reason about a rule you need some facts. A fact is a bodyless clause
 * that reads left to right. This fact reads: "spade is the instructor of ee300"
 *
 *       instructor(spade,ee300).  
 *
 * Finally, a query starts the inference engine rolling - queries are typed
 * at the interactive command prompt. This query returns all joe's instructors:
 *       % |-? teaches (X, joe).
 *  ----------------------------
 *  Syntax and Technical Issues
 *  ----------------------------
 *  To enter fact into the database interactively use asserta:
 *       % |-?  asserta(parent(chester,irvin)).
 *
 *  Facts and rules are more easily entered from a file.
 *  %|-? [filename].
 *
 *  The order in which facts and rules are listed is mostly irrelevant but 
 *  predicates should be contiguous.
 *
 *  Variables must be uppercase. Do not use dashes in predicate names.
 *
 *  Rules are tested in the order entered (top to bottom). After loading the 
 *  facts and rules, you can run queries in the interactive interpretor.
 *  Queries must end with '.' and cannot have white spaces
 *  hit ';' to continue query
 *  hit [CR] to end query
 *  Prolog wants all facts clumped together - discontiguous error is not good
 */

/*-------------------------------*
 * FAMILY TREE INFERENCE ENGINE  *
 *-------------------------------*/

% FACTS
parent(chester,irvin).
parent(chester,clarence).
parent(chester,mildred).
parent(irvin,ron).
parent(irvin,ken).
parent(clarence,shirley).
parent(clarence,charlie).
parent(mildred,mary).
parent(ken,nora).
parent(ken,elizabeth).

female(shirley).
female(nora).
female(elizabeth).
female(mildred).

male(chester).
male(clarence).
male(ron).
male(ken).
male(charlie).
male(irvin).


% RULES 
% a single rule can make male the default unless explicitly true for female 
% male(X) :- not(female(X)).
% define a NOT function since prolog by nature doesn't use not
% -> if (1st) then (2nd)
not(P) :- (call(P) -> fail ; true).

% "If X is Y's parent AND X is male then X is Y's father." 
father(X,Y):-  parent(X,Y), male(X).

sister(X,Y) :- female(X), female(Y), parent(Z,X), parent(Z,Y), \==(X,Y).

% this rule would be satisfied by "Ron is the sibling of Ron"
% sibling(X,Y) :- parent(Z,X), parent(Z,Y).

% this rule will not return true when X==Y so Bob is not Bob's own sibling
sibling(X,Y):- parent(Z,X), parent(Z,Y), \==(X,Y).

% If X is the parent of Y then X is a close relative of Y.
closeRelative(X,Y) :- parent(X,Y).
closeRelative(X,Y) :- parent(Y,X).
closeRelative(X,Y) :- sibling(X,Y).

ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(X,Z), ancestor(Z,Y).

% replacing the above rule with this rule will cause infinite recursion
% ancestor(X,Y) :- ancestor(Z,Y), parent(X,Z).

% this rule returns Ron is a cousin of Ron 
cousin(X,Y) :- parent(W,X), parent(Z,Y), sibling(W,Z).

% QUERIES
% Queries/goals are entered from the prolog interactive prompt:   |-? 
% After executing a query, press [Return] to end or ; to resume the inference
% engine and display more results.

% Query examples:
% 
% This query is read as "Who is a female?"
% |-? female(X). 

% This query is read as "Is elizabeth a close relative of ken?"
% |-? closeRelative(elizabeth,ken).

% This query can read as "Who are the descendants of irvin?"
% |-? ancestor(irvin,Y).

writeln(T) :- write(T), nl.
end :- writeln('#'), halt.

q1 :- write('parent irvin?'),findall(X,(parent(X,irvin),format('~w ~n',[X])),_).
q2 :- write('sibling irvin?'),findall(X,(sibling(irvin,X),format('~w ',[X])),_).
q3 :- write('sisters?'),findall(X, (sister(X,Y), format('~n~w ~w',[X,Y])),_).
q4 :- write('close relatives? ').
q4 :- findall(X, (closeRelative(X,Y), format('~n~w ~w',[X,Y])),_).
