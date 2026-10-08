/* Here is a Prolog version of the animal identification game (simple expert system) 
        presented in a Lisp program in Chapter 6 of Winston and Horn (1985). 
Load the file and pose the query ?- go. 
The program uses its identification rules to determine the animal that you have chosen. 

https://www.cpp.edu/~jrfisher/www/prolog_tutorial/2_17.html

/* MEDIA ADVISOR Expert System 
   Determines the best training medium based on user responses.
   Start with ?- go.
*/

go :- hypothesize(Medium),
      write('The best training medium is: '),
      write(Medium),
      nl,
      undo.

/* Hypotheses to be tested */
hypothesize(workshop)      :- workshop, !.
hypothesize(lecture)       :- lecture, !.
hypothesize(videocassette) :- videocassette, !.
hypothesize(role_play)     :- role_play, !.
hypothesize(unknown). /* No suitable medium found */

/* Medium selection rules */
workshop :-
    stimulus_situation(physical_object),
    stimulus_response(hands_on),
    verify(feedback_required), !.

lecture :-
    stimulus_situation(visual),
    stimulus_response(analytical),
    verify(feedback_required), !.

lecture :-
    stimulus_situation(visual),
    stimulus_response(oral),
    verify(feedback_required), !.

lecture :-
    stimulus_situation(verbal),
    stimulus_response(analytical),
    verify(feedback_required), !.

role_play :-
    stimulus_situation(verbal),
    stimulus_response(oral),
    verify(feedback_required), !.

videocassette :-
    stimulus_situation(visual),
    stimulus_response(documented),
    verify(feedback_not_required), !.

/* Classification rules */
stimulus_situation(verbal) :-
    verify(environment_papers), !.
stimulus_situation(verbal) :-
    verify(environment_manuals), !.
stimulus_situation(verbal) :-
    verify(environment_documents), !.
stimulus_situation(verbal) :-
    verify(environment_textbooks), !.

stimulus_situation(visual) :-
    verify(environment_pictures), !.
stimulus_situation(visual) :-
    verify(environment_illustrations), !.
stimulus_situation(visual) :-
    verify(environment_photographs), !.
stimulus_situation(visual) :-
    verify(environment_diagrams), !.

stimulus_situation(physical_object) :-
    verify(environment_machines), !.
stimulus_situation(physical_object) :-
    verify(environment_buildings), !.
stimulus_situation(physical_object) :-
    verify(environment_tools), !.

stimulus_situation(symbolic) :-
    verify(environment_numbers), !.
stimulus_situation(symbolic) :-
    verify(environment_formulas), !.
stimulus_situation(symbolic) :-
    verify(environment_computer_programs), !.

stimulus_response(oral) :-
    verify(job_lecture), !.
stimulus_response(oral) :-
    verify(job_advising), !.
stimulus_response(oral) :-
    verify(job_counselling), !.

stimulus_response(hands_on) :-
    verify(job_building), !.
stimulus_response(hands_on) :-
    verify(job_repairing), !.
stimulus_response(hands_on) :-
    verify(job_troubleshooting), !.

stimulus_response(documented) :-
    verify(job_writing),  !.
stimulus_response(documented) :-
    verify(job_typing), !.
stimulus_response(documented) :-
    verify(job_drawing), !.

stimulus_response(analytical) :-
    verify(job_evaluating), !.
stimulus_response(analytical) :-
    verify(job_reasoning), !.
stimulus_response(analytical) :-
    verify(job_investigating), !.

/* how to ask questions */
ask(Question) :-
    write('Does the medium have the following attribute: '),
    write(Question),
    write('? '),
    read(Response),
    nl,
    ( (Response == yes ; Response == y)
      ->
       assert(yes(Question)) ;
       assert(no(Question)), fail).

:- dynamic yes/1,no/1.

/* How to verify something */
verify(S) :-
   (yes(S) 
    ->
    true ;
    (no(S)
     ->
     fail ;
     ask(S))).

/* undo all yes/no assertions */
undo :- retract(yes(_)),fail. 
undo :- retract(no(_)),fail.
undo.