; General Problem Solver 
; (load "d://Test//Lisp//Example04.cl")

(defun genericsearch (problem)
 (let(node newnode nodes states result)
  (push(list(car problem)nil 0 0)nodes)
  (loop (unless nodes(return))
   (setq node(car nodes))(setq nodes(cdr nodes))
   (when(equal(car node)(caddr problem))(return node))
   (dolist(operation(cadr problem))
    (setq newnode
     (list(funcall operation(car node))
      (cons operation(cons(car node)(cadr node)))
      (+(caddr node)1)))
    (unless(member(car newnode)states :test
            (function equal))
     (setq nodes(reverse(cons newnode(reverse nodes))))
	(setq states(cons(car newnode)states)))))))

(defun e1(state)(list 0(cadr state)))
(defun e2(state)(list(car state)0))
(defun f1(state)(list w1(cadr state)))
(defun f2(state)(list(car state)w2))
(defun g1(state)
 (list(-(car state)(min(car state)(- w2(cadr state))))
  (+(cadr state)(min(car state)(- w2(cadr state))))))    
(defun g2(state)
 (list(+(car state)(min(cadr state)(- w1(car state))))
  (-(cadr state)(min(cadr state)(- w1(car state))))))
(setq w1 7) (setq w2 5)
(setq problem '((0 0)(e1 e2 f1 f2 g1 g2)(4 0)))

; (genericsearch problem)
; > ((4 0) ( e2 (4 5) g1 (7 2) f1 (0 2) g1 (2 0) e2 (2 5) g1
;    (7 0) f1 (0 0)) 7)
