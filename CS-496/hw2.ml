(*Himanshu Rana - hrana2*)
(*2/16/20*)

(*"I pledge my honor that I have abided by the Stevens Honor System" - hrana2*)


type dTree = Leaf of int | Node of char*dTree*dTree

(*creating two trees that represent Figure 1*)
let tLeft = Node('w',Node('x',Leaf(2),Leaf(5)),Leaf(8))
let tRight = Node('w',Node('x',Leaf(2),Leaf(5)),Node('y',Leaf(7),Leaf(5)))


(*This function returns the height of a dTree*)
let rec dTree_height : dTree -> int = fun t ->
	match t with
	(*if the tree is just a leaf then return 0*)
	|Leaf(x) -> 0 
	(*else find the height of left and right tree 
	then find the max of those plus 1, for the root*)
	|Node(_, left, right) ->  
		let l_height = dTree_height left in 
		let r_height = dTree_height right in 
		1 + max l_height r_height


(*This function returns the size of a dTree
size = the number of nodes and leaves*)
let rec dTree_size : dTree -> int = fun t ->
	match t with
	(*if tree only has one leaf return 1*)
	|Leaf(x) -> 1
	(*else take the size of the left and right tree plus 1 for the root*)
	|Node(_,left,right) -> 1 + dTree_size left + dTree_size right


(*This function returns the path of a dTree
A path is a list of the set {0,1} that will lead to a leaf*)
let rec dTree_paths p = 
	let zeros_path list_paths = 
		0::list_paths in 
	let ones_path list_paths = 
		1::list_paths in 
		match p with 
		(*if tree only has a leaf return a list of an empty list*)
		|Leaf(x) -> [[]]
		(*else map the zeros path of the left and the ones path of the right*)
		|Node(_, left, right) -> (List.map zeros_path (dTree_paths left)) @ (List.map ones_path (dTree_paths right))
	

(*This function checks to see if a tree is perfect or not*)

let rec dTree_is_perfect : dTree -> bool = fun t -> 
	match t with
	(*if tree only has one leaf then its perfect*)
	|Leaf(x) -> true
	(*else check to see if the height of the left and right side are equal 
	and if that true then check if both side are perfect else return false*)
	|Node(_,left,right) -> if dTree_height left = dTree_height right
						then dTree_is_perfect left && dTree_is_perfect right
						else false


(*(char -> char) -> (int -> int) -> dTree -> dTree*)
(*This function applies a function f to all the chars 
and a function g to all the numbers in each leaf  *)
let rec dTree_map f g t = 
	match t with 
	(*if tree only has one leaf return tree with g applied*)
	|Leaf(x) -> Leaf(g x)
	(*else apply f and g to both left and right sides of tree*)
	|Node(c, left, right) -> Node(f c, dTree_map f g left, dTree_map f g right)


(*This function creates a tree with all of its leaves set to 0*)
let rec list_to_tree : char list -> dTree = fun l -> 
	match l with 
	(*empty list return leaf of 0*)
	|[] -> Leaf(0)
	(*else traverse list and apply to tail*)
	|h::t -> Node(h, list_to_tree t, list_to_tree t)



(*dTree -> (int list * int) list -> dTree = <fun>*)
(*This function replaces all the leaves in a tree with the values 
given by the graph of a function f.*)
let rec replace_leaf_at t f = 
	let rec replace_helper t r value = 
	match r with 
	(*if list is empty return leaf of value*)
	|[] -> Leaf(value)
	(*else traverse list *)
	|x::xs -> 
		match t with 
		|Node(i, left, right) -> 
			(*if the current head is 0 then replace tail with value on left side
			else do it for the right side*)
			if x = 0
			then Node(i, replace_helper left xs value, right)
		else Node(i, left, replace_helper right xs value)
		|_ -> failwith "Error, something went wrong."
	in match f with 
	(*if list is empty then return tree*)
	|[] -> t 
	|(x,y)::xs -> replace_leaf_at (replace_helper t x y) xs 



(*char list * (int list * int) list -> dTree = <fun>*)
(*This function returns a tree-encoding 
of a pair-encoding of a boolean function *)
let bf_to_dTree (l, t) =
	replace_leaf_at (list_to_tree l) t
