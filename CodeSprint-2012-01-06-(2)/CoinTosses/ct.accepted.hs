
import Data.Array.IArray

ct0 = (!) ct0'

ct0' :: Array Int Integer
ct0' = array (1, 1000) (take 1000 ct0'')

ct0'' :: [(Int, Integer)]
ct0'' = (1, 2) : [(succ i, (1 + x) * 2) | (i, x) <- ct0'']

ct :: Int -> Int -> Integer
ct n 0 = ct0 n
ct n m = if n == m then 0 else 1 + ((ct n (m + 1)) `div` 2) + ((ct0 n) `div` 2)

main = do
         t <- getLine
         mapM_ (const tst) [1 .. (read t)]

tst = do
        l <- getLine
        let (n, m) = (takeWhile (/= ' ') l,  tail $ dropWhile (/= ' ') l)
        putStrLn ((show $ ct (read n) (read m)) ++ ".00")

