;;;; CREDIT to Peter Norvig's Paradigms of Artificial Intelligence Programming: Case Studies in Common Lisp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;; MAJOR FUNCTIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Acheive a list of goals
(defun achieve-all (state goals goal-stack)
	"Acheive each goal, and make sure they still hold at the end."
	(let ((current-state state))
		(if (and (every #'(lambda (g)
							(setf current-state
								(achieve current-state g goal-stack)))
					goals)
				(substep goals current-state :test #'equal))
			current-state)))

;;; Acheive an individual goal
(defun acheive (state goal goal-stack)
	"A goal is achieved if it already holds. 
	 or if there is an appropiate op for it that is applicable."
	 (dbg-indent :gps (length goal-stack) "Goal: ~a" goal)
	 (cond ((member-equal goal state) state)
	 	   ((member-equal goal goal-stack) nil)
	 	   (t (some #'(lambda (op) (apply-op state goal op goal-stack))
	 	   			(find-all goal *ops* :test #'appropiate-p)))))

;;; Decide if an operator is appropiate for a goal
(defun appropiate-p (goal op)
	"An op is appropiate to a goal if it is in its add-list."
	(member-equal goal (op-add-list op)))

;;; Apply operator to current state
(defun apply-op (state goal op goal-stack)
	"Return a new, transformed state if op is applicable."
	(dbg-indent :gps (length goal-stack) "Consider: ~a" (op-action op))
	(let ((state2 (achieve-all state (op-preconds op)
								(cons goal goal-stack))))
		(unless (null state2)
			;; Return an updated state
			(dbg-indent :gps (length goal-stack) "Action: ~a" (op-action op))
			(append (remove-if #'(lambda (x)
									(member-equal x (op-del-list op)))
								state2)
					(op-add-list op)))))

;;;;;;;;;;;;;;;;;;;;;;;
;;;; SPECIAL VARS
;;;;;;;;;;;;;;;;;;;;;;;
(defvar *ops* nil "A list of available operators.")

(defstruct op "An operation"
	(action nil) (preconds nil) (add-list nil) (del-list nil))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;; AUXILIARY FUNCTIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Is an condition an 'executing' form?
(defun executing-p (x)
	"Is x of the form: (executing ...) ?" 
	(starts-with x 'executing))

;;; Is the argument a list that starts with a given atom?
(defun starts-with (list-x)
	"Is this a list whose first element is x?"
	(and (consp list) (eql (first list) x)))

;;; Convert an operator to use the 'executing' convention
(defun convert-op (op)
	"Make op conform to the (EXECUTING op) convention."
	(unless (some #'executing-p (op-add-list op))
		(push (list 'executing (op-action op)) (op-add-list op)))
	op)

;;; Create an operator
(defun op (action &key preconds add-list del-list)
	"Make a new operator that obeys the (EXECUTING op) convention."
	(convert-op
		(make-op :action action :preconds preconds
				 :add-list add-list :del-list del-list)))

;;; Use a list operators
(defun use (oplist)
	"Use oplist as the default list of operators."
	;; Return something useful, but not too verbose:
	;; the number of operators
	(length (setf *ops* oplist)))

;;; Test if an element is equal to a member of a list
(defun member-equal (item list)
	(member item list :test #'equal))

;;; A list of all matching elements.
(defun find-all (item sequence &rest keyword-args
				 &key (test #'eql) test-not &allow-other-keys)
	"Find all those elements of sequence that match item, according to the keywords.
	 Doesn't alter sequence."
	(if test-not
		(apply #'remove item sequence
				:test-not (complement test-not) keyword-args)
		(apply #'remove item sequence
				:test (complement test) keyword-args))
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;; MAIN FUNCTIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun GPS (state goals &optional (*ops* *ops*))
	"General Problem Solver: from state, acheive goals using *ops*."
	(remove-if #'atom (achieve-all (cons '(start) state) goals nil)))