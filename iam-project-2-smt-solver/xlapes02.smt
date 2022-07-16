; author Zdenek Lapes <xlapes02>

; run with
;   $ z3 -smt2 xlapes02.smt

; declare the sorts of pos --- pos represents the chessboard (an 8x8 array) ,
; indexed by "(pos row column)":
; true  --- a queen is on [row, column]
; false --- a queen is not on [row, column]
(declare-fun pos (Int Int) Bool)

; a helper function that checks that 1 <= x <= 8
(define-fun is-in-range ((x Int)) Bool 
	(and 
		(> x 0) 
		(<= x 8)
	)
)

; first, we say that in all rows, there is at least one queen 
(assert 
	(forall ((i Int)) 
		(=> 
			(is-in-range i) 
			(exists ((j Int)) 
				(and 
					(is-in-range j) 
					(pos i j)
				)
			)
		)
	)
)

; second, we say that if a queen is on [k; l], 
; then there is no queen on any [m; l] (for m != k) 
; and on any [k; m] (for m != l)
(assert 
	(forall ((k Int)) 
		(forall ((l Int)) 
			(=>
				(is-in-range k) 
				(=> 
					(pos k l)
					(forall ((m Int)) 
						(=> 
							(is-in-range m) 
							(and 
								(=> 
									(not (= m k)) 
									(not (pos m l))
								) 
								(=> 
									(not (= m l)) 
									(not (pos k m))
								)
							)
						)
					)
				)
			)
		)
    )
)


; ADD YOUR CONSTRAINTS HERE
; ============================= START ==============
; we must provide that on each diagonal will not occur two queens
(assert 
	(forall ((k Int)) 
		(forall ((l Int)) 
			(=> 
				(and 
					(is-in-range k)
					(is-in-range l)
				)
				(=>
					(pos k l)
					(forall ((m Int))
						(=>
							(is-in-range m)
							(and
								; top-left
								(=>
									(and 
										(is-in-range  (- k m))
										(is-in-range  (- l m))
									)
									(not (pos (- k m) (- l m)))
								)
								; top-right
								(=>
									(and 
										(is-in-range  (- k m))
										(is-in-range  (+ l m))
									)
									(not (pos (- k m) (+ l m)))
								)
							)
						)
					)
				)
			)
		)
    )
)


;============================= END ================
(declare-const y-pos-a Int)
(declare-const y-pos-b Int)
(declare-const y-pos-c Int)
(declare-const y-pos-d Int)
(declare-const y-pos-e Int)
(declare-const y-pos-f Int)
(declare-const y-pos-g Int)
(declare-const y-pos-h Int)

;			    1 <= y-pos <= 8		   row column
(assert (and (is-in-range y-pos-a) (pos 1 y-pos-a)))
(assert (and (is-in-range y-pos-b) (pos 2 y-pos-b)))
(assert (and (is-in-range y-pos-c) (pos 3 y-pos-c)))
(assert (and (is-in-range y-pos-d) (pos 4 y-pos-d)))
(assert (and (is-in-range y-pos-e) (pos 5 y-pos-e)))
(assert (and (is-in-range y-pos-f) (pos 6 y-pos-f)))
(assert (and (is-in-range y-pos-g) (pos 7 y-pos-g)))
(assert (and (is-in-range y-pos-h) (pos 8 y-pos-h)))

(check-sat)
(get-model)
(get-value (y-pos-a))
(get-value (y-pos-b))
(get-value (y-pos-c))
(get-value (y-pos-d))
(get-value (y-pos-e))
(get-value (y-pos-f))
(get-value (y-pos-g))
(get-value (y-pos-h))
(exit)











