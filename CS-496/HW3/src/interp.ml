(* Himanshu Rana 
"I pledge my honor that I have abided by the Stevens Honor System - hrana2" *)

open Ast
open Ds
             

let rec apply_proc : exp_val -> exp_val -> exp_val ea_result =
  fun f a ->
  match f with
  | ProcVal (id,body,env) ->
    return env >>+
    extend_env id a >>+
    eval_expr body
  | _ -> error "apply_proc: Not a procVal"
and
 eval_expr : expr -> exp_val ea_result = fun e ->
  match e with
  | Int(n) ->
    return @@ NumVal n
  | Var(id) ->
    apply_env id
  | Add(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return @@ NumVal (n1+n2)
  | Sub(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return @@ NumVal (n1-n2)
  | Mul(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return @@ NumVal (n1*n2)
  | Div(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    if n2==0
    then error "Division by zero"
    else return @@ NumVal (n1/n2)
  | Let(id,def,body) ->
    eval_expr def >>= 
    extend_env id >>+
    eval_expr body 
  | ITE(e1,e2,e3) ->
    eval_expr e1 >>=
    bool_of_boolVal >>= fun b ->
    if b 
    then eval_expr e2
    else eval_expr e3
  | IsZero(e) ->
    eval_expr e >>=
    int_of_numVal >>= fun n ->
    return @@ BoolVal (n = 0)
  | Proc(id,e)  ->
    lookup_env >>= fun en ->
    return (ProcVal(id,e,en))
  | App(e1,e2)  -> 
    eval_expr e1 >>= fun v1 ->
    eval_expr e2 >>= fun v2 ->
    apply_proc v1 v2 
    (* if the number is greater than 0 just return the number 
    otherwise use the absolute value function to take absolute 
    value and return that number *)
  | Abs(e1)      ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    if n1 > 0 
    then return @@ NumVal n1
    else return @@ NumVal (abs n1)
    (* takes a list and cons with whats at the end  *)
  | Cons(e1, e2) ->
    eval_expr e1 >>= fun head -> 
    eval_expr e2 >>= 
    list_of_listVal >>= fun t -> 
    return @@ ListVal(head::t)
    (* returns hte head of a list *)
  | Hd(e1) ->
    eval_expr e1 >>= 
    list_of_listVal >>= fun head -> 
    if head = []
    then error "list is empty"
    else return @@ List.hd head
    

    (* returns the tail of a list *)
  | Tl(e1) ->
    eval_expr e1 >>= 
    list_of_listVal >>= fun tail -> 
    if tail = []
    then error "list is empty"
    else return @@ ListVal(List.tl tail)
    (* checks to see if the list is empty or not 
    returns boolean value true if empty and false if not *)
  | Empty(e1) ->
    eval_expr e1 >>= 
    list_of_listVal >>= fun x -> 
    return @@ BoolVal(x = [])
  | EmptyList -> return @@ ListVal([])
    
  | EmptyTree -> return @@ TreeVal(Empty)
    (* creates a tree with data e1 and left and right 
    subtress of e2 and e3 *)
  | Node(e1,lte,rte) ->
    eval_expr e1 >>= fun n -> 
    eval_expr lte >>= 
    tree_of_treeVal >>= fun lt -> 
    eval_expr rte >>= 
    tree_of_treeVal >>= fun rt -> 
    return @@ TreeVal(Node(n, lt, rt))
  | CaseT(target,emptycase,id1,id2,id3,nodecase) ->
    eval_expr target >>= 
    tree_of_treeVal >>= fun x -> 
    match x with 
    | Ds.Empty -> eval_expr emptycase
    | Ds.Node(x, lt, rt) -> 
    extend_env id1 x >>+
    extend_env id2 (TreeVal lt) >>+
    extend_env id3 (TreeVal rt) >>+
    eval_expr nodecase
    (* error "implement" *)
and
  eval_prog (AProg e) = eval_expr e

(***********************************************************************)
(* Everything above this is essentially the same as we saw in lecture. *)
(***********************************************************************)

(* Parse a string into an ast *)

let parse s =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast

let lexer s =
  let lexbuf = Lexing.from_string s
  in Lexer.read lexbuf 


(* Interpret an expression *)
let interp (e:string) : exp_val result =
  let c = e |> parse |> eval_prog
  in run c



