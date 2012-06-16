
msop n = (n + (9 * (n ^ 2)) + (2 * (n ^ 3))) `div` 6

tst = do
  n <- getLine
  (putStrLn . show . msop . pred . read) n

main = do
  t <- getLine
  mapM_ (const tst) [1 .. (read t)]

