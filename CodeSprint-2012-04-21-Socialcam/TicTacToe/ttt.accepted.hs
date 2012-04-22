
import Data.List

data Outcome = Lost Int | Draw Int | Won Int deriving (Show, Eq, Ord)

main = do
         nstr <- getLine
         mapM_ (const tst) [1 .. (read nstr)]

tst = do
        str <- getLine
        (putStrLn . show . gm . outcome . prs) str

prs [] = []
prs ('\n' : _) = []
prs (' ' : xs) = prs xs
prs ('0' : xs) = 0 : (prs xs)
prs ('1' : xs) = 1 : (prs xs)
prs ('-' : '1' : xs) = (-1) : (prs xs)

gm (Won n) = n
gm (Lost n) = n
gm (Draw n) = n

flipBoard = map negate

move board n = (take n board) ++ (1 : (drop (n + 1) board))

negoutcome n (Lost _) = Won n
negoutcome n (Draw _) = Draw n
negoutcome n (Won _) = Lost n

invmove board n = (negoutcome n) (outcome newboard)
                  where newboard = flipBoard $ move board n

investigate board = maximum $ map (invmove board) (elemIndices 0 board)

outcome = outcomeInt . toInt

outcomeInt x = (memoizeInt outcomeInt') x

outcomeInt' = outcome' . fromInt

outcome' [1, 1, 1, _, _, _, _, _, _] = Lost 0
outcome' [_, _, _, 1, 1, 1, _, _, _] = Lost 0
outcome' [_, _, _, _, _, _, 1, 1, 1] = Lost 0
outcome' [1, _, _, 1, _, _, 1, _, _] = Lost 0
outcome' [_, 1, _, _, 1, _, _, 1, _] = Lost 0
outcome' [_, _, 1, _, _, 1, _, _, 1] = Lost 0
outcome' [1, _, _, _, 1, _, _, _, 1] = Lost 0
outcome' [_, _, 1, _, 1, _, 1, _, _] = Lost 0
outcome' [-1, -1, -1, _, _, _, _, _, _] = Won 0
outcome' [_, _, _, -1, -1, -1, _, _, _] = Won 0
outcome' [_, _, _, _, _, _, -1, -1, -1] = Won 0
outcome' [-1, _, _, -1, _, _, -1, _, _] = Won 0
outcome' [_, -1, _, _, -1, _, _, -1, _] = Won 0
outcome' [_, _, -1, _, _, -1, _, _, -1] = Won 0
outcome' [-1, _, _, _, -1, _, _, _, -1] = Won 0
outcome' [_, _, -1, _, -1, _, -1, _, _] = Won 0
outcome' board = if 0 `elem` board then investigate board else Draw 0

toInt :: [Int] -> Int
toInt [] = 0
toInt (x : xs) = ((x + 1) `mod` 3) + (3 * (toInt xs))

fromInt b = map f [0 .. 8]
            where f n = (b `div` (3 ^ n)) `mod` 3 - 1

data NaturalTree a = Node a (NaturalTree a) (NaturalTree a)

instance Functor NaturalTree where
   fmap f (Node a tl tr) = Node (f a) (fmap f tl) (fmap f tr)

Node a tl tr !!! 0 = a 
Node a tl tr !!! n =
   if odd n
     then tl !!! top
     else tr !!! (top-1)
        where top = n `div` 2

naturals r n =
   Node n
     ((naturals $! r2) $! (n+r))
     ((naturals $! r2) $! (n+r2))
        where r2 = 2*r

memoizeInt :: (Int -> a) -> (Int -> a)
memoizeInt f = (fmap f (naturals 1 0) !!!)

memoizeInteger :: (Integer -> a) -> (Integer -> a)
memoizeInteger f = (fmap f (naturals 1 0) !!!)

memoizeIntegral :: Integral a => (a -> b) -> (a -> b)
memoizeIntegral f = (fmap f (naturals 1 0) !!!)

