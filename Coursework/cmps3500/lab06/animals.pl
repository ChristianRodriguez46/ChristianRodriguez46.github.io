/* animals.pl
 * demonstrate Prolog's inference engine
 *  $ prolog
 *  ?- [animals].    <- execute queries after file is loaded
 *  ?- halt.
 */

/*********************************************************************/
/*                ANIMAL INFERENCE ENGINE                            */
/*********************************************************************/
%
% This example demonstrates Prolog's inference engine through logical
% arguments and logical fallacies in propositional logic.
%
% The universe of discourse is the set containing specific types of animals: 
%       U = {dolphin,crow,dragon,shark} 
% The predicates are general attributes or classifications of animals: 
% breathes(X), fish(X), reptile(X)... 
%
% In a Prolog rule the antecedent and consequence are reversed.
% Thus, this implication
%       "If an animal produces milk for its young then it is a mammal."
% in Prolog is:
%        mammal(X) :- milk(X).
%
% Test the conclusion of each argument a Prolog query. Enter the query at the
% interactive console.
%
% If the argument is valid Prolog will respond 'yes.'
% If the argument is a fallacy Prolog will respond 'no.'
%
% When completed you should be able to run these queries to test your code: 
% ?- breathes(dolphin).  yes 
% ?- bird(crow).         yes 
% ?- reptile(dragon).    yes 
% ?- amphibian(dragon).  no
% ?- fish(shark).        no
%
% NOTES: do not put dashes in predicate names. 
% Predicates not shown to be true are assumed false.
/******************************/
/*   Hypothetical Syllogism:  */
/******************************/
%
%  p -> q  
%  q -> r  
% ----------
% : p -> r
%
% ARGUMENT:
% If an animal produces milk for its young it is a mammal.
% If an animal is a mammal it is warmblooded.  (don't use a dash)
% If an animal is warmblooded it breathes.
% A dolphin produces milk for its young.
% Therefore: A dolphin breathes.  <= this query should return YES
% ?- breathes(dolphin).

mammal(X) :- milk(X). 
breathes(pig).
breathes(X) :- warm(X).
warm(X) :- mammal(X).
milk(dolphin).

/******************************/
/*         Modus Ponens       */
/******************************/
%
%   p -> q  
%   p  
% ----------
% :  q
%
% ARGUMENT:
% An animal is a bird if it has feathers.
% A crow has feathers.
% Therefore, a crow is a bird.  
% ?- bird(crow). query should return YES
%
bird(X) :- feathers(X).
feathers(crow).
%
/******************************/
/*   Constructive Dilemma     */	
/******************************/
%
%  (p -> q) ^ (r -> s)  
%   p v r  
% ----------------------
% : q v s
%
% ARGUMENT:
% An animal is a reptile if it is coldblooded. (no dashes in predicate names)
% An animal is an amphibian if it has slimy skin.
% A dragon is cold-blooded or it has slimy skin.
% Therefore: A dragon is a reptile or an amphibian. 
% ?- reptile(dragon).  yes 
% ?- amphibian(dragon). no
%
%
reptile(X) :- cold(X).
amphibian(X) :- slimy(X).
% slimy(dragon) can also be added.
cold(dragon).
% some fact about slimy is needed since prolog is closed-world
slimy(snail).   
%
%
/*************************************************/
/*     Fallacy of affirming the consequence      */
/*************************************************/
% p -> q
% q
% -------
% p        
%
% FALLACY:
% An animal lives in the water if it is a fish.
% Sharks live in the water.
% Therefore: A shark is a fish.   
% ?- fish(shark) <= query should return NO
%
% Note: you need to enter at least one fact about a fish to get this
% query to work, so enter:
% fish(trout).
%
fish(trout).
% 
water(X) :- fish(X).
water(shark).
%
