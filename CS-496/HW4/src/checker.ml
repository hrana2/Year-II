(* Himanshu Rana  *)
(* "I pledge my honor that I have abided by the Stevens Honor System" - hrana2 *)
open Ast
open ReM
open Dst


let rec type_of_expr : expr -> texpr tea_result = function 
  | Int _n -> return IntType
  | Var id -> apply_tenv id
  | IsZero(e) ->
    type_of_expr e >>= fun t ->
    if t=IntType
    then return BoolType
    else error "isZero: expected argument of type int"
  | Add(e1,e2) | Sub(e1,e2) | Mul(e1,e2)| Div(e1,e2) ->
    type_of_expr e1 >>= fun t1 ->
    type_of_expr e2 >>= fun t2 ->
    if (t1=IntType && t2=IntType)
    then return IntType
    else error "arith: arguments must be ints"
  | ITE(e1,e2,e3) ->
    type_of_expr e1 >>= fun t1 ->
    type_of_expr e2 >>= fun t2 ->
    type_of_expr e3 >>= fun t3 ->
    if (t1=BoolType && t2=t3)
    then return t2
    else error "ITE: condition not boolean or types of then and else do not match"
  | Let(id,e,body) ->
    type_of_expr e >>= fun t ->
    extend_tenv id t >>+
    type_of_expr body
  | Proc(var,t1,e) ->
    extend_tenv var t1 >>+
    type_of_expr e >>= fun t2 ->
    return @@ FuncType(t1,t2)
  | App(e1,e2) ->
    type_of_expr e1 >>=
    pair_of_funcType "app: " >>= fun (t1,t2) ->
    type_of_expr e2 >>= fun t3 ->
    if t1=t3
    then return t2
    else error "app: type of argument incorrect"
  | Letrec(id,param,tParam,tRes,body,target) ->
    extend_tenv id (FuncType(tParam,tRes)) >>+
    (extend_tenv param tParam >>+
     type_of_expr body >>= fun t ->
     if t=tRes 
     then type_of_expr target
     else error
         "LetRec: Type of recursive function does not match
declaration")
    
  (* pairs *)
  | Pair(e1,e2) ->
    type_of_expr e1 >>= fun s -> 
    type_of_expr e2 >>= fun t -> 
    return @@ PairType(s,t)
  | Unpair(id1,id2,e1,e2) ->
    type_of_expr e1 >>= 
    pair_of_pairType "unpair: " >>= fun (s, r) -> 
    extend_tenv id1 s >>+
    extend_tenv id2 r >>+
    type_of_expr e2 
      
      
  (* references *)
  | BeginEnd(es) ->
    List.fold_left (fun r e -> r >>= fun _ -> type_of_expr e) (return UnitType) es 
  | NewRef(e) ->
    type_of_expr e >>= fun s -> 
    return @@ RefType(s)
  | DeRef(e) ->
    type_of_expr e >>= 
    arg_of_refType "deref: " >>= fun t -> 
    if RefType(t) = t
    then error "deref: Expected a reference type"
  else return t
    
  | SetRef(e1,e2) ->
    type_of_expr e1 >>= fun t1 -> 
    type_of_expr e2 >>= fun t2 -> 
    if t1 = RefType(t2)
    then return @@ UnitType
  else error "setref: Expected a reference type"
 
  (* lists *)
  | EmptyList(t) -> return @@ ListType(t) 
  (* cons two expressions together and making sure they the same types  *)
  | Cons(h, t) ->
    type_of_expr h >>= fun t1 -> 
    type_of_expr t >>= fun t2 -> 
    if ListType(t1) = t2 
    then return @@ t2 
  else error "cons: type of head and tail do not match"
    
  | Null(e) ->
    type_of_expr e >>= fun t -> 
    if ListType(t) = t
    then error "null: expected a ListType"
  else return BoolType
  | Hd(e) ->
    type_of_expr e >>=
    arg_of_listType "hd: " >>= fun t -> 
    if ListType(t) = t
    then error "head: expected a ListType"
    else return t
  | Tl(e) ->
    type_of_expr e >>= fun t -> 
    if ListType(t) = t
    then error "tail: expected a ListType"
  else return @@ t
    


  (* trees *)
  | EmptyTree(t) -> return @@ TreeType(t) 
  | Node(de, le, re) ->
    type_of_expr de >>= fun dt -> 
    type_of_expr le >>= fun lt -> 
    type_of_expr re >>= fun rt -> 
    if TreeType(dt) = rt && TreeType(dt) = lt
    then return @@ TreeType(dt)
  else error "left and right types no match"
  (* checks to see if the given expression is null and that its a TreeType *)
  | NullT(t) ->
    type_of_expr t >>= 
    arg_of_treeType "nullt: " >>= fun t1 -> 
    if TreeType(t1) = t1
    then error "nullT: expected a TreeType"
  else return @@ BoolType

  | GetData(t) ->
    type_of_expr t >>= 
    arg_of_treeType "getdata: " >>= fun t1 -> 
    if TreeType(t1) = t1
    then error "getdata: expected a TreeType"
    else return @@ t1

  (* gets the left subtree of the expression and makes sure 
  its of TreeType *)
  | GetLST(t) ->
    type_of_expr t >>= fun t1 -> 
    if TreeType(t1) = t1
    then error "getlst: expected a TreeType"
  else return @@ t1
  (* gets right subtree and makes sure its of TreeType *)
  | GetRST(t) ->
    type_of_expr t >>= fun t1 -> 
    if TreeType(t1) = t1
    then error "getrst: expected a TreeType"
  else return @@ t1

  | Debug(_e) ->
    string_of_tenv >>= fun str ->
    print_endline str;
    error "Debug: reached breakpoint"
  | _ -> error "type_of_expr: implement"    

let type_of_prog (AProg e) =  type_of_expr e



let parse s =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast


(* Type-check an expression *)
let chk (e:string) : texpr result =
  let c = e |> parse |> type_of_prog
  in run_teac c

let chkpp (e:string) : string result =
  let c = e |> parse |> type_of_prog
  in run_teac (c >>= fun t -> return @@ Ast.string_of_texpr t)


let ex1 = "
let x = 7  
in let y = 2 
   in let y = let x = x-1 
              in x-y 
      in (x-8)- y"

let ex2 = "
   let g = 
      let counter = 0 
      in proc(d:int) {
         begin 
           set counter = counter+1; 
           counter
         end
         }
   in (g 11)-(g 22)"

let ex3 = "
  let g = 
     let counter = newref(0) 
     in proc (d:int) {
         begin
          setref(counter, deref(counter)+1);
          deref(counter)
         end
       }
  in (g 11) - (g 22)"

let ex4 = "
   let g = 
      let counter = 0 
      in proc(d:int) {
         begin 
           set counter = counter+1; 
           counter
         end
         }
   in (proc (x:int) { x + x }
(g 0))"
(* 3 in call-by-name *)
(* 2 in call-by-need *)

let ex5 = "
let a = 3
in let p = proc(x) { set x = 4 }
in begin 
         (p a); 
         a 
       end"

let ex6 = "let p = proc(x:int) { 5-x } in (p 3)"
(* 2 *)

let ex7 = "
let a = 3
in let f = proc(x:int) { proc(y:int) { set x = x-y }}
in begin
((f a) 2);
a
end"
(* 1 *)

let ex8 = "
let swap = proc (x:int) { proc (y:int) {
                      let temp = x
                      in begin 
                          set x = y;
                          set y = temp
                         end
                      } 
            }
         in let a = 33
         in let b = 44
         in begin
             ((swap a) b);
             a-b
            end"
(* 11 *)

let ex9 = "
letrec fact (x) = if zero?(x) then 1 else x*(fact (x-1)) 
in (fact 7)"
(* 5040 *)

let ex10 = "
letrec infiniteLoop (x) = (infiniteLoop (x+1)) 
in let f = proc (z) { 11 }
in (f (infiniteLoop 0))"

