
import Data.Bits
import Data.List
import Data.Word
import Random
import System.IO.Unsafe

main = getLine >>= (putStrLn . show . sol . read)

sol n = let pds = map (sum . dgts) fastprimes
            aps = filter (\(_, x) -> primep x) (zip fastprimes pds)
			in (fst . head) (drop (n - 1) aps)

toBase :: Integral a => a -> a -> [a]
toBase = unfoldr . toBase'

toBase' :: Integral a => a -> a -> Maybe (a, a)
toBase' _ 0 = Nothing
toBase' b n = Just (n `mod` b, n `div` b)

dgts :: Integral a => a -> [a]
dgts = toBase 10

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

fbnd :: Integral a => a -> a
fbnd = round . sqrt . fromIntegral

primep :: Integral a => a -> Bool
primep 1 = False
primep 2 = True
primep 3 = True
primep 4 = False
primep 5 = True
primep 6 = False
primep 7 = True
primep 8 = False
primep 9 = False
primep x | x `mod` 2 == 0 = False
         | x `mod` 3 == 0 = False
         | otherwise = (memoizeIntegral primep') x

primep' :: Integral a => a -> Bool
primep' x = all ((/= 0) . (x `mod`)) (takeWhile (<= (fbnd x)) fastprimes)

wheel2357 :: Integral a => [a]
wheel2357 = 2 : 4 : 2 : 4 : 6 : 2 : 6 : 4 : 2 : 4 : 6 : 6 : 2 : 6 : 4 : 2 : 6 : 4 : 6 : 8 : 4 : 2 : 4 : 2 : 4 : 8 : 6 : 4 : 6 : 2 : 4 : 6 : 2 : 6 : 6 : 4 : 2 : 4 : 6 : 2 : 6 : 4 : 2 : 4 : 2 : 10 : 2 : 10 : wheel2357

spin :: Integral a => [a] -> a -> [a]
spin (x : xs) n = n : spin xs (n + x)

fastprimes :: Integral a => [a]
fastprimes = 2 : 3 : 5 : 7 : sieve (spin wheel2357 11)

sieve :: Integral a => [a] -> [a]
sieve [] = []
sieve (x : xs) = x : sieve' xs (insertprime x xs pQempty)
                 where
                      insertprime p xs table = pQinsert (p * p) (map (* p) xs) table
                      sieve' [] table = []
                      sieve' (x : xs) table
                                           | nextComposite <= x = sieve' xs (adjust table)
                                           | otherwise = x : sieve' xs (insertprime x xs table)
                                             where
                                                  nextComposite = pQminKey table
                                                  adjust table
                                                              | n <= x = adjust (pQdeleteMinAndInsert n' ns table)
                                                              | otherwise = table
                                                                where (n, n' : ns) = pQminKeyValue table

data Ord k => PQPriorityQueue k a = Nil | Branch k a (PQPriorityQueue k a) (PQPriorityQueue k a) deriving Show

pQempty :: Ord k => PQPriorityQueue k a
pQempty = Nil

pQminKey :: Ord k => PQPriorityQueue k a -> k
pQminKey = fst . pQminKeyValue

pQminKeyValue :: Ord k => PQPriorityQueue k a -> (k, a)
pQminKeyValue (Branch k a _ _) = (k, a)

pQinsert :: Ord k => k -> a -> PQPriorityQueue k a -> PQPriorityQueue k a
pQinsert k a q = pQunion (pQsingleton k a) q

pQdeleteMin :: Ord k => PQPriorityQueue k a -> PQPriorityQueue k a
pQdeleteMin (Branch _ _ l r) = pQunion l r

pQdeleteMinAndInsert :: Ord k => k -> a -> PQPriorityQueue k a -> PQPriorityQueue k a
pQdeleteMinAndInsert k a Nil = pQsingleton k a
pQdeleteMinAndInsert k a (Branch _ _ l r) = pQunion (pQinsert k a l) r

pQunion :: Ord k => PQPriorityQueue k a -> PQPriorityQueue k a -> PQPriorityQueue k a
pQunion l Nil = l
pQunion Nil r = r
pQunion l@(Branch kl _ _ _) r@(Branch kr _ _ _)
                                               | kl <= kr  = pQlink l r
                                               | otherwise = pQlink r l

pQlink (Branch k a Nil m) r = Branch k a r m
pQlink (Branch k a ll lr) r = Branch k a lr (pQunion ll r)

pQsingleton :: Ord k => k -> a -> PQPriorityQueue k a
pQsingleton k a = Branch k a Nil Nil

