
(* ******************************************** *)
(** Basic functions on finite automata *)
(* ******************************************** *)
(**
   Code stub for assignment 1
*)

(*Author: Himanshu Rana - hrana2*)
(*Date: 2/9/20*)
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

 
(*This function applies the transistion function to a symbol*)   
let rec apply_transition_function : tf -> state -> symbol -> state option = fun tf state sym ->
  match tf with 
  | [] -> None
  | (state0, input, state1) :: paths ->
  if sym = input && state0 = state then Some state1
  else apply_transition_function paths state sym

(*Determines whether a word if accepted by a fa*)
let rec accept fa input =
  let rec accept_help state input =
    match input with
    | [] -> state
    | h::t ->
      (*checks to see if a letter is used in a transistion function*)
      match state with
      | Some x -> accept_help (apply_transition_function fa.tf x h) t
      | None -> None
  (*checks to see if the beginning of the word is part of that start state
  and if the last letter is in the final state*)    
  in match accept_help(Some fa.start) input with
  | None -> false
  | Some state -> List.mem state fa.final

(*next returns the list of all states after a given state and symbol*)
let rec next tf state symbol =
  match tf with
  | [] -> []
  | (x,y,z)::tf' ->
    (*gets the next state and symbol after the given input*)
    if x = state && y = symbol
    then z::next tf' state symbol
    else next tf' state symbol

(*Deterministic function that uses a helper to check if a given fa is true or false*)
let rec deterministic fa =
  let rec deterministic_help = function
    | [] -> true
    | (x,y,z) :: tf ->
      match next tf x y with
      | [] -> deterministic_help tf
      | _ -> false
  in deterministic_help fa.tf

(*checks to see if a given fa is valid or not and returns 
a boolean accordingly*)
let rec valid fa =
  let curr_state state = List.mem state fa.states
  (*checking to see of the start state and final state belong in the set of 
  all states and seeing if the fa is deterministic*)
  in curr_state fa.start && List.for_all curr_state fa.final && deterministic fa


(*returns a list of all states that are reachable from the start state*)
(*this is done by filitering out all the reachable states and mapping them 
together. once a path is complete it goes back to the start and repeats*)
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


(*helps to remove all the dead states*)
let rec removes_state state state1 =
  match state with
  | [] -> []
  | h::t ->
    (*if the dead state belongs to the set of states 
    remove and go to the next state, otherwise just remove 
    the dead state*)
    if List.mem h state1
    then h::removes_state t state1
    else removes_state t state1

(*helps to remove all the transistion functions involved 
with dead states*)
let rec removes_tf tf state1 =
  match tf with
  | [] -> []
  | (x,y,z)::tf' ->
    (*if the dead state is in the set then remove its transition function*)
    if List.mem x state1
    then (x,y,z)::removes_tf tf' state1
    else removes_tf tf' state1

(*returns an fa with all the dead states removed 
including the set of states, transitions and set 
of final states*)
  let rec remove_dead_states fa =
  (*only worrying about states that are reachable*)
  let state1 = reachable fa in
  (*setting each of the states, start and final, and tf with 
  the removed dead ones*)
  {
    states = state1;
    tf = remove_tf fa.tf state1;
    start = fa.start;
    final = remove_state fa.final state1;
  }