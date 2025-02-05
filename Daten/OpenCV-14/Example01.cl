; Symbolic Differentiation 
; (load "d://Test//Lisp//Example01.cl")

(defun diff (x v)
 (cond ((eq x v) 1)
  ((atom x) 0)
  ((member(car x)'(+ -))
	(list(car x)(diff(cadr x)v)(diff(caddr x)v)))
  ((eq(car x)'*) 
	(list '+(list '*(diff(cadr x)v)(caddr x))
	  (list '*(cadr x)(diff(caddr x)v))))
  ((eq(car x)'/) 
 	(list '/(list '-(list '*(diff(cadr x)v)(caddr x))
		           (list '*(cadr x)(diff(caddr x)v)))
		   (list 'expt(caddr x)2)))
  ((eq(car x)'sin)
	(list '*(diff(cadr x)v)(list 'cos(cadr x))))
  ((eq(car x)'cos)
	(list '*(diff(cadr x)v)(list '-(list 'sin(cadr x)))))
  ((and(eq(car x)'expt)(numberp(caddr x)))
	(list '* (diff(cadr x)v)
        (list '*(caddr x)(list 'expt(cadr x)(-(caddr x)1)))))
  (t (append '(no rule for) (list x)))))

(defun simp (x)
 (cond ((atom x) x)
  ((and(member(car x)'(+ -))(member 0 x))
	(simp(car(remove 0(cdr x)))))
  ((and(member(car x)'(*))(member 1 x))
	(simp(car(remove 1(cdr x)))))
  ((and(member(car x)'(*))(member 0 x)) 0)
  ((and(numberp(cadr x))(numberp(caddr x))) (eval x))
  (t (cons(car x)(mapcar(function simp)(cdr x))))))

(setq formula1 '(+ (expt x 3) (* (sin x) 5)))

; (diff formula1 'x)			
;  > (+ (* 1 (* 3 (EXPT X 2))) 
;      (+ (* (* 1 (COS X)) 5) (* (SIN X) 0)))
; (simp (diff formula1 'x))	
;  >  (+ (* 3 (EXPT X 2)) (+ (* (COS X) 5) 0))
