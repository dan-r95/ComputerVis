; Mengenvereinigung, Fakultaet
; (load "d://Test//Lisp//Example00.cl")

(defun myunion (x y)
  (cond ((null x) y)
    ((member (car x) y) (myunion (cdr x) y))
    (t (cons (car x) (myunion (cdr x) y)))))

; (myunion '(1 2) '(2 3))  > (1 2 3)

(defun fak1(x)(if(= x 0)1(* x(fak1(- x 1)))))
(defun fak2(x)(let((s 1))(dotimes(n x s)(setq s(* s(+ n 1))))))

; (fak1 10)
; (fak2 100)
