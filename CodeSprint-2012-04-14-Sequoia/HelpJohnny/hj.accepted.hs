
tst = do
        nstr <- getLine
        let n = read nstr
        putStrLn $ if n `mod` 4 <= 1 then "YES" else "NO"

main = getLine >>= (\t -> mapM_ (const tst) [1 .. (read t)])

