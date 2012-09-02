;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname change_money) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define (count-change money)
  (change money 6))

(define (change money kind-of-coins)
  (cond [(= money 0) 1]
        [(or (< money 0) (= kind-of-coins 0)) 0]
        [else (+ (change money (- kind-of-coins 1))
                 (change (- money 
                            (first-denomination kind-of-coins))
                         kind-of-coins))         
         ]
        ))
(define (first-denomination kind-of-coins)
  (cond 
    [(= kind-of-coins 1) 1]
    [(= kind-of-coins 2) 5]
    [(= kind-of-coins 3) 10]
    [(= kind-of-coins 4) 20]
    [(= kind-of-coins 5) 50]
    [(= kind-of-coins 6) 100]
    ))
(count-change 5)