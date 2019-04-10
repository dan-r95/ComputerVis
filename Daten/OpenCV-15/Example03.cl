; Production Rules 
;  (load "d://Test//Lisp//Example03.cl")

(defun pri (condi ruleset factset)
  (prog (rule rules match matches trace (facts factset) v)
   loop0 (setq rules ruleset)
   (if (end-condition condi facts)
     (return (list 'solution facts)))
   loop1
   (cond ((setq rule (pop rules)) 
	    (setq matches (rule-condition rule facts)))
         ((setq v(pop trace))
	    (setq rule(nth 0 v)rules(nth 1 v)match(nth 2 v)
          matches(nth 3 v)facts(nth 4 v)))
         ((return (list 'no-solution facts))))
   (unless (setq match (pop matches)) (go loop1))
   (push (list rule rules match matches facts) trace)
   (setq facts (rule-action rule match facts))
   (go loop0)))

(defun end-condition (condi facts)
  (subsetp condi facts :test (function equal)))

(defun rule-condition (rule facts)
  (and (null (subsetp (cddr rule) facts
       :test (function equal)))
    (subsetp (car rule) facts :test (function equal))
    (car rule)))

(defun rule-action (rule match facts) (cons (caddr rule)
  facts))

(setq rules
      '((((it rains)) ---> (wet streets))
        (((wet streets)) ---> (slip danger))
        (((bad tires)) ---> (slip danger))))

(setq facts '((it rains)))

; (pri '((slip danger)) rules facts)
; >  (SOLUTION ((SLIP DANGER) (WET STREETS) (IT RAINS)))
