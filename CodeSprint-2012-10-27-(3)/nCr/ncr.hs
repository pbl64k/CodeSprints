
import Data.List

m = 142857

bc n k = (product [(n - k + 1) .. n]) `div` (product [1 .. k])

explode = unfoldr f
    where f str = let (chunk, rest) = span (/= ' ') str in if null chunk then Nothing else if null rest then Just (chunk, rest) else Just (chunk, tail rest)

tst = do
        i <- getLine
        let ii = map read (explode i)
        (putStrLn . show) ((bc (ii !! 0) (ii !! 1)) `mod` m)

main = do
         t <- getLine
         mapM_ (const tst) [1 .. (read t)]

