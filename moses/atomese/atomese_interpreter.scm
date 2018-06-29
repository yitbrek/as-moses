;given domain
(define domain
 (SetLink
  (ListLink
   (Node "r1")
   (ListLink
    (NumberNode "1.000000")
    (NumberNode "2.000000")
   )
  )
  (ListLink
   (Node "r2")
   (ListLink
    (NumberNode "3.000000")
    (NumberNode "4.000000")
   )
  )
  (ListLink
   (Node "r3")
   (ListLink
    (NumberNode "5.000000")
    (NumberNode "6.000000")
   )
  )))

;program one
(define i1+i2
 (Put
  (Variable "$R")
  (List
   (ExecutionOutput
    (GroundedSchemaNode "scm:row")
    (List (Variable "$R")
    )
   )
   (gar (Variable "$R"))
   (Plus
    (ExecutionOutput
     (GroundedSchemaNode "scm:f1")
     (List (Variable "$R")
     )
    )
    (ExecutionOutput
     (GroundedSchemaNode "scm:f2")
     (List (Variable "$R"))
    )
   )
  )
  domain)
)

;inputs/features

(define (f1 atom)
 (gar (gdr atom)
 ))


(define (f2 atom)
 (gdr (gdr atom))
)

;rownames
(define (row therow)
 (gar therow))