
(* ******************************************** *)
(** Basic functions on finite automata *)
(* ******************************************** *)
(**
   Code stub for assignment 1
*)
(*Author: Himanshu Rana - hrana2*)
(*Date: 2/9/19*)
(*"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana*)

type symbol = char
type input = char list

type state = string

(* transition function *)
type tf = (state * symbol * state) list

(* initial state * transition function * end state *)
type fa = { states: state list; start:state; tf: tf; final: state list}


(* ******************************************** *)
(* Examples of automata *)
(* ******************************************** *)

let a = {states = ["q0";"q1";"q2"];
         start = "q0";
         tf = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")];
         final = ["q2"]}

let a2 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q2"]
         }
let tf_of_a = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")]



(* ******************************************** *)
(* Helper functions *)
(* ******************************************** *)

let input_of_string s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []


(* ******************************************** *)
(* Simulating automata *)
(* ******************************************** *)


(*Function 1*)
(*This function applies the transistion function to a symbol*)
let rec apply_transition_function : tf -> state -> symbol -> state option = fun tf state sym ->
	match tf with 
	| [] -> None
	| (state0, input, state1) :: paths ->
	if sym = input && state0 = state then Some state1
	else apply_transition_function paths state symbol

	
(*Function 2*)
(*This function determines wehter a word is accepted by the finite automaton
by using the transistion function and keeping track of the current state
If the list is empty the the current state becomes the final and if not 
then the function traverses through the list and checks if each letter is 
acceptable if it has a transition function.*)
let accept : fa -> input -> bool = fun fa input ->
	let rec accept_help currstate = function
		| [] -> List.mem currstate fa.final
		| head :: body -> 
		(match apply_transition_function fa.tf currstate first with 
			| Some state -> accept_help state body
			| None -> false)
	in accept_help fa.start input
	

(*Function 3*)
(*This function checks whether the given automaton is non-determinsitic or not*)
let deterministic : fa -> bool = fun fa ->
	let rec deterministic_help tf visited = 
		match tf with
		 | [] -> true
		 | (state1, input, _) :: paths ->
		 	if List.mem (state1, input) visited then false 
		 	else deterministic_help paths ((state1, input) :: seen) 
	in deterministic_help fa.tf []



(*Function 4*)
(*This function checks for validity by making sure three rules are met. This is done 
by the single line and "&&" the three cases together. The cases are that the start state
belongs to set of all states, the final states belong to set of all states and that is is 
deterministic.*)
let valid : fa -> bool = fun fa ->
	let valid_help state = List_mem state fa.states
	in valid_help fa.start && List.for_all valid_help fa.final && deterministic fa


(*Function 5*)
(*This function gives a list of states that are reachable fron the start state.
This is acheived by filtering out all the states that are reachable, using the 
previoulsy defined reachable_hellp function and mapping them together. Once a path
of all reachable states have been found the function goes back to the start and makes 
sures to get the rest of the states avoiding the ones it has already visited.*)
let rec reachable : fa -> state list = fun fa -> 
	let go_back state = 
		fa.tf
		|> List.filter (fun (_,_,state1) -> state1 = state)
		|> List.map (fun (state1, _, _) -> state1) in
	let rec reachable_help state = 
		if state = fa.start then true
	    else let previous = go_back state
			in List.mem state previous || List.exists reachable_help previous
	in List.filter reachable_help fa.states