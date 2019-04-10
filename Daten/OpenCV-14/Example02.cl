; Semantic Network 
; (load "d://Test//Lisp//Example02.cl")

(defun defarc (x r y) (setf (get x r) (union(get x r)(list y))))
(defun delarc (x r y) (setf (get x r) (remove y (get x r))))

(defun getnod (x r)
  (if x (union (get (car x) r) (getnod (cdr x) r))))

(defun restr (x f)
  (remove-if (function (lambda (s) (null (funcall f s)))) x))

(setq martha nil) (setq anna nil) (setq fritz nil)
(setq frieda nil) (setq female nil) (setq male nil)

(defun mother (x) (getnod x 'mother))
(defun married (x) (getnod x 'married))
(defun sex (x) (getnod x 'sex))
(defun father (x) (married (mother x)))
(defun parents (x) (union (mother x) (father x)))
(defun grandmother (x) (mother (parents x)))
(defun child (x)
  (restr (sex '(male female))
    (function(lambda(s) (intersection x (parents(list s)))))))
(defun daughter (x) (intersection (child x) (sex '(female))))
(defun ancestor (x)
  (if x (union (parents x) (ancestor (parents x)))))

(defarc 'martha 'mother 'anna)
(defarc 'anna 'married 'fritz)
(defarc 'fritz 'mother 'frieda)
(defarc 'female 'sex 'martha)
(defarc 'female 'sex 'anna)
(defarc 'female 'sex 'frieda)
(defarc 'male 'sex 'fritz)

; (mother '(martha))		>   (anna)
; (father '(martha))		>   (fritz)
; (parents '(martha))		>   (fritz anna)
; (grandmother '(martha))	>   (frieda)	
; (child '(anna))		>   (martha)
; (daughter '(fritz))		>   (martha)
; (ancestor '(martha))	>   (frieda fritz anna)
