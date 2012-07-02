
fib = 1 : 1 : [a + b | (a, b) <- zip fib (tail fib)]

ff n = head $ filter ((> 1) . (gcd n)) fib

tst = do
  n <- getLine
  let n' = read n
  let x = ff n'
  putStrLn $ show x ++ " " ++ (show $ gcd x n')

main = getLine >>= \t -> mapM_ (const tst) [1 .. (read t)]

