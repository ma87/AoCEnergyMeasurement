module Queue 
  ( push
  , pushList
  , pop
  , null
  , empty
  ) where

import           Prelude hiding (null)

data Queue a = Queue { inbox :: [a], outbox :: [a] } deriving Show

push v (Queue a b) = Queue (v:a) b

pushList xs q = foldr push q xs

pop (Queue [] []) = (Nothing, Queue [] [])
pop (Queue inb (v:outb)) = (Just v, Queue inb outb)
pop (Queue inb []) = pop (Queue [] (reverse inb))

null (Queue [] []) = True
null _ = False

empty = Queue [] []
