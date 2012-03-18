
winnable x = x `mod` 2 == 0

pg x y = (winnable x) || (winnable y)

sol = do
        l <- getLine
        let (x, y) = span (/= ' ') l
        putStrLn (if pg (read x) (read $ tail y) then "Alice" else "Bob")

main = getLine >>= (\t -> mapM_ (const sol) [1 .. (read t)])

