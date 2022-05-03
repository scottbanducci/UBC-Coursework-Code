% % listify(empty,[]).
% % listify(node(Key,_,LT,RT),List) :-listify(LT,List1), listify(RT,List2), append(List1, [Key|List2],List).

% prefix([], _).
% prefix([A|As], [A|Bs]) :- prefix(As,Bs).

% fnord(A, B) :- prefix(A, B).
% fnord(A, [_|B]) :- fnord(A, B).

% Binary Search Trees Starter Code.


% A BST will be one of:
% + empty
% + node(Key, Value, LeftSubtree, RightSubtree), where 
%     all keys in LeftSubtree are less than Key, and
%     all keys in RightSubtree are greater than Key.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Sample BSTs
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% example_bst("empty", empty).
% example_bst("1 -> a", node(1, a, empty, empty)).
% example_bst("1 -> a, 0 -> b, 2 -> c", 
%     node(1, a,
%         node(0, b, empty, empty),
%         node(2, c, empty, empty))).
% % Same contents as the previous one, but "rotated"
% % to put 0 at the root:
% example_bst("0 -> b, 1 -> a, 2 -> c", 
%     node(0, b, empty,
%         node(1, a, empty, 
%             node(2, c, empty, empty)))).
% % Again, same contents but "rotated" to put 2 at the root.
% example_bst("2 -> c, 1 -> a, 0 -> b", 
%     node(2, c,
%         node(1, a, 
%             node(0, b, empty, empty),
%             empty),
%         empty)).

% % The example from our lecture:
% example_bst("lecture",
%     node(8, a, 
%         node(3, b,
%           node(1, d, empty, empty),
%           node(6, e, 
%             node(4, g, empty, empty),
%             node(7, h, empty, empty))),
%         node(10, c,
%           empty,
%           node(14, f,
%             node(13, i, empty, empty),
%             empty)))).


% in_range(empty,_,_).
% in_range(node(Key,_,LT,RT),Below,Above) :- Key>Below, Key<Above, in_range(LT,Below,Above), in_range(RT,Below,Above).

% out_of_order([],0).
% out_of_order([_],0).
% out_of_order([X,X|Tail],N) :- out_of_order([X|Tail],N).
% out_of_order([X,Y|Tail],N) :- X<Y, out_of_order([Y|Tail],N).
% out_of_order([X,Y|Tail],N) :- X>Y, out_of_order([Y|Tail],M), N is M+1.

vecsum([vec3(X1,Y1,Z1)],vec3(X1,Y1,Z1)).
vecsum([vec3(X1,Y1,Z1)|Tail],vec3(Xsum,Ysum,Zsum)) :- vecsum(Tail,vec3(X,Y,Z)), Xsum is X+X1,Ysum is Y+Y1, Zsum is Z+Z1.