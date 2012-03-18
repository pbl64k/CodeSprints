
import Data.List

tk' :: String -> String -> [Integer]
tk' [] [] = []
tk' buf [] = (read buf) : []
tk' buf (' ' : str) = (read buf) : (tk' [] str)
tk' buf (c : str) = tk' (buf ++ [c]) str

x' :: [(Integer, Integer)] -> (Integer, Integer) -> [(Integer, Integer)]
x' [] p = [p]
x' opts p@(a, w) = let wmax = foldl' (\wm (a', w') -> if a' < a then max wm (w + w') else wm) w opts
                       (prefix, postfix) = (takeWhile ((< a) . fst) opts, dropWhile ((< a) . fst) opts)
                       postfix' = filter ((> wmax) . snd) postfix
                       opts' = prefix ++ if (null postfix') || (a < ((fst . head) postfix')) then (a, wmax) : postfix' else postfix'
                       in opts'

main = do
         t <- getLine
         mapM_ (const tst) [1 .. (read t)]

tst = do
        _ <- getLine
        al <- getLine
        wl <- getLine
        let ps = zip (tk' [] al) (tk' [] wl)
        let opts = foldl' x' [] ps
        putStrLn (show $ maximum (map snd opts))

