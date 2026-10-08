-- dogspa.ada
-- demonstrate use of selection statement 
-- demonstrate selective waits with guards in concurrent tasks 

with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with text_io; use text_io;
with Ada.Numerics.Discrete_Random;
with Ada.Strings.Unbounded;	--these 4 are for unbounded strings.
use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO;
use Ada.Strings.Unbounded.Text_IO;

procedure dogspa is
  
  package TI renames Ada.Strings.Unbounded.Text_IO;--rename packages for
  package SU renames Ada.Strings.Unbounded;	   --easier use in the code
  -- setup framework for a discrete random number generator
  subtype myint is Integer range 1..100;
  package Random_Int is new Ada.Numerics.Discrete_Random (myint);
  use Random_Int;
  G: Generator;                
  myrand:   integer:= 0;
  im_alive: boolean:= true;

  type NAMESARRAY is array (INTEGER range 1..100) of SU.UNBOUNDED_STRING;
  type ARR is array (INTEGER range 1..100) of INTEGER;

  inf: 	    FILE_TYPE;		--reads in the dog name encyclopedia names.txt
  names:    NAMESARRAY;  	--Encyclopedia of names
  randname: INTEGER := 0;	--for randomly choosing dropoffs and pickups
  match:    BOOLEAN := false;	--avoids duplicate dog names
  biter:    BOOLEAN;		--for sending boolean parameter
  i: 	    INTEGER := 1;	--for loops and such
  dogs:     NAMESARRAY;		--holds dogs currently in kennel
  dog_cnt:  INTEGER := 0;	--How many dogs currently in kennel	

  -- setup a task that accepts requests only; i.e., a server
-- ****************************** Kennel task ********************************
  task type Kennel is            
    entry dropoffDog(is_biter: IN Boolean; nm: IN SU.UNBOUNDED_STRING); -- UPDATE THIS LINE
    entry pickupDog(nm: IN SU.UNBOUNDED_STRING);--name
    entry treats;
  end Kennel;

  task body Kennel is

    time2clean:  boolean:= false;
    dirt_level:  integer:= 0;
    OK2add:      boolean:= true;
    MAX_DOG_CNT: integer:= 100; 

  begin
    put_line("Kennel pets-R-us is open for business.....");
    loop                          -- loop continuously waiting for requests
                                   
       select                      -- a selective wait with guards 

          when OK2add =>           -- OK2add is the guard 
	     -- ______________________ dropoffDog _________________________
         -- Update the accept line to have the correct parameters:
          accept dropoffDog(is_biter: IN Boolean; nm: IN SU.UNBOUNDED_STRING) do
              -- Add the logic to check for a biter
              -- Pseudocode:
              --   if biter param is false, then put dog's name in dogs array,
              --       increment dog_cnt, and print a message that dog has
              --       entered the kennel with the dog's name
              --   else, print a message that dog "name" will not be accepted
              --       at the kennel
              --   end-if
              if is_biter = false then
                  dog_cnt := dog_cnt + 1;
                  dogs(dog_cnt) := nm;
                  put("Dog ");
                  put(nm);
                  put_line(" has been put into the kennel.");
              else
                  put("Dog "); put(nm); put_line(" is a biter and will not be accepted at the kennel");
              end if;

	     New_Line;
	     put("     Dog Count: ");
	     put(dog_cnt,3);		--How many dogs are there now?
         New_Line;
         dirt_level := dirt_level + 1;
         if dog_cnt = MAX_DOG_CNT then --100 is the max        
            OK2add:= false;    	-- set guard to false
         end if;
         if dirt_level = 20 then    --cleans every 20 dropoffs     
	        time2clean:= true;
         end if;
         end dropoffDog;
	     --____________________________________________________________

          or 

          when true =>        
	     -- _______________________ pickupDog _________________________
             accept pickupDog(nm: IN SU.UNBOUNDED_STRING)do 
             if dog_cnt > 0 then	--check if there's anyone to pickup
                 put("Pickup  dog: ");
		 put_line(nm);		--nm is the passed name
		 for i in randname..dog_cnt loop
		     dogs(i):=dogs(i+1);--deletes the dog and shifts 
		 end loop;	        	--everything over to the left
                 dog_cnt := dog_cnt - 1;--decrement dog count
		 put("     Dog Count: ");
		 put(dog_cnt,3);
                 put_line("");
             else
                 put("Empty Kennel");  --if there are zero dogs display this
                 put_line("");
             end if;
             end pickupDog;
	     --______________________________________________________________

           or

          when true =>                -- accept treats at any time 
             accept treats; 
             put("TREAT!");
             put_line("");

           or
              terminate;
           
       end select;

       -- cleanup after every 10 dog tasks ??
       if time2clean then      
          put("Time to clean the kennel (");
          put(dog_cnt,3);
          put_line(")");
          time2clean:= false;
          dirt_level:= 0;	--restarts clean counter
       end if;  

    end loop;

    -- code here is never executed

  end Kennel;
  -- *************************************************************************

  petsRus: Kennel;       -- instantiate a Kennel task

begin -- The whole main program pretty much starts here.
  Reset(G);                      -- start the random number generator
  Open(inf, In_File, "names.txt");
  for i in 1..100 loop		 --reads in the names
      exit when END_Of_File(inf);--this is kinda arbitrary
      TI.Get_Line(inf,names(i)); --I renamed it TI up there for unbnded strngs
  end loop;
  New_line;
    
 
   for x in 0..100 loop

     myrand := Random(G);

     case myrand mod 4 is     --  requests are made in this loop 

        when 0 => -- TREATS!!  ---------------------------------
           petsRus.treats;

        when 1 => -- pickupDog ---------------------------------
	   if dog_cnt > 0 then
	       randname := (Random(G) mod dog_cnt)+1;
	   else
	       randname := 1;
	   end if;
           petsRus.pickupDog(dogs(randname));

        when others => -- other/dropoffDog ---------------------
	     -- prepares to send biter and name to dropoffDog
		 i := Random(G) mod 5; --randomly determine if biter
		 if i < 1 then	       --1/5 chance the dog is a biter
		     biter:= true;
		 else
		     biter:= false;
		 end if;
	     loop
		 match:= false;
	         randname := Random(G);--helps choose random name from enclpdia
	         for i in 1..dog_cnt loop
		     if dogs(i) = names(randname) then--avoids duplicates
		         match := true;
		     end if;
	         end loop;
		 exit when match = false;
	     end loop;
         -- Uncomment the following line when you have updated dropoffDog
         -- to take both parameters:
         --
         petsRus.dropoffDog(biter,names(randname));--sends biter & name

     end case;

  end loop;
  new_line;
  put_line("Kennel Closed.");


end dogspa;

