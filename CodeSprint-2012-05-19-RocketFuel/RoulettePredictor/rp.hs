
import Data.List
import Data.Set

data X = X Integer Integer deriving (Show, Eq)

instance Ord X where
    x1@(X i1 j1) `compare` x2@(X i2 j2) =
        if i1 == i2 && j1 == j2
            then EQ
            else
                if i1 == i2
                    then j1 `compare` j2
                    else
                        if j1 == j2
                            then i1 `compare` i2
                            else x1 `logcmp` x2

logbin3 = (log 3) / (log 2)

(X i1 j1) `logcmp` (X i2 j2) = let l = (fromIntegral $ i1 - i2) + (logbin3 * (fromIntegral $ j1 - j2)) in l `compare` 0.0

expmod b x q = if x == 0 then 1 else if even x then let p = expmod b (x `div` 2) q in (p * p) `mod` q else ((expmod b (x - 1) q) * b) `mod` q
   
--winnum' pq = let (x@(X i j), pq') = deleteFindMin pq in x : ((winnum' . (Data.Set.insert $ X i (succ j)) . (Data.Set.insert $ X (succ i) j)) pq')
winnum' pq =
            let (x@(X i j), pq') = deleteFindMin pq
                pq'' = Data.Set.insert (X i (succ j)) (if j == 0 then Data.Set.insert (X (succ i) j) pq' else pq')
                in x : (winnum' pq'')

winnum q = Data.List.map (\(X i j) -> ((expmod 2 i q) * (expmod 3 j q)) `mod` q) (winnum' $ singleton (X 0 0))

main = do
         inp <- getLine
         let (kstr, qstr) = span (/= ' ') inp
         let k = read kstr
         let q = read $ tail qstr
         (putStrLn . show) $ (Data.List.foldl' (\x y -> (x + y) `mod` q) 0 $ take k (winnum q))

