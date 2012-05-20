
import Data.List
import Data.Set

winnum' pq = let (x, pq') = deleteFindMin pq in x : ((winnum' . (Data.Set.insert $ x * 3) . (Data.Set.insert $ x * 2)) pq')

winnum :: [Integer]
winnum = winnum' $ singleton 1

main = do
         inp <- getLine
         let (kstr, qstr) = span (/= ' ') inp
         let k = read kstr
         let q = read $ tail qstr
         (putStrLn . show) $ (Data.List.foldl' (\x y -> (x + y) `mod` q) 0 $ take k (Data.List.map (`mod` q) winnum))

