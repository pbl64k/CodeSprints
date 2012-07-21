
import Data.List

list n = take n $ l n 1 3

l n i c = (i, c) : l n (succ i) (if c + 3 > n then ((c + 3) `mod` n) - 1 else c + 3)

main = do
  let n = 100000
  putStrLn $ show n
  putStrLn $ intercalate " " (map (show . snd) (list n))

