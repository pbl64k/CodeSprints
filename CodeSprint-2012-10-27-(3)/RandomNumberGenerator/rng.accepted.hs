
import Data.List
import Data.Ratio

prob :: Integer -> Integer -> Integer -> Ratio Integer
prob a b c =
    if a + b <= c
       then 1 % 1
       else if c <= b
               then ((sqarea c c) / 2) / (sqarea a b)
               else if c >= a
                    then ((sqarea a b) - ((sqarea ((a + b) - c) ((a + b) - c)) / 2)) / (sqarea a b)
                    else ((sqarea (c - b) b) + ((sqarea b b) / 2)) / (sqarea a b)

sqarea a b = (a * b) % 1

explode = unfoldr f
    where f str = let (chunk, rest) = span (/= ' ') str in if null chunk then Nothing else if null rest then Just (chunk, rest) else Just (chunk, tail rest)

tst = do
        i <- getLine
        let ii = map read (explode i)
        let r = prob (max (ii !! 0) (ii !! 1)) (min (ii !! 0) (ii !! 1)) (ii !! 2)
        putStrLn ((show $ numerator r) ++ "/" ++ (show $ denominator r))

main = do
         t <- getLine
         mapM_ (const tst) [1 .. (read t)]

